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

// Testing supplyCount()
int main()
{
	printf("Testing supplyCount()\n");
	int r, i;

	//Setup an empty game.
	struct gameState *g = calloc(1, sizeof(struct gameState));

	//There should not be any cards yet, so supplyCount should return 0 for all
	//cards.
	r = 0;
	for (i = 0; i < treasure_map; i++) {
		r = r + supplyCount(i, g);
	}
	myassert(r == 0, "There should not be any cards yet.\n");

	//Set smithy to 10 cards
	g->supplyCount[smithy] = 10;

	r = supplyCount(smithy, g);
	myassert(r == 10, "Smithy should have 10 cards.\n");
	// Initialize supplyCount

	checkasserts();
	return 0;
}
