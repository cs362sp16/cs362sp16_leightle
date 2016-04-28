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

// Testing buyCard. Does not test if the card is correctly placed in the
// discard pile after purchase, as that is handled by the gainCard function.
// Only test if buyCard allows the player to buy a card when they should, and
// disallows buying if the player either doesn't have enough coins, enough
// numBuys, or in the Buy phase.
int main()
{
	printf("Testing buyCard function.\n");
	int r, i;

	//Setup an empty game.
	struct gameState *g = calloc(1, sizeof(struct gameState));

	// Initialize supplyCount
	for (i = 0; i < treasure_map; i++) {
		g->supplyCount[i] = 10;
	}

	// Setup a player to buy cards
	g->whoseTurn = 0;
	g->coins = 0;
	g->numBuys = 0;
	g->phase = 0;

	// No coins, numBuys, and wrong phase. Definitely shouldn't be able to buy
	// a card.
	r = buyCard(smithy, g);
	myassert(r == -1,
		 "Should not work. No coins, numBuys, and wrong phase.");

	// Setup so that player should be able to buy cards
	g->coins = 10;
	g->numBuys = 1;
	g->phase = 1;

	r = buyCard(smithy, g);
	myassert(r == 0, "Should work. Has coins, numBuys, and correct phase.");

	// No coins, but otherwise able to buy coins
	g->coins = 0;
	g->numBuys = 1;
	g->phase = 1;

	r = buyCard(smithy, g);
	myassert(r == -1, "Should not work. No coins.");

	// Give coins, but remove numBuys.
	g->coins = 10;
	g->numBuys = 0;
	g->phase = 1;

	r = buyCard(smithy, g);
	myassert(r == -1, "Should not work. No numBuys.");

	// Wrong phase. Action phase.
	g->coins = 10;
	g->numBuys = 1;
	g->phase = 0;

	r = buyCard(smithy, g);
	myassert(r == -1, "Should not work. Wrong phase (Action)");

	// Wrong phase. Clean-Up phase.
	g->coins = 10;
	g->numBuys = 1;
	g->phase = 0;

	r = buyCard(smithy, g);
	myassert(r == -1, "Should not work. Wrong phase (Clean-Up)");

	checkasserts();
	return 0;
}
