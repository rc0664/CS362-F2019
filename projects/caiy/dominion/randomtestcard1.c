#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(NULL));  //set random seed
	int i, j, r, b, c;
	// set your card array
	int k[10] = { adventurer, baron, council_room, estate, gardens, mine , remodel, smithy, village, great_hall };
	// declare the game state. Put a baron and an estate on hand.
	struct gameState G;
	// declare the arrays of all coppers, silvers, and golds

	printf("\nBegin Testing baron():\n");

	for (i = 0; i < 50; i++)
	{
		int playernum = 2 + rand() % 3; //randomly 2-4 players. From the testing, I found that if player number is 1 the current player will be exception.
		int seed = 1 + rand() % 100;
		int a = rand() % 2;//0 or 1 for choice1
		int e = 0; //test baron on hand
		int ne = 0; //test adding estate
		int player = 0;//the first player will be our tester
		memset(&G, 23, sizeof(struct gameState)); // clear the game state
		r = initializeGame(playernum, k, seed, &G); // initialize a new game. Set num of players to playnum.
		
		player = whoseTurn(&G); //move to current Player

		printf("\n loop %d\n", i+1);
		printf("\n player# %d, choice1 = %d, currentplayer = %d \n", playernum, a, player);

		//check if baron is on hand or on deck
		for (j = 0; j < G.deckCount[player]; j++) {
			if (G.deck[player][j] == baron) {
				printf("Get Baron on deck on Test # %d\n", i+1);
				e = 1;
				break;
			}
		}
		for (j = 0; j < G.handCount[player]; j++) {
			if (G.hand[player][j] == baron) {
				printf("Get Baron on hand on Test # %d\n", i+1);
				e = 1;
				break;
			}
		}
		if(e == 0)
			printf("Failed to get baron on Test # %d\n", i+1);

		c = G.numBuys; //number of buys
		//play baron
		b = case_baron(player, a, &G); //choice1=0 to gain an estate, choice1=1 to throw an estate.
				//test +1 buy
		if (G.numBuys != c + 1)
			printf("Failed to +1 buy after played baron on Test # %d\n", i+1);

		//check if baron has been threw away after played
		for (j = 0; j < G.deckCount[player]; j++) {
			if (G.deck[player][j] == baron) {
				printf("Failed to threw baron after played it on Test # %d\n", i+1);
				break;
			}
		}


		//tese throw estate
		if (a == 1)//if player throw an estate for 4 coins
		{
			if (G.coins != 4)//test get coin
				printf("Failed to get coin after threw an estate on Test # %d\n", i+1);
			for (j = 0; j < G.deckCount[player]; j++) {
				if (G.deck[player][j] == estate) { //test throw an estate 
					printf("Failed to throw an estate on Test # %d\n", i+1);
					break;
				}
			}
		}
		//test gain an estate
		if (a == 0) {//If player gained an estate, the supplycount of estate should be decreased.
			if (supplyCount(estate, &G) != 7 && playernum == 2)
				printf("Failed to reduce supply count of estate by 1 after gained one on Test # %d. While 2 players the supplycount becomes %d\n", i+1, supplyCount(estate, &G));
			if (supplyCount(estate, &G) != 11 && playernum > 2)
				printf("Failed to reduce supply count of estate by 1 after gained one on Test # %d. While %d players the supplycount becomes %d\n", i+1, playernum, supplyCount(estate, &G));
			for (j = 0; j < G.deckCount[player]; j++) {
				if (G.deck[player][j] == estate) {
					ne += 1;
				}
			}
			if (ne != 2)
				printf("Wrong number of estates on hand after gained one on Test # %d. It is %d\n", i+1,ne);
		}
	}
	printf("\nEnd Testing baron():\n");
	return 0;
}

