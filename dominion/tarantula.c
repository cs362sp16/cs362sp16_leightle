#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Colors for printing
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

// Card Testing: adventurer
int main(int argc, char **argv)
{
	int seed, n;
	int lines = 1366;	//number of lines in gcov file
	float totalfail = 0;
	float totalpass = 0;
	FILE *fp;
	float array[lines][2];	//Keep track of fails/passes
	memset(array, 0, sizeof(array));
	seed = 1;

	srand(seed);

	// gcov doesn't seem to run correctly unless there has been some usage of
	// dominion.c already
	system("./randomtestadventurer 1 1 > /dev/null");

	for (n = 0; n < 100; n++) {
		int randPlayers = (rand() % 3) + 2;

		int r = 0;
		int i = 0;
		int tr_hand = 0;
		int tr_deck = 0;
		int expected = 0;
		int failed = 0;
		int tempcard;

		//Setup a game.
		struct gameState *g = calloc(1, sizeof(struct gameState));
		int k[10] =
		    { smithy, adventurer, gardens, embargo, cutpurse, mine,
			ambassador,
			outpost, baron, tribute
		};

		initializeGame(randPlayers, k, seed, g);

		//Make the card we are testing the first in the users hand, and make sure
		//we play the first user.
		g->hand[0][0] = adventurer;
		g->whoseTurn = 0;

		//Determine how many treasure cards are currently in the hand, and how many
		//are in the deck, up to 2, for comparison after we play the adventurer
		//card.

		//Randomize deck
		for (i = 0; i < g->deckCount[0]; i++) {
			g->deck[0][i] = rand() % (treasure_map + 1);
		}

		for (i = 0; i < g->handCount[0]; i++) {
			tempcard = g->hand[0][i];
			if (tempcard == copper || tempcard == silver
			    || tempcard == gold) {
				tr_hand++;
			}
		}

		for (i = 0; i < g->deckCount[0] && tr_deck < 3; i++) {
			tempcard = g->deck[0][i];
			if (tempcard == copper || tempcard == silver
			    || tempcard == gold) {
				tr_deck++;
			}
		}

		expected = tr_hand + tr_deck;

		playCard(0, 0, 0, 0, g);

		for (i = 0; i < g->handCount[0]; i++) {
			tempcard = g->hand[0][i];
			if (tempcard == copper || tempcard == silver
			    || tempcard == gold) {
				r++;
			}
		}

		if (r != expected) {
			failed = 1;
			totalfail++;
		} else {
			totalpass++;
		}

		char buffer[256];
		char *s;
		system("gcov dominion.c > /dev/null");
		fp = fopen("dominion.c.gcov", "r");
		if (fp == NULL) {

			printf("nulled\n");
		}

		i = 0;
		while (fgets(buffer, 256, fp) != NULL) {
			s = strpbrk(buffer, ":-#");
			if (failed) {
				if (!strncmp(s, ":", 1)) {	//there is a number
					array[i][0] += 1;
				}
			} else {
				if (!strncmp(s, ":", 1)) {	//there is a number
					array[i][1] += 1;
				}
			}

			i++;
		}
		system("mv dominion.c.gcov tarantula.out");

		fclose(fp);
		free(g);
	}
	int i;
	char buffer[256];

	fp = fopen("tarantula.out", "r");
	i = 0;
	float x;
	while (fgets(buffer, 256, fp) != NULL) {
		x = (array[i][0] / totalfail) / ((array[i][1] / totalpass) +
						 (array[i][0] / totalfail));
		if (x > 0.6) {
			printf(RED "%f%s\n" RESET, x, buffer);
		} else if (x > 0.3) {
			printf(YEL "%f%s\n" RESET, x, buffer);
		} else {
			printf(GRN "%f%s\n" RESET, x, buffer);
		}

		i++;
	}
	return 0;
}
