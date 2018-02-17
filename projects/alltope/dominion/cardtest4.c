/*
 Author: Erin Alltop
 Class: CS362 - Winter 2018
 Description: Assignment 3. cardtest4

   Testing Council Room Card
   Expected results:
   		- Current player receives 4 cards
			- Current player deckcount decreases by 4
			- Current player handcount increases by 4
		- Current player receives no bonus coins
   		- Current player receives 1 buy
   		- Each other player draws a card
   			- Each other player deckcount decreases by 1
   			- Each other player handcount increases by 1
   		- No state change occurs to Victory and Kingdom Cards
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council_room"

int main() {

    int shuffledCards = 0;
    int i; 
    int handpos = 0, choice1 = -1, choice2 = -1, choice3 = -1, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n\n", TESTCARD);

	// ----------- TEST 1: current player receives 3 cards --------------
	printf("TEST 1: Current player receives 4 cards.\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 3); // draw 4 + discard 1

	if(testG.handCount[thisPlayer] != (G.handCount[thisPlayer] + 3))
	{
		printf("TEST 1 FAILED!\n\n");
	}
	else
		printf("TEST 1 SUCCEEDED!\n\n");

	//-------------TEST 2: Three cards are drawn from the current player's deck ----------
	printf("TEST 2: Four cards are drawn from the current player's deck.\n");

	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 4 + shuffledCards);

	if(testG.deckCount[thisPlayer] != (G.deckCount[thisPlayer] - 4 + shuffledCards))
	{
		printf("TEST 2 FAILED!\n\n");
	}
	else
		printf("TEST 2 SUCCEEDED!\n\n");


	//------------TEST 3: Current player receives no bonus coins ----------------

	printf("TEST 3: Current Player received no bonus coins.\n");

	printf("coins = %d, expected = %d\n", testG.coins, G.coins + 0);

	if(testG.coins != (G.coins + 0))
	{
		printf("TEST 3 FAILED!\n\n");
	}
	else
		printf("TEST 3 SUCCEEDED!\n\n");

	//-----------TEST 4: Current player receives one buy--------------------

	printf("TEST 4: Current player receives one buy.\n");

	printf("Buys = %d, Expected = %d\n", testG.numBuys, G.numBuys + 1);

	if(testG.numBuys != G.numBuys + 1)
	{
		printf("TEST 3 FAILED!\n\n");
	}
	else
		printf("TEST 3 SUCCEEDED!\n\n");

	//-----------TEST 5: Each other player deckcount decreased by 1 --------------------

	printf("Each other player deck count decreased by 1.\n");

	for(i = 1; i < numPlayers; i++) //Checking deck count
	{
		printf("Deck count expected for other player %d:\n", i);
		printf("count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i] - 1);

		if(testG.deckCount[i] != G.deckCount[i] - 1)
		{
		printf("TEST 5 FAILED!\n\n");
	}
	else
		printf("TEST 5 SUCCEEDED!\n\n");
	}


	//----------TEST 6: Each other player handcount increased by 1----------------

	printf("Each other player hand count increased by 1.\n");

		for(i = 1; i < numPlayers; i++) //Checking hand count
	{
		printf("Hand count expected for other player %d:\n", i);
		printf("count = %d, expected = %d\n", testG.handCount[i], G.handCount[i] + 1);

		if(testG.handCount[i] != G.handCount[i] + 1)
		{
		printf("TEST 6 FAILED!\n\n");
	}
	else
		printf("TEST 6 SUCCEEDED!\n\n");
	}


	//--------- TEST 7: No changes to other player's discard pile  -----------

	printf("TEST 7: No changes to other player's discard pile.\n");

	for(i = 1; i < numPlayers; i++) //Checking discard count
	{
		printf("Discard count expected for other player %d:\n", i);
		printf("count = %d, expected = %d\n", testG.discardCount[i], G.discardCount[i]);

		if(testG.discardCount[i] != G.discardCount[i])
		{
		printf("TEST 7 FAILED!\n\n");
	}
	else
		printf("TEST 7 SUCCEEDED!\n\n");
	}


	//------------TEST 5: Victory and Kingdom Card states remain unchanged ----------

	printf("TEST 8: No state change in Victory Cards.\n");

	printf("Victory Cards:\n");
	printf("count = %d, expected = %d\n", (testG.supplyCount[estate] + testG.supplyCount[duchy] + testG.supplyCount[province]), 
		(G.supplyCount[estate] + G.supplyCount[duchy] + G.supplyCount[province]));

		if((testG.supplyCount[estate] + testG.supplyCount[duchy] + testG.supplyCount[province]) !=
		(G.supplyCount[estate] + G.supplyCount[duchy] + G.supplyCount[province]))
		{
		printf("TEST 8 FAILED!\n\n");
		}
		else
		printf("TEST 8 SUCCEEDED!\n\n");


	printf("Kingdom Cards:\n");

	int testKingCards = (testG.supplyCount[adventurer] + testG.supplyCount[embargo] + testG.supplyCount[village] + testG.supplyCount[minion]
		+ testG.supplyCount[mine] + testG.supplyCount[cutpurse] + testG.supplyCount[sea_hag] + testG.supplyCount[tribute]
		+ testG.supplyCount[smithy] + testG.supplyCount[council_room]);

	int gKingCards = (G.supplyCount[adventurer] + G.supplyCount[embargo] + G.supplyCount[village] + G.supplyCount[minion]
		+ G.supplyCount[mine] + G.supplyCount[cutpurse] + G.supplyCount[sea_hag] + G.supplyCount[tribute]
		+ G.supplyCount[smithy] + G.supplyCount[council_room]);

	printf("TEST 8: No state change in Kingdom Cards.\n");
	printf("count = %d, expected = %d\n", testKingCards, gKingCards);

		if(testKingCards != gKingCards)
		{
		printf("TEST 9 FAILED! \n\n");
		}
		else
		printf("TEST 9 SUCCEEDED!\n\n");


	printf("\n >>>>> Testing complete for %s <<<<<\n\n", TESTCARD);

	return 0;
}



