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

//gainCard() not included in dominion.h
int gainCard(int, struct gameState *, int, int);

// Testing gainCard
int main()
{
	printf("Testing gainCard()\n");
	int r;

	//Setup an empty game.
	struct gameState *g = calloc(1, sizeof(struct gameState));

	//no supply count.
	r = gainCard(smithy, g, 0, 0);
	myassert(r == -1, "No supplyCount. Should fail.");

	// Initialize supplyCount for smithy to -1 (not used)
	g->supplyCount[smithy] = -1;

	r = gainCard(smithy, g, 0, 0);
	myassert(r == -1, "Card not used. Should fail.");

	//Set supplyCount for smithy to 10 so that there will be a card for the
	//player to gain
	g->supplyCount[smithy] = 10;

	// Should add smithy to player 0 discard
	r = gainCard(smithy, g, 0, 0);
	myassert(r == 0, "Card exists. Should not fail.");
	myassert(g->discard[0][0] == smithy, "Smithy should be in discard");

	// Should add smithy to player 0 deck
	r = gainCard(smithy, g, 1, 0);
	myassert(r == 0, "Card exists. Should not fail.");
	myassert(g->deck[0][0] == smithy, "Smithy should be in deck");

	// Should add smithy to player 0 hand
	r = gainCard(smithy, g, 2, 0);
	myassert(r == 0, "Card exists. Should not fail.");
	myassert(g->hand[0][0] == smithy, "Smithy should be in hand");

	checkasserts();
	free(g);
	return 0;
}
