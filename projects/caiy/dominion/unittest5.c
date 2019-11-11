#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
	int i, r, b;
	int e = 0;
	// set your card array
	int k[10] = { gold, silver, feast, gardens, mine , remodel, smithy, village, baron, great_hall };
	// declare the game state. Put a mine on hand, a gold on handpos[0].
	struct gameState G;
	// declare the arrays of all coppers, silvers, and golds

	printf("Begin Testing mine():\n");

	int seed = rand() % 100;//initialize random seed

	// Bug: The code is expected to return failure to use the card if the value of the treasure card chosen to trash + 3 is smaller than the card to gain. (The card to gain is no more than the card to trash + 3) But this code will return failure if card to trash + 3 is bigger than the card to gain.
	// set the state of your variables so that you will trigger the bug for feast
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(2, k, seed, &G); // initialize a new game. Set num of players to 2. 

	//from dominion.c, for 2 players, the supply count of estates is 8.
	b = case_mine(1, 0, copper, 0, &G); //gain choice2, which is copper. The handpos[0] is gold.
	if (b == -1)//If failed to throw away a gold for a copper
		printf("Failed throw gold for the copper\n");
	else
		printf("Passed throw gold for the copper\n");

	printf("Ending Testing mine()\n");
	return 0;
}