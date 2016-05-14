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

// Card Testing: village
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

	printf("Testing card: village\n");

	for (n = 0; n < atoi(argv[2]); n++) {
		// variables to hold random data to feed to initialize game and the game
		// state.
		int randPlayers, randActions, randHandCount;

		randPlayers = (rand() % 2) + 2;
		randActions = rand() % 10;
		randHandCount = rand() % 6;

		int final_numhand, init_numhand, init_numact, final_numact;

		//Setup a game.
		struct gameState *g = calloc(1, sizeof(struct gameState));
		int k[10] =
		    { smithy, adventurer, gardens, embargo, cutpurse, mine,
			ambassador,
			outpost, baron, tribute
		};

		initializeGame(randPlayers, k, seed, g);

		//Make the card we are testing the first in the users hand, and make sure
		//we play the first user. Set random values.
		g->hand[0][0] = village;
		g->whoseTurn = 0;
		g->numActions = randActions;
		g->handCount[0] = randHandCount;

		//Get current number of cards in hand and number of actions for comparison.
		init_numhand = numHandCards(g);
		init_numact = g->numActions;

		playCard(0, 0, 0, 0, g);

		//playCard with village should add one card to the hand, but discard one
		//(village), so the final should be the same as initial. And number of
		//actions should increased by two, but subtract one for playing the card.
		final_numhand = numHandCards(g);
		final_numact = g->numActions;
		myassert(final_numhand == init_numhand,
			 "Village should add one card to hand.");

		myassert(final_numact == init_numact + 1,
			 "Village should add two actions");

		free(g);
	}

	checkasserts();
	return 0;
}
