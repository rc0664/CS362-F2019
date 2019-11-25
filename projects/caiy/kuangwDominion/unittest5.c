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
	int k[10] = { gold, copper, silver, gardens, mine , remodel, smithy, village, baron, great_hall };
	// declare the game state. Put a mine on hand, two golds on front.
	int m[10] = { silver,copper, gold, curse, mine , remodel, smithy, village, baron, great_hall }; //put copper and silver to check if we throwed correct card
	struct gameState G;
	// declare the arrays of all coppers, silvers, and golds

	printf("Begin Testing mine():\n");

	int seed = rand() % 100;//initialize random seed

	// Bug: The code is expected to return failure to use the card if the value of the treasure card chosen to trash + 3 is smaller than the card to gain. (The card to gain is no more than the card to trash + 3) But this code will return failure if card to trash + 3 is bigger than the card to gain.
	// set the state of your variables so that you will trigger the bug for feast
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(2, k, seed, &G); // initialize a new game. Set num of players to 2. 

	//from dominion.c, for 2 players, the supply count of estates is 8.
	b = mineCard(0, copper,0, 4, &G); //gain choice2, which is copper. The choice 1 is gold
	if (b == -1)//If failed to throw away a gold for a copper
		printf("Failed throw gold for the copper\n");
	else
		printf("Passed throw gold for the copper\n");
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(2, k, seed, &G); // initialize a new game. Set num of players to 2. 
	b = mineCard(2, copper,0, 4, &G); //gain choice2, which is copper. The choice 1 is silver
	if (b == -1)//If failed to throw away a gold for a copper
		printf("Failed throw silver for the copper\n");
	else
		printf("Passed throw silver for the copper\n");
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(2, k, seed, &G); // initialize a new game. Set num of players to 2. 
	b = mineCard(1, gold,0, 4, &G); //gain choice2, which is gold. The choice 1 is copper
	if (b == -1)//If failed to throw away a gold for a copper
		printf("Passed to deal with throw copper for the gold\n");
	else
		printf("Failed to deal with throw copper for the gold\n");


	//Test if the trashed card is correct
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(2, m, seed, &G); // initialize a new game. Set num of players to 2. 

	//from dominion.c, for 2 players, the supply count of estates is 8.
	b = mineCard(0, copper,0, 4, &G); //we choose to trash a silver
	for (i = 0; i < G.deckCount[0]; i++) {
		if (G.deck[0][i] == silver) {
			printf("Failed trashing silver\n");
			e = 1;
			break;
		}

	}
	if (e == 0)
		printf("Passed trashing silver\n");
	
	//Test if we did not choose a treasure e.g. a curse
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(2, m, seed, &G); // initialize a new game. Set num of players to 2. 

	//from dominion.c, for 2 players, the supply count of estates is 8.
	b = mineCard(3, copper, 0, 4, &G); //we choose to trash a curse
	if(b == -1)
		printf("Passed choosing range 1\n");
	else
		printf("Failed choosing range 1\n");

	//Test if we choose to get a non-treasure card e.g. a curse
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(2, m, seed, &G); // initialize a new game. Set num of players to 2. 

	//from dominion.c, for 2 players, the supply count of estates is 8.
	b = mineCard(1, curse, 0, 4, &G); //we choose to buy a curse with a copper.
	if (b == -1)
		printf("Passed choosing range 2\n");
	else
		printf("Failed choosing range 2\n");

	printf("Ending Testing mine()\n");
	return 0;
}