#include "dominion.h"
#include <stdio.h>

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
	//Setup a game to test
	struct gameState g;

	int k[10] =
	    { smithy, adventurer, gardens, embargo, cutpurse, mine, ambassador,
		outpost, baron, tribute
	};

	int r = initializeGame(2, k, 5, &g);

	myassert(r == 0, "No duplicates, 2 players, should succeed");

	// After initialization, neither of the conditions for game over should be
	// met

	r = isGameOver(&g);
	myassert(r == 0, "Just started game. Should not be over");

	//Set province to 0. Should end game.
	g.supplyCount[province] = 0;
	r = isGameOver(&g);
	myassert(r == 1, "Province is 0. Should end game");

	//Reset province. Then choose any 3 of the other supply and set to zero.
	//Should end game.
	g.supplyCount[province] = 10;
	g.supplyCount[copper] = 0;
	g.supplyCount[estate] = 0;
	g.supplyCount[duchy] = 0;
	r = isGameOver(&g);
	myassert(r == 1, "Three of supply are zero. Should end game");

	checkasserts();
	return 0;
}
