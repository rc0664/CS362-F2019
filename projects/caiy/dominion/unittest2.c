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
int k[10] = { adventurer, adventurer, ambassador, gardens, minion , remodel, smithy, village, baron, great_hall };
// declare the game state. Put a minion on hand.
struct gameState G;
// declare the arrays of all coppers, silvers, and golds

printf("Begin Testing minion():\n");

int seed = rand() % 100;//initialize random seed

//This is a code I tried to test the card on hand of player 0 and 2.
memset(&G, 23, sizeof(struct gameState)); // clear the game state
r = initializeGame(3, k, seed, &G); // initialize a new game. Set num of players to 3. 

//All players should have 4 cards on hand after minion played
b = case_minion(0, 0, 1, 4, &G);//It is not working. I don't know why, but the input functions should be correct. int case_minion(int currentPlayer, int choice1, int choice2, int handPos, struct gameState *state)
/*	
	if(G.deckCount[1] == 4 && G.deckCount[2] == 4 && G.deckCount[0] == 4)
		printf("Passed redraw cards\n");
	else
		printf("Failed redraw cards\n");
*/

	printf("Ending Testing minion()\n");
	return 0;
}