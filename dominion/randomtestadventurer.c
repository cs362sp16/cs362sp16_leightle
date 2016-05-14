#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

int failed = 0;

void myassert(int b, char *msg)
{
	if (b == 0) {
		printf("FAILED ASSERTION: %s\n", msg);
		failed = 1;
	}
}

void checkasserts()
{
	if (!failed) {
		printf("TEST SUCCESSFULLY COMPLETED.\n");
	}
}

// Card Testing: adventurer
int main(int argc, char **argv)
{
	int seed, n;

	if (argc != 3) {
		printf("Usage: %s SEED #ofTests\n", argv[0]);
		exit(1);
	} else {
		seed = atoi(argv[1]);
		srand(seed);
	}

	printf("Testing card: adventurer\n");

	for (n = 0; n < atoi(argv[2]); n++) {
		int randPlayers = (rand() % 3) + 2;

		int r = 0;
		int i = 0;
		int tr_hand = 0;
		int tr_deck = 0;
		int expected = 0;
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

		myassert(r == expected,
			 "Adventurer should add a maximum of 2 treasure cards");

		free(g);
	}
	checkasserts();
	return 0;
}
