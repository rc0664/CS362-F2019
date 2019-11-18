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
	int i, j, r, b, c, d;
	int player = 0;//the first player will be our tester
	// set your card array
	int k[10] = { adventurer, tribute, ambassador, gardens, mine , remodel, smithy, village, baron, great_hall };
	// set 0: on top are tribute and adventurer, 2 action cards.
	int m[10] = { estate, copper, adventurer, tribute, ambassador, gardens, mine, remodel, gold, duchy };
	//set 1: on top are estate and copper, 1 treasure card and 1 victory card.
	struct gameState G;
	// declare the arrays of all coppers, silvers, and golds

	printf("\nBegin Testing tribute():\n");

	for (i = 0; i < 50; i++)
	{
		int e = 0; //condition 1
		int ne = 0; //test adding estate
		int playernum = 2 + rand() % 3; //randomly 2-4 players. From the testing, I found that if player number is 1 the current player will be exception.
		int playernext = 0;
		int seed = 1 + rand() % 100;
		int a = rand() % 2;//0 or 1 for using which cardset
		int tributer[2] = { -1, -1 }; //default in cardEffect Function
		memset(&G, 23, sizeof(struct gameState)); // clear the game state
		if(a == 0)
			r = initializeGame(playernum, k, seed, &G); // initialize a new game. using set 0, Set num of players to playnum.
		else
			r = initializeGame(playernum, m, seed, &G); // initialize a new game. using set 1, Set num of players to playnum.
		player = whoseTurn(&G); //move to current Player
		
		if (player != playernum)
			playernext = player + 1;
		else
			playernext = 0;

		printf("\n loop %d\n", i+1);
		printf("\n player# %d, card set = %d, currentplayer = %d,next player# %d \n", playernum,a, player, playernext);

		//check if tribute is on hand
		for (j = 0; j < G.deckCount[player]; j++) {
			if (G.deck[player][j] == tribute) {
				printf("Get tribute on deck on Test # %d\n", i+1);
				e = 1;
				break;
			}
		}
		for (j = 0; j < G.handCount[player]; j++) {
			if (G.hand[player][j] == tribute) {
				printf("Get Minion on hand on Test # %d\n", i+1);
				e = 1;
				break;
			}
		}
		if (e == 0)
			printf("Failed to get tribute on Test # %d\n", i+1);

		c = G.numActions;
		d = G.coins;

		//play tribute
		b = case_tribute(player,playernext,&G,tributer); //for choice1 and 2, 0 is false, otherwise true.


		//check if tribute has been threw away after played
		for (j = 0; j < G.deckCount[player]; j++) {
			if (G.deck[player][j] == tribute) {
				printf("Failed to threw tribute after played it on Test # %d\n", i+1);
				break;
			}
		}
		//for card set 0, on top are tribute and adventurer, 2 different action cards.
		if (a == 0)
			if (G.numActions != c + 4)//should add actions by 4
				printf("Failed to add actions by 4 for card set 0 on Test # %d\n", i+1);
		//for card set 1, on top are estate and copper, 1 treasure card and 1 victory card.
		if (a == 1) {
			if (G.coins != d + 2)//should add coins by 2
				printf("Failed to add coins by 2 for card set 1 on Test # %d\n", i+1);
			if (G.deckCount[player] != 11) //Threw away tribute, so the card count should be 11.
				printf("Failed to draw 2 cards for card set 1 on Test # %d\n", i+1);
		}
		//throw away 2 cards in front of next player's deck.
		if(G.deckCount[playernext] != 8)
			printf("Failed to throw 2 cards from next player's deck on Test # %d, the # of cards on next player's deck is %d\n", i+1, G.deckCount[playernext]);
	}
	printf("\nEnd Testing tribute():\n");
	return 0;
}