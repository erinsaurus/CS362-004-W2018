/* 
 Author: Erin Alltop
 Class: CS362 - Winter 2018
 Description: Assignment 3. unittest4

   TestinG gainCard Function
   Expected results:
        - if toFlag set to 0, card added to discard 
        - if toFlag set to 1, card added to deck
        - if toFlag set to 2, card added to hand
        - No changes to other player states
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "rngs.h"

#define TESTFUNC "gainCard"

int main(){
    struct gameState G, testG;

    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
        sea_hag, tribute, smithy, council_room};
    int numPlayers = 2;
    int thisplayer = 0;
    int seed = 1000;
    int supplyPos = 1;
    
  //added card for [whoseTurn] current player:
  // toFlag = 0 : add to discard
  // toFlag = 1 : add to deck
  // toFlag = 2 : add to hand
    int toFlag = 1;

    // initialize game state and player cards
    initializeGame(numPlayers, k, seed, &G);
    
    printf("----------------- Testing Function: %s ----------------\n", TESTFUNC);
    
    // ----------- TEST 1: Pile is empty -> cannot add a card --------------
    
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.supplyCount[supplyPos] = 0; 
    printf("TEST 1: Attempting to add a card when pile is empty.\n");
    int result = gainCard(supplyPos, &testG, toFlag, thisplayer);
    if(result != -1)
    {
      printf ("TEST 1 FAILED!\n\n");
    }
    else
      printf("TEST 1 SUCCEEDED!\n\n");

    // ----------- TEST 2: Add card to deck --------------
    printf("TEST 2: Add a card to the deck.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.supplyCount[supplyPos] = 1;
    int deckCountBefore = testG.deckCount[thisplayer];
    gainCard(supplyPos, &testG, 1, thisplayer); // toFlag = 1
  
    printf("deck count = %d, expected = %d\n", testG.deckCount[thisplayer], deckCountBefore + 1);
    
    if(testG.deckCount[thisplayer] != deckCountBefore + 1)
     {
      printf ("TEST 2 FAILED!\n\n");
    }
    else
      printf("TEST 2 SUCCEEDED!\n\n");

    
    // ----------- TEST 3: Add card to hand --------------
    printf("TEST 2: Add a card to the hand.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.supplyCount[supplyPos] = 1;
    int handCountBefore = testG.handCount[thisplayer];
    gainCard(supplyPos, &testG, 2, thisplayer); //toFlag = 2
  
    printf("hand count = %d, expected = %d\n", testG.handCount[thisplayer], handCountBefore + 1);
   
    if(testG.handCount[thisplayer] != handCountBefore + 1)
    {
      printf ("TEST 3 FAILED!\n\n");
    }
    else
      printf("TEST 3 SUCCEEDED!\n\n");
    
    // ----------- TEST 4: Add card to discard --------------
        printf("TEST 4: Add card to discard pile.\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.supplyCount[supplyPos] = 1;
    int discardCountBefore = testG.discardCount[thisplayer];
    gainCard(supplyPos, &testG, 0, thisplayer); //toFlag = 0

    printf("discard count = %d, expected = %d\n", testG.discardCount[thisplayer], discardCountBefore + 1);

    if(testG.discardCount[thisplayer] != discardCountBefore + 1)
    {
      printf ("TEST 4 FAILED!\n\n");
    }
    else
      printf("TEST 4 SUCCEEDED!\n\n");

//-----------TEST 5: Other player states are unchanged--------------------
    printf("TEST 5: No state change in other players.\n");

    for(int i = 1; i < numPlayers; i++) //Checking discard count
    {
        printf("Discard count expected for other player %d:\n", i);
        printf("count = %d, expected = %d\n", testG.discardCount[i], G.discardCount[i]);

        if(testG.discardCount[i] != G.discardCount[i])
        {
        printf("TEST 5 FAILED! DISCARD COUNT CHANGED\n\n");
    }
    else
        printf("TEST 5 DISCARD COUNT SUCCEEDED!\n\n");
    }

    for(int i = 1; i < numPlayers; i++) //Checking deck count
    {
        printf("Deck count expected for other player %d:\n", i);
        printf("count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);

        if(testG.deckCount[i] != G.deckCount[i])
        {
        printf("TEST 5 FAILED! DECK COUNT CHANGED\n\n");
    }
    else
        printf("TEST 5 DECK COUNT SUCCEEDED!\n\n");
    }

    for(int i = 1; i < numPlayers; i++) //Checking hand count
    {
        printf("Hand count expected for other player %d:\n", i);
        printf("count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);

        if(testG.handCount[i] != G.handCount[i])
        {
        printf("TEST 5 FAILED! HAND COUNT CHANGED\n\n");
    }
    else
        printf("TEST 5 HAND COUNT SUCCEEDED!\n\n");
    }
    
    printf("\n >>>>> Testing complete for %s <<<<<\n\n", TESTFUNC);

    return 0;

  }