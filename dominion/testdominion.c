#include <stdio.h>
#include <stdlib.h>
#include "rngs.h"
#include "dominion.h"

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
	int nplayers = (rand() % 2) + 2;

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
	return 0;
}
