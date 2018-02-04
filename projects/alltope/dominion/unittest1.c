/* 
 Author: Erin Alltop
 Class: CS362 - Winter 2018
 Description: Assignment 3. unittest1

   Testing isGameOver Function
   Expected results:
   		- if Province deck is empty -> game over
   		- if 3 supply decks are empty -> game over
   		- if 2 supply decks are empty and Province deck is not -> not game over
   		- if supply decks are not empty -> not game over
 */



#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define TESTFUNC "isGameOver"


int testGameOver(int prov, int sil, int duc, int est, struct gameState g, struct gameState testState)
{
    int k[10] = {feast, gardens, embargo, remodel, tribute, mine, cutpurse, ambassador, great_hall, village};
    initializeGame(2, k, 1000, &g);
    memcpy(&testState, &g, sizeof(struct gameState));
    testState.supplyCount[province] = prov;
    testState.supplyCount[silver] = sil;  
    testState.supplyCount[duchy] = duc;
    testState.supplyCount[estate] = est;
    int result = isGameOver(&testState);
    return result;
}


int main(){

  struct gameState g;     
  struct gameState testState;   // test game
  int result;

  printf("---------- Testing Function: %s ----------\n\n", TESTFUNC);
    

    // TEST 1 - IF THE PROVINCE DECK IS EMPTY -> GAME OVER
    result = testGameOver(0, 1, 1, 1, g, testState);
    printf("TEST 1: Province deck is empty (Game over).\n");
    printf("Expected: %d, Result: %d\n", 1, result);
    if(result == 1)
      printf("TEST 1 SUCCEEDED!\n\n");
    else
      printf("TEST 1 FAILED!\n\n");


    // TEST 2 - IF THREE SUPPLY DECKS ARE EMPTY - > GAME OVER
    result = testGameOver(1, 0, 0, 0, g, testState);
    printf("TEST 2: Three supply decks empty (Game over).\n");
    printf("Expected: %d, Result: %d\n", 1, result);
    if(result == 1)
      printf("TEST 2 SUCCEEDED!\n\n");
    else
      printf("TEST 2 FAILED!\n\n");

    // TEST 3 - IF TWO SUPPLY DECKS ARE EMPTY AND PROVINCE IS NOT -> NOT GAME OVER
  	result = testGameOver(1, 1, 0, 0, g, testState);

    printf("TEST 3: Two supply decks empty (Not game over).\n");
    printf("Expected: %d, Result: %d\n", 0, result);
    if(result == 0)
      printf("TEST 3 SUCCEEDED!\n\n");
    else
      printf("TEST 3 FAILED!\n\n");

    // TEST 4 - SUPPLY DECKS NOT EMPTY -> NOT GAME OVER
    result = testGameOver(1, 1, 1, 1, g, testState);

    printf("TEST 4: Supply decks not empty (Not game over).\n");
    printf("Expected: %d, Result: %d\n", 0, result);
    if(result == 0)
      printf("TEST 3 SUCCEEDED!\n\n");
    else
      printf("TEST 3 FAILED!\n\n");

  printf("\n >>>> Tesing complete for  %s<<<<\n\n", TESTFUNC);

  return 0;
}