/* 
 Author: Erin Alltop
 Class: CS362 - Winter 2018
 Description: Assignment 3. cardtest2

   Testing Adventurer Card
   Expected results:
   		- Current player receives 2 Treasure cards
   		- The 3 cards come from his own deck
   			- Total handcount +2
   			- Total deckcount decreased by 2 + # of other cards revealed that were not Treasure cards
   			- Discard pile increased by # of other cards revealed that were not Treasure cards
   		- No state change in other players
   		- No state change occurs to Victory and Kingdom Cards
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
    int shuffledCards = 0;
    int i; 
    int handpos = 0, choice1 = -1, choice2 = -1, choice3 = -1, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {duchy, gardens, province, estate, tribute, mine, cutpurse, ambassador, great_hall, adventurer};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n\n", TESTCARD);

	// ----------- TEST 1: current player receives 2 cards cards --------------
	printf("TEST 1: Current player receives 2 cards.\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 2);

	if(testG.handCount[thisPlayer] != (G.handCount[thisPlayer] + 2))
	{
		printf("TEST 1 FAILED!\n\n");
	}
	else
		printf("TEST 1 SUCCEEDED!\n\n");

	//-------------TEST 2: Three cards are drawn from the current player's deck ----------
	printf("TEST 2: Two cards are drawn from the current player's deck.\n");

	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 2 + shuffledCards);

	if(testG.deckCount[thisPlayer] != (G.deckCount[thisPlayer] - 2 + shuffledCards))
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

	//-----------TEST 4: Other player states are unchanged--------------------
	printf("TEST 4: No state change in other players.\n");

	for(i = 1; i < numPlayers; i++) //Checking discard count
	{
		printf("Discard count expected for other player %d:\n", i);
		printf("count = %d, expected = %d\n", testG.discardCount[i], G.discardCount[i]);

		if(testG.discardCount[i] != G.discardCount[i])
		{
		printf("TEST 4 FAILED! DISCARD COUNT CHANGED\n\n");
	}
	else
		printf("TEST 4 DISCARD COUNT SUCCEEDED!\n\n");
	}

	for(i = 1; i < numPlayers; i++) //Checking deck count
	{
		printf("Deck count expected for other player %d:\n", i);
		printf("count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);

		if(testG.deckCount[i] != G.deckCount[i])
		{
		printf("TEST 4 FAILED! DECK COUNT CHANGED\n\n");
	}
	else
		printf("TEST 4 DECK COUNT SUCCEEDED!\n\n");
	}

	for(i = 1; i < numPlayers; i++) //Checking hand count
	{
		printf("Hand count expected for other player %d:\n", i);
		printf("count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);

		if(testG.handCount[i] != G.handCount[i])
		{
		printf("TEST 4 FAILED! HAND COUNT CHANGED\n\n");
	}
	else
		printf("TEST 4 HAND COUNT SUCCEEDED!\n\n");
	}

	//------------TEST 5: Victory and Kingdom Card states remain unchanged ----------
	printf("TEST 5: No state change in Victory and Kingdom Cards.\n");

	printf("Victory Cards:\n");
	printf("count = %d, expected = %d\n", (testG.supplyCount[estate] + testG.supplyCount[duchy] + testG.supplyCount[province]), 
		(G.supplyCount[estate] + G.supplyCount[duchy] + G.supplyCount[province]));

		if((testG.supplyCount[estate] + testG.supplyCount[duchy] + testG.supplyCount[province]) !=
		(G.supplyCount[estate] + G.supplyCount[duchy] + G.supplyCount[province]))
		{
		printf("TEST 5 FAILED!\n\n");
		}
		else
		printf("TEST 5 SUCCEEDED!\n\n");


	printf("Kingdom Cards:\n");

	int testKingCards = (testG.supplyCount[adventurer] + testG.supplyCount[embargo] + testG.supplyCount[village] + testG.supplyCount[minion]
		+ testG.supplyCount[mine] + testG.supplyCount[cutpurse] + testG.supplyCount[sea_hag] + testG.supplyCount[tribute]
		+ testG.supplyCount[smithy] + testG.supplyCount[council_room]);

	int gKingCards = (G.supplyCount[adventurer] + G.supplyCount[embargo] + G.supplyCount[village] + G.supplyCount[minion]
		+ G.supplyCount[mine] + G.supplyCount[cutpurse] + G.supplyCount[sea_hag] + G.supplyCount[tribute]
		+ G.supplyCount[smithy] + G.supplyCount[council_room]);


	printf("count = %d, expected = %d\n", testKingCards, gKingCards);

		if(testKingCards != gKingCards)
		{
		printf("TEST 5 FAILED!\n\n");
		}
		else
		printf("TEST 5 SUCCEEDED!\n\n");


	printf("\n >>>>> Testing complete for %s <<<<<\n\n", TESTCARD);

	return 0;
}



