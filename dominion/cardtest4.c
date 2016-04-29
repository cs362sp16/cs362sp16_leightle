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

// Card Testing: outpost
int main()
{
	printf("Testing card: outpost\n");
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
	g->hand[0][0] = outpost;
	g->whoseTurn = 0;

	//Get initial outpostPlayed for comparison
	i = g->outpostPlayed;

	//Playing the outpost card increments the outpostPlayed flag by one,
	//presumbably for use else where. For this test, I am not determining
	//whether the playing the card actually causes the correct action, only
	//that playing the card sets the flag properly. Testing for correct action
	//would be testing other functionality of the code.
	playCard(0, 0, 0, 0, g);

	r = g->outpostPlayed;
	myassert(r == i + 1,
		 "Outpost should increment the outpostPlayed flag by 1.");

	checkasserts();
	free(g);
	return 0;
}
