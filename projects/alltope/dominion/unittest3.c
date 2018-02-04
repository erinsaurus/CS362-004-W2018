/* 
 Author: Erin Alltop
 Class: CS362 - Winter 2018
 Description: Assignment 3. unittest3

   TestinG fullDeckCount Function
   Expected results:
        - correct return when deck, hand, and discard counts are all 0
        - correct return when multiple cards in hand count
        - correct return when multiple cards in deck count+
        - no state changes to other players
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"

#define TESTFUNC "fullDeckCount"

int main(){
    struct gameState G, testG;
    
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    int numPlayers = 2;
    int thisplayer = 0;
    int seed = 1000;
    int count = 0;
    
    // initialize game state and thisplayer k
    initializeGame(numPlayers, k, seed, &G);
    
    printf("----------------- Testing Function: %s ----------------\n", TESTFUNC);
    
    // ----------- TEST 1: Testing full deck count when deck, hand, and discard count are 0. --------------
    printf("TEST 1: Testing full deck count when deck, hand, and discard count are 0.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[thisplayer] = 0;
    testG.handCount[thisplayer] = 0;
    testG.discardCount[thisplayer] = 0;
    count = fullDeckCount(thisplayer, estate, &testG);

    printf("Full deck count = %d, expected %d\n", count, 0);
    if(count != 0)
    {
        printf("TEST 1 FAILED!\n\n");
    }
    else
        printf("TEST 1 SUCCEEDED!\n\n");

    // ----------- TEST 2: Testing multiple of same cards in deck count --------------
    printf("TEST 2: Testing multiple of same cards in deck count.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[thisplayer] = 3;
    testG.handCount[thisplayer] = 0;
    testG.discardCount[thisplayer] = 0;
    testG.deck[thisplayer][0] = estate;
    testG.deck[thisplayer][1] = duchy;
    testG.deck[thisplayer][2] = estate;
    count = fullDeckCount(thisplayer, estate, &testG);
  
    printf("Full deck count = %d, expected = %d\n", count, 2);
    if(count != 2)
    {
        printf("TEST 2 FAILED!\n\n");
    }
    else
        printf("TEST 2 SUCCEEDED!\n\n");

    // ----------- TEST 3: Testing multiple of same cards in hand count --------------
    printf("TEST 3: Testing multiple of same cards in hand count.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.deckCount[thisplayer] = 0;
    testG.handCount[thisplayer] = 3;
    testG.discardCount[thisplayer] = 0;
    testG.hand[thisplayer][0] = estate;
    testG.hand[thisplayer][1] = duchy;
    testG.hand[thisplayer][2] = estate;
    count = fullDeckCount(thisplayer, estate, &testG);

    printf("Full hand count = %d, expected = %d\n", count, 2);
       if(count != 2)
    {
        printf("TEST 3 FAILED!\n\n");
    }
    else
        printf("TEST 3 SUCCEEDED!\n\n");
    
//-----------TEST 4: Other player states are unchanged--------------------
    printf("TEST 4: No state change in other players.\n");

    for(int i = 1; i < numPlayers; i++) //Checking discard count
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

    for(int i = 1; i < numPlayers; i++) //Checking deck count
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

    for(int i = 1; i < numPlayers; i++) //Checking hand count
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
    printf("\n >>>>> Testing complete for %s <<<<<\n\n", TESTFUNC);
    
    return 0;
}