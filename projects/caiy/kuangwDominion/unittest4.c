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
	int m[10] = { estate, copper, adventurer, tribute, ambassador, gardens, mine, remodel, gold, duchy };//fill your deck with a victory card and a treasure card on top.
	struct gameState G;
	// declare the arrays of all coppers, silvers, and golds

	printf("Begin Testing tribute():\n");

	int seed = rand() % 100;//initialize random seed
	int tributer[2] = { -1, -1 }; //default in cardEffect Function
	//test trashing card for there is no handPos
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(3, k, seed, &G); // initialize a new game. Set num of players to 3. 

	b = tributeCard(1,0, &G, tributer); //Check if the card has been trashed
	for (i = 0; i < G.deckCount[1]; i++) {
		if (G.deck[0][i] == tribute) {
			printf("Failed trashing tribute\n");
			e = 1;
			break;
		}
	}
	if (e == 0)
		printf("Passed trashing tribute\n");


	//test chosen card effect. It should be a treasure and a victory card on the front of each decks.
	// set the state of your variables so that you will trigger the bug for feast
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(3, m, seed, &G); // initialize a new game. Set num of players to 3. 

	b = tributeCard(1,0, &G, tributer); //Check if the effect has played
	if (G.coins == 2)//should add coins by 2
		printf("Passed adding coins\n");
	else
		printf("Failed adding coins\n");
	if (G.deckCount[0] == 11)//should trash tribute and draw cards by 2
		printf("Passed drawing cards\n");
	else
		printf("Failed drawing cards\n");

	//test if there are two different cards and both of them are action cards.
	memset(&G, 23, sizeof(struct gameState)); // clear the game state
	r = initializeGame(3, k, seed, &G); // initialize a new game. Set num of players to 3. 
	int action = G.numActions;
	b = tributeCard(1,0, &G, tributer); //Check if the effect has played
	if (G.numActions == action + 4)//should add actions by 4
		printf("Passed adding action and read 2 different cards \n");
	else if (G.numActions == action + 2)
		printf("Failed to read 2 different action cards\n");
	else
		printf("Failed to read cards\n");

	printf("Ending Testing tribute()\n");
	return 0;
}