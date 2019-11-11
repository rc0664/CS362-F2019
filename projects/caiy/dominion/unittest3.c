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
	int k[10] = { adventurer, adventurer, ambassador, gardens, mine , remodel, smithy, village, baron, great_hall };
	// declare the game state. Put a baron on hand. Made 2 adventurer to check the bug
	int m[10] = { estate, estate, ambassador, estate, estate , estate, estate, estate, estate, estate};
	struct gameState G;
	// declare the arrays of all coppers, silvers, and golds

	printf("Begin Testing ambassador():\n");

	int seed = rand() % 100;//initialize random seed

	//test adding j
	// set the state of your variables so that you will trigger the bug for feast
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(2, k, seed, &G); // initialize a new game. Set num of players to 2. 

	b = case_ambassador(1, 0, 2, 1, &G); //choice1=0 to be different from handpos of 1. 
	if (b == -1)//If the j++ code only check if position i is equals to the choice1th card on current player¡¯s hand, j will be 1, smaller than choice2, which is 2.
		printf("Failed adding j\n");
	else
		printf("Passed adding j\n");

	//Bug: The removal of cards from a player's deck does not follow the game logic for the Ambassador card. The current player's cards are trashed instead of being returned to the supply for that card type.
	// set the state of your variables so that you will trigger the bug for feast
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(2, m, seed, &G); // initialize a new game. Set num of players to 2. Use m to get a deck filled with estates.

	//from dominion.c, for 2 players, the supply count of estates is 8.
	b = case_ambassador(1, 0, 1, 5, &G); //handpos is 5, it is an estate. 
	if (supplyCount(estate, &G) > 8) //If the card has been returned to the supply
		printf("Passed returning card to supply\n");
	else
		printf("Failed returning card to supply\n");



	printf("Ending Testing ambassador()\n");
	return 0;
}