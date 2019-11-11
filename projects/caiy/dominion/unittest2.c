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
	// set your card array
	int k[10] = { minion, council_room, feast, gardens, mine , remodel, smithy, village, adventurer, great_hall };
	// declare the game state. Put a minion on hand.
	struct gameState G;
	// declare the arrays of all coppers, silvers, and golds

	printf("Begin Testing minion():\n");

	int seed = rand() % 100;//initialize random seed

	//test the card on hand of player 0 and 2
	// set the state of your variables so that you will trigger the bug for feast
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(3, k, seed, &G); // initialize a new game. Set num of players to 3. 

	//All players should have 4 cards on hand after minion played
	b = case_minion (1, 2, 0, 1, &G); //choice1=0, choice2!=0 to discard hand.
	if(G.deckCount[0] == 4 && G.deckCount[2] ==4)
		printf("Passed redraw cards\n");
	else
		printf("Failed redraw cards\n");

	


	printf("Ending Testing baron()\n");
	return 0;
}