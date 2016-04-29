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

// Testing isGameOver
int main()
{
	printf("Testing isGameOver()\n");
	int r, i;

	//Setup an empty game.
	struct gameState *g = calloc(1, sizeof(struct gameState));

	// Initialize supplyCount
	for (i = 0; i < treasure_map; i++) {
		g->supplyCount[i] = 10;
	}

	// None of the conditions for game over should exist.
	r = isGameOver(g);
	myassert(r == 0, "Initialzed supplyCount. Should not be over");

	//Set province to 0. Should end game.
	g->supplyCount[province] = 0;
	r = isGameOver(g);
	myassert(r == 1, "Province is 0. Should end game");

	//Reset province. Then choose any 3 of the other supply and set to zero.
	//Should end game.
	g->supplyCount[province] = 10;
	g->supplyCount[copper] = 0;
	g->supplyCount[estate] = 0;
	g->supplyCount[duchy] = 0;
	r = isGameOver(g);
	myassert(r == 1, "Three of supply are zero. Should end game");

	checkasserts();
	free(g);
	return 0;
}
