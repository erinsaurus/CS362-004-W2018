/* 
 Author: Erin Alltop
 Class: CS362 - Winter 2018
 Description: Assignment 5. randomtestadventurer

   Testing Adventurer Card
   Expected results:
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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "rngs.h"

// Global allows different values to be easily tested
#define NUM_ITER 1000
#define NUM_TESTS 10
#define TESTCARD "Adventurer"
char failedTests[NUM_TESTS][256]; // this is an array to hold strings of which tests have failed


int main () 
{
    int handpos = 0, choice1 = -1, choice2 = -1, choice3 = -1, bonus = 0;
    int seed;
    int thisPlayer;
    int failures = 0; // total failures
    int successes = 0; // total successes
    struct gameState G, testG;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
    srand(time(NULL)); // get random seed
    int failureIter = 0; // tracks number of failed tests


    printf("------------------- Random Tests - Testing Card: %s ------------------\n\n", TESTCARD);

    
    
    for(int i = 0; i < NUM_ITER; i++)
    {
        // seed and initialize a random game with random values
        seed = rand();
        initializeGame(MAX_PLAYERS, k, seed, &G);
        thisPlayer = rand() % MAX_PLAYERS;
        G.whoseTurn = thisPlayer;
        bonus = rand() % 50;
        choice1 = rand() % 50;
        choice2 = rand() % 50;
        choice3 = rand() % 50;
        handpos = rand() % MAX_HAND;
        int result = 0;

        memcpy(&testG, &G, sizeof(struct gameState)); // copy game state for comparison

        cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

        // Testing to see if the hand count of current player has drawn two cards
        if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + 2)
        {
            //printf("TEST FAILED: Player %d didn't draw 2 cards.\n", thisPlayer);
            result = 0;
            for(int i = 0; i < NUM_TESTS; i++)
                {
                    if(strncmp(failedTests[i], "Player drew two cards", 255) == 0)
                    {
                        result = 1;
                    }

                }
            if(result == 0)
            {
                strcpy(failedTests[failureIter],"Player drew two cards");
                failureIter++;
            }
            failures++;
        }
        else successes++;

        // Testing to see if the cards drawn are from the current player's deck
        if(testG.deckCount[thisPlayer] != (G.deckCount[thisPlayer] - 2))
        {
           // printf("TEST FAILED: cards did not come from current player's deck.\n\n");
            result = 0;
            for(int i = 0; i < NUM_TESTS; i++)
                {
                    if(strncmp(failedTests[i], "Cards come from correct deck", 255) == 0)
                    {
                        result = 1;
                    }

                }
            if(result == 0)
            {
                strcpy(failedTests[failureIter], "Cards come from correct deck");
                failureIter++;
            }
            failures++;
        }
        else successes++;

        // Testing to see if player received any bonus coins (should not)
        if(testG.coins != (G.coins + 0))
        {
           // printf("TEST FAILED: Bonus coins received. Should have been 0.\n\n");
            result = 0;
            for(int i = 0; i < NUM_TESTS; i++)
                {
                    if(strncmp(failedTests[i], "No bonus coins received", 255) == 0)
                    {
                        result = 1;
                    }

                }
            if(result == 0)
            {
                strcpy(failedTests[failureIter], "No bonus coins received");
                failureIter++;
            }
            failures++;
        } 
        else successes++;

        // Testing to see if first card drawn is a treasure card
        int cardDrawn1 = testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1];
        if(cardDrawn1 != copper && cardDrawn1 != silver && cardDrawn1 != gold)
        {
          //  printf("TEST FAILED: Player %d's newest card isn't money.\n", thisPlayer);
            result = 0;
            for(int i = 0; i < NUM_TESTS; i++)
                {
                    if(strncmp(failedTests[i], "First drawn card is treasure", 255) == 0)
                    {
                        result = 1;
                    }

                }
            if(result == 0)
            {
                strcpy(failedTests[failureIter], "First drawn card is treasure");
                failureIter++;
            }
            failures++;
        }
        else successes++;

        // Testing to see if the second card drawn is a treasure card
        int cardDrawn2 = testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2];
        if(cardDrawn2 != copper && cardDrawn2 != silver && cardDrawn2 != gold)
        {
           // printf("TEST FAILED: Player %d's second newest card isn't money.\n", thisPlayer);
            result = 0;
            for(int i = 0; i < NUM_TESTS; i++)
                {
                    if(strncmp(failedTests[i], "Second drawn card is treasure", 255) == 0)
                    {
                        result = 1;
                    }

                }
            if(result == 0)
            {
                strcpy(failedTests[failureIter], "Second drawn card is treasure");
                failureIter++;
            }
            failures++;
        }
        else successes++;

        // Testing that other player states are unchanged
        for(int i = 1; i < MAX_PLAYERS; i++) //Checking discard count
        {
            if(testG.discardCount[i] != G.discardCount[i])
            {
               // printf("TEST FAILED! player %d's dicard count has changed.\n\n", i);
            result = 0;
            for(int i = 0; i < NUM_TESTS; i++)
                {
                    if(strncmp(failedTests[i], "Other players discard counts not changed", 255) == 0)
                    {
                        result = 1;
                    }

                }
            if(result == 0)
            {
                strcpy(failedTests[failureIter], "Other players discard counts not changed");
                failureIter++;
            }
                failures++;
            }
            else successes++;
        }

        for(int i = 1; i < MAX_PLAYERS; i++) //Checking deck count
        {
            if(testG.deckCount[i] != G.deckCount[i])
            {
               // printf("TEST FAILED! player %d's deck count has changed.\n\n", i);
                result = 0;
                for(int i = 0; i < NUM_TESTS; i++)
                {
                    if(strncmp(failedTests[i], "Other players deck counts not changed", 255) == 0)
                    {
                        result = 1;
                    }

                }
            if(result == 0)
            {
                strcpy(failedTests[failureIter], "Other players deck counts not changed");
                failureIter++;
            }
                failures++;
            }
            else successes++;
        }

        for(int i = 1; i < MAX_PLAYERS; i++) //Checking hand count
        {   
            if(testG.handCount[i] != G.handCount[i])
            {
               // printf("TEST FAILED! player %d's hand count has changed.\n\n", i);
                result = 0;
                for(int i = 0; i < NUM_TESTS; i++)
                {
                    if(strncmp(failedTests[i], "Other players hand counts not changed", 255) == 0)
                    {
                        result = 1;
                    }

                }
            if(result == 0)
            {
                strcpy(failedTests[failureIter], "Other players hand counts not changed");
                failureIter++;
            }
                failures++;
            }
            else successes++;
        }


        // Testing that there were no state changes to Victory cards
        if((testG.supplyCount[estate] + testG.supplyCount[duchy] + testG.supplyCount[province]) !=
        (G.supplyCount[estate] + G.supplyCount[duchy] + G.supplyCount[province]))
        {
           // printf("TEST FAILED: Victory cards have changed.\n\n");
            result = 0;
            for(int i = 0; i < NUM_TESTS; i++)
            {
                if(strncmp(failedTests[i], "Victory cards have not changed", 255) == 0)
                {
                      result = 1;
                }

            }
            if(result == 0)
            {
                strcpy(failedTests[failureIter], "Victory cards have not changed");
                failureIter++;
            }
            failures++;
        }
        else successes++;

        //Testing that there were no state changes to Kingdom Cards
        int testKingCards = (testG.supplyCount[adventurer] + testG.supplyCount[embargo] + testG.supplyCount[village] + testG.supplyCount[minion]
        + testG.supplyCount[mine] + testG.supplyCount[cutpurse] + testG.supplyCount[sea_hag] + testG.supplyCount[tribute]
        + testG.supplyCount[smithy] + testG.supplyCount[council_room]);

        int gKingCards = (G.supplyCount[adventurer] + G.supplyCount[embargo] + G.supplyCount[village] + G.supplyCount[minion]
        + G.supplyCount[mine] + G.supplyCount[cutpurse] + G.supplyCount[sea_hag] + G.supplyCount[tribute]
        + G.supplyCount[smithy] + G.supplyCount[council_room]);

        if(testKingCards != gKingCards)
        {
           // printf("TEST FAILED: Kingdom cards have changed.\n\n");
            result = 0;
            for(int i = 0; i < NUM_TESTS; i++)
            {
                if(strncmp(failedTests[i], "Kingdom cards have not changed", 255) == 0)
                {
                      result = 1;
                }

            }
            if(result == 0)
            {
                strcpy(failedTests[failureIter], "Kingdom cards have not changed");
                failureIter++;
            }
            failures++;
        }
        else successes++;
    }


    printf("     -----------------------------------------------------------------\n");
    printf("                        %s Test Results:                              \n", TESTCARD);
    printf("                        Number of tests: %d                           \n", NUM_TESTS);
    printf("                        Number of iterations: %d                      \n", NUM_ITER);
    printf("                        %d successes, %d failures                     \n\n", successes, failures);
    printf("                        Tests failed:                                 \n");
  

    // Loop through the failedTests array to print out which tests have failed
    if(failureIter == 0) // if failureIter is 0, no tests failed
    {
        printf("None\n");
    }
    for(int i = 0; i < failureIter; i++)
    {
        printf("                        %s\n", failedTests[i]);
    }
    printf("     -----------------------------------------------------------------\n\n");
    printf("-------------------- %s Testing Complete ----------------------------\n", TESTCARD);


 
}
