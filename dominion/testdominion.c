#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"

void actionPhase(struct gameState *g)
{
	int i, c1, c2, c3;
	for (i = 0; i < g->handCount[g->whoseTurn]; i++) {
		if (g->hand[g->whoseTurn][i] >=
		    adventurer || g->hand[g->whoseTurn][i] <= treasure_map) {
			c1 = rand() % (treasure_map + 1);
			c2 = rand() % (treasure_map + 1);
			c3 = rand() % (treasure_map + 1);
			playCard(g->hand[g->whoseTurn][i], c1, c2, c3, g);
			break;
		}
	}
}

void buyPhase(int *array, struct gameState *g)
{
	int i, r, card;
	int money = 0;
	g->phase = 1;
	for (i = 0; i < g->handCount[g->whoseTurn]; i++) {
		switch (g->hand[g->whoseTurn][i]) {
		case copper:
			money += 1;
			break;
		case silver:
			money += 2;
			break;
		case gold:
			money += 3;
			break;
		}
	}

	for (i = 0; i < g->numBuys; i++) {
		if (money == 0) {
			card = copper;
		} else if (money >= 8) {
			card = province;
		} else if (money >= 5) {
			card = duchy;
		} else if (money >= 2) {
			card = estate;
		} else {
			card = rand() % 13;

			if (card < 10) {
				card = array[card];
			} else {
				card = card - 10 + copper;
			}

		}
		if (supplyCount(card, g) > 0) {
			r = buyCard(card, g);
		}
	}
}

int main(int argc, char **argv)
{
	struct gameState *g = calloc(1, sizeof(struct gameState));

	int seed = atoi(argv[1]);
	srand(seed);

	int num_king_cards = treasure_map - gold;
	int array[num_king_cards];
	int k[10];
	int i, n, temp;

	// Random number of players 2-4
	int nplayers = (rand() % 3) + 2;

	//Array for all the kingdom cards
	for (i = 0; i < num_king_cards; i++) {
		array[i] = i + adventurer;
	}

	// Shuffle the array using Fisher/Yates
	for (i = num_king_cards - 1; i >= 0; i--) {
		n = rand() % (i + 1);
		temp = array[n];
		array[n] = array[i];
		array[i] = temp;
	}

	// Take the first ten from the shuffled cards for the kingdom cards
	for (i = 0; i < 10; i++) {
		k[i] = array[i];
	}

	initializeGame(nplayers, k, seed, g);

	while (!isGameOver(g)) {
		for (i = 0; i < nplayers; i++) {
			actionPhase(g);
			buyPhase(array, g);
			printf("Player %d: %d\n", i, scoreFor(i, g));
			endTurn(g);
		}
	}

	printf("\nGame Over\n");
	for (i = 0; i < nplayers; i++) {
		printf("Player %d: %d\n", i, scoreFor(i, g));
	}

	return 0;
}
