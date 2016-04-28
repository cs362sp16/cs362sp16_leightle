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

// Card Testing: smithy
int main()
{
	printf("Testing card: smithy\n");
	int r, i;

	//Setup a game.
	struct gameState *g = calloc(1, sizeof(struct gameState));
	int k[10] =
	    { smithy, adventurer, gardens, embargo, cutpurse, mine, ambassador,
		outpost, baron, tribute
	};

	initializeGame(2, k, 5, g);

	//Make the card we are testing the first in the users hand, and make sure
	//we play the first user.
	g->hand[0][0] = smithy;
	g->whoseTurn = 0;

	//Get current number of cards in hand for comparison.
	i = numHandCards(g);

	playCard(0, 0, 0, 0, g);

	//playCard with smithy should add three cards to the hand, but discard one
	//(smithy), so the total should be initial + 2.
	r = numHandCards(g);
	myassert(r == i + 2, "Smithy should add three cards to hand.");

	checkasserts();
	return 0;
}
