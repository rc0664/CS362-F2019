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
	int i,r,b;
	int e = 0;
	// set your card array
	int k[10] = {adventurer, council_room, feast, gardens, mine , remodel, smithy, village, baron, great_hall };
	// declare the game state. Put a baron on hand.
	struct gameState G;
	// declare the arrays of all coppers, silvers, and golds
	
 	printf("Begin Testing baron():\n");
	
	int seed = rand()%100;//initialize random seed

	//test removing estates
	// set the state of your variables so that you will trigger the bug for feast
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(2, k, seed, &G); // initialize a new game. Set num of players to 2. 
	
	//from dominion.c, for 2 players, the supply count of estates is 8.
	b = case_baron(1, 0, &G); //choice1=0 to gain an estate
	if(supplyCount(estate, &G)  == 7)//the default supply count is 8. It should become 7 after we played baron.
		printf("Passed removing estates\n");
	else
		printf("Failed removing estates\n");
	
	//test trashing card
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(2, k, seed, &G); // initialize a new game. Set num of players to 2. 

	b = case_baron(1, 1, &G); //choice1=1 to discard an estate
	for(i = 0; i < G.deckCount[1]; i++){
		if(G.deck[1][i]  == baron){
			printf("Failed trashing baron\n");
			e = 1;
			break;
		}

	}
	if (e == 0)
		printf("Passed trashing baron\n");
	printf("Ending Testing baron()\n");
	return 0;
}