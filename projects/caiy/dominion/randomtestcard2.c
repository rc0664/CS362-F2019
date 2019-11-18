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
	int i, j, r, b, c,d;
	int player = 0;//the first player will be our tester
	// set your card array
	int k[10] = { adventurer, minion, estate, gardens, mine , remodel, smithy, village, baron, great_hall };
	// declare the game state. Put a minion on handpos[1].
	struct gameState G;
	// declare the arrays of all coppers, silvers, and golds

	printf("\nBegin Testing minion():\n");

	for (i = 0; i < 50; i++)
	{
		int f = 0; //condition 1
		int e = 0;
		int ne = 0; //test adding estate
		int playernum = 2 + rand() % 3; //randomly 2-4 players. From the testing, I found that if player number is 1 the current player will be exception.
		int seed = 1 + rand() % 100;
		int a = rand() % 2;//0 or 1 for choice1
		if (a == 0)
			e = 1;//a is condition 1 whereas e is condition 2
		memset(&G, 23, sizeof(struct gameState)); // clear the game state
		r = initializeGame(playernum, k, seed, &G); // initialize a new game. Set num of players to playnum.

		player = whoseTurn(&G); //move to current Player

		printf("\n loop %d\n", i+1);
		printf("\n player# %d, choice1 = %d, choice2 = %d, currentplayer = %d \n", playernum, a, e, player);

		//check if minion is on hand
		for (j = 0; j < G.deckCount[player]; j++) {
			if (G.deck[player][j] == minion) {
				printf("Get Minion on deck on Test # %d\n", i+1);
				f = 1;
				break;
			}
		}
		for (j = 0; j < G.handCount[player]; j++) {
			if (G.hand[player][j] == minion) {
				printf("Get Minion on hand on Test # %d\n", i+1);
				f = 1;
				break;
			}
		}
		if (f == 0)
			printf("Failed to get minion on Test # %d\n", i+1);

		c = G.numActions; //number of actions
		d = G.coins; //number of coins

		//play minion
		b = case_minion(player, 1, a, e, &G); //for choice1 and 2, 0 is false, otherwise true.
		//test +1 action
		if (G.numActions != c + 1)
			printf("Failed to +1 action after played minion on Test # %d\n", i+1);

		//check if minion has been threw away after played
		for (j = 0; j < G.deckCount[player]; j++) {
			if (G.deck[player][j] == minion) {
				printf("Failed to threw minion after played it on Test # %d\n", i+1);
				break;
			}
		}
		//for choice1, a=1 and e=0, then choice1. Gain 2 coins.
		if (G.coins != d + 2 && a == 1)
			printf("Failed to +2 coins after played minion on Test # %d\n", i+1);
		//for choice2, a=0 and e=1, then choice2, discard all hand cards and redraw 4 cards, the other players with 5 or more cards will discard all and redraw 4 too.
		if (a == 0)
			for (j = 0; j < playernum; j++) {//check all players!
				if (G.handCount[j] != 4) {
					printf("Failed to discard all and redraw 4 cards after played minion on Test # %d. The handcount of player %d is %d\n", i+1,j, G.handCount[j]);
					break;
				}
			}
	}
	printf("\nEnd Testing minion():\n");
	return 0;
}