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
	int k[10] = { adventurer, tribute, ambassador, gardens, mine , remodel, smithy, village, baron, great_hall };
	// declare the game state. Put a baron on hand. Made 2 adventurer to check the bug
	int m[10] = { tribute, copper, copper, copper , copper , copper , copper , copper , copper ,copper };//fill your deck with coppers
	struct gameState G;
	// declare the arrays of all coppers, silvers, and golds

	printf("Begin Testing tribute():\n");

	int seed = rand() % 100;//initialize random seed
	int tributer[2] = { -1, -1 }; //default in cardEffect Function
	//test trashing card
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(3, k, seed, &G); // initialize a new game. Set num of players to 2. 

	b = case_tribute(1, 2, &G, tributer); //Check if the card has been trashed
	for (i = 0; i < G.deckCount[1]; i++) {
		if (G.deck[1][i] == tribute) {
			printf("Failed trashing tribute\n");
			break;
		}
	}
	if (e == 0)
		printf("Passed trashing tribute\n");
/*
	//test array index error
	// set the state of your variables so that you will trigger the bug for feast
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(3, m, seed, &G); // initialize a new game. Set num of players to 3. 
	for (i = 0; i < G.handCount[1]; i++)
	{
		if (G.hand[3][i] == copper)
		{
			discardCard(i, 1, &G, 0);
			break;
		} //throw away all coppers from player 3. Player 3 now only have one card: tribute.
		assert(b = case_tribute(1, 2, &G, tributer)); //Check if the array index problem occurs
		printf("Passed array index test\n");
	}

*/
	printf("Ending Testing tribute()\n");
	return 0;
}