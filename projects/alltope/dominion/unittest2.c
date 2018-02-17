/* 
 Author: Erin Alltop
 Class: CS362 - Winter 2018
 Description: Assignment 3. unittest2

   TestinG updateCoins Function
   Expected results:
   		- for each copper, current player coins +1
   		- for each silver, current player coins +2
   		- for each gold, current player coins +3
   		- for each bonus, current player coins +bonus
   		- for mixed coin types, current player coins +number of coins
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"

#define TESTFUNC "updateCoins"

int main(){
    struct gameState G, testG;
    
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    int numPlayers = 2;
    int thisPlayer = 0;
    int seed = 1000;
    int bonus;
    int copperCoin = 1;
    int silverCoin = 2;
    int goldCoin = 3;
    
    initializeGame(numPlayers, k, seed, &G);
    
    printf("----------------- Testing Function: %s ----------------\n", TESTFUNC);

    // ----------- TEST 1: Testing with empty hand and 0 bonus coins. --------------
    printf("TEST 1: Testing with empty hand and 0 bonus coins.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    int coinsBefore = 1;
    bonus = 0;
    testG.coins = coinsBefore;
    testG.handCount[thisPlayer] = 0;
    updateCoins(thisPlayer, &testG, bonus);

    printf("coins = %d, expected = %d\n", testG.coins, 0);
    if(testG.coins != 0)
    {
    	printf("TEST 1 FAILED!\n\n");
    }
    else
    	printf("TEST 1 SUCCEEDED!\n\n");
    
    // ----------- TEST 2: Testing with empty hand and 10 bonus coins. --------------
    printf("TEST 2: Testing with empty hand and 10 bonus coins. \n");
    memcpy(&testG, &G, sizeof(struct gameState));
    coinsBefore = 1;
    bonus = 10;
    testG.coins = coinsBefore;
    testG.handCount[thisPlayer] = 0;
    updateCoins(thisPlayer, &testG, bonus);
    
    printf("coins = %d, expected = %d\n", testG.coins, bonus);    
    if(testG.coins != bonus)
     {
    	printf("TEST 2 FAILED!\n\n");
    }
    else
    	printf("TEST 2 SUCCEEDED!\n\n");
    
    // ----------- TEST 3: Testing adding 1 copper coin. --------------
    printf("TEST 3: Testing adding 1 copper coin.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    coinsBefore = 2;
    bonus = 0;
    testG.coins = coinsBefore;
    testG.handCount[thisPlayer] = 1; //add just the copper coin
    testG.hand[thisPlayer][0] = copper;
    updateCoins(thisPlayer, &testG, bonus);
    
    printf("coins = %d, expected = %d\n", testG.coins, copperCoin);
    if(testG.coins != copperCoin)
    {
    	printf("TEST 3 FAILED!\n\n");
    }
    else
    	printf("TEST 3 SUCCEEDED!\n\n");

    // ----------- TEST 4: Testing adding 1 silver coin. --------------
    printf("TEST 4: Testing adding 1 silver coin.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    coinsBefore = 1;
    bonus = 0;
    testG.coins = coinsBefore;
    testG.handCount[thisPlayer] = 1;
    testG.hand[thisPlayer][0] = silver;
    updateCoins(thisPlayer, &testG, bonus);

    printf("coins = %d, expected = %d\n", testG.coins, silverCoin);
    if(testG.coins != silverCoin)
    {
    	printf("TEST 4 FAILED!\n\n");
    }
    else
    	printf("TEST 4 SUCCEEDED!\n\n");

    // ----------- TEST 5: Testing adding 1 gold coin. --------------
    printf("TEST 4: Testing adding 1 gold coin.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    coinsBefore = 1;
    bonus = 0;
    testG.coins = coinsBefore;
    testG.handCount[thisPlayer] = 1;
    testG.hand[thisPlayer][0] = gold;
    updateCoins(thisPlayer, &testG, bonus);
    
     printf("coins = %d, expected = %d\n", testG.coins, goldCoin);
    if(testG.coins != goldCoin)
    {
    	printf("TEST 5 FAILED!\n\n");
    }
    else
    	printf("TEST 5 SUCCEEDED!\n\n");

    // ----------- TEST 6: Testing adding 1 copper, silver, gold, and bonus. --------------
    printf("TEST 6: Testing adding 1 copper, silver, gold, and bonus.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    coinsBefore = 1;
    bonus = 1;
    testG.coins = coinsBefore;
    testG.handCount[thisPlayer] = 4;
    
    int multCoins = copperCoin + silverCoin + silverCoin + goldCoin + bonus;
    testG.hand[thisPlayer][0] = copper;
    testG.hand[thisPlayer][1] = silver;
    testG.hand[thisPlayer][2] = gold;
    updateCoins(thisPlayer, &testG, bonus);
    
    printf("coins = %d, expected = %d\n", testG.coins, multCoins);
    if(testG.coins != multCoins)
    {
    	printf("TEST 6 FAILED!\n\n");
    }
    else
    	printf("TEST 6 SUCCEEDED!\n\n");
    
    printf("\n >>>>> Testing complete for %s <<<<<\n\n", TESTFUNC);
    
    return 0;
}