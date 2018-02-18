/* 
 Author: Erin Alltop
 Class: CS362 - Winter 2018
 Description: Assignment 4. randomtestcard1

   Testing Great Hall Card
   Expected results:
   		- Current player receives 1
   			- Deck count decreased by 1
   			- Hand count increased by 1
   		- Current player receives 1 action
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
#define NUM_TESTS 8
#define TESTCARD "Great Hall"
char failedTests[NUM_TESTS][256]; // this is an array to hold strings of which tests have failed

int main()
{
	int handpos = 0, choice1 = -1, choice2 = -1, choice3 = -1, bonus = 0;
    int seed, thisPlayer, numPlayers;
    int failures = 0; // total failures
    int successes = 0; // total successes
    struct gameState G, testG;
    int k[10] = {great_hall, gardens, embargo, village, minion, mine, cutpurse, 
           sea_hag, tribute, smithy};
    srand(time(NULL)); // get random seed
    int failureIter = 0; // tracks number of failed tests

    printf("------------------- Random Tests - Testing Card: %s ------------------\n\n", TESTCARD);

    for(int i = 0; i < NUM_ITER; i++)
    {

		// seed and initialize a random game with random values
    	seed = rand();
    	numPlayers = MAX_PLAYERS;//(rand() % (4 - 2) + 2);
    	initializeGame(numPlayers, k, seed, &G);
    	thisPlayer = rand() % numPlayers;
    	G.whoseTurn = thisPlayer;
    	bonus = rand() % 50;
    	choice1 = rand() % 50;
    	choice2 = rand() % 50;
    	choice3 = rand() % 50;
    	handpos = rand() % MAX_HAND;
    	int result = 0;

    	memcpy(&testG, &G, sizeof(struct gameState)); // copy game state for comparison

    	cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus); //call cardEffect

    	//-------------TEST 1: One card is drawn by the current player ----------
    	if(testG.handCount[thisPlayer] != (G.handCount[thisPlayer] + 0)) // draw 1 discard 1
		{
			result = 0;
            	for(int i = 0; i < NUM_TESTS; i++)
                	{
                    	if(strncmp(failedTests[i], "Player drew one card", 255) == 0)
                    {
                        result = 1;
                    }
                }
            	if(result == 0)
            	{
                	strcpy(failedTests[failureIter], "Player drew one card");
                	failureIter++;
            	}
            	failures++;
		}
		else successes++;

		//-------------TEST 2: One card is drawn from the current player's deck ----------
        if(testG.deckCount[thisPlayer] != (G.deckCount[thisPlayer] - 1))
        {
            result = 0;
            for(int i = 0; i < NUM_TESTS; i++)
                {
                    if(strncmp(failedTests[i], "Card comes from correct deck", 255) == 0)
                    {
                        result = 1;
                    }

                }
            if(result == 0)
            {
                strcpy(failedTests[failureIter], "Card comes from correct deck");
                failureIter++;
            }
            failures++;
        }
        else successes++;

        //-------------TEST 3: Player obtains one additional action ----------
        if(testG.numActions != G.numActions + 1)
        {
            result = 0;
            for(int i = 0; i < NUM_TESTS; i++)
                {
                    if(strncmp(failedTests[i], "Number of actions increased by 1", 255) == 0)
                    {
                        result = 1;
                    }

                }
            if(result == 0)
            {
                strcpy(failedTests[failureIter], "Number of actions increased by 1");
                failureIter++;
            }
            failures++;
        }
        else successes++;

        //-------------TEST 4: Player obtains no bonus coins ----------
        if(testG.coins != (G.coins + 0))
        {
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

         //-------------TEST 5: Other players discard count unchanged ----------
        for(int i = 1; i < numPlayers; i++) 
        {
            if(testG.discardCount[i] != G.discardCount[i])
            {
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

        //-------------TEST 6: Other players hand counts unchanged ----------
        for(int i = 1; i < numPlayers; i++) 
        {   
            if(testG.handCount[i] != G.handCount[i])
            {
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

        //-------------TEST 7: Victory cards are unchanged ----------
        if((testG.supplyCount[estate] + testG.supplyCount[duchy] + testG.supplyCount[province]) !=
        (G.supplyCount[estate] + G.supplyCount[duchy] + G.supplyCount[province]))
        {
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

        //-------------TEST 8: Kingdom cards are unchanged ----------
        int testKingCards = (testG.supplyCount[adventurer] + testG.supplyCount[embargo] + testG.supplyCount[village] + testG.supplyCount[minion]
        + testG.supplyCount[mine] + testG.supplyCount[cutpurse] + testG.supplyCount[sea_hag] + testG.supplyCount[tribute]
        + testG.supplyCount[smithy] + testG.supplyCount[council_room]);

        int gKingCards = (G.supplyCount[adventurer] + G.supplyCount[embargo] + G.supplyCount[village] + G.supplyCount[minion]
        + G.supplyCount[mine] + G.supplyCount[cutpurse] + G.supplyCount[sea_hag] + G.supplyCount[tribute]
        + G.supplyCount[smithy] + G.supplyCount[council_room]);

        if(testKingCards != gKingCards)
        {
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

	// Print out test results
	printf("     -----------------------------------------------------------------\n");
    printf("                        %s Test Results:                              \n", TESTCARD);
    printf("                        Number of tests: %d                           \n", NUM_TESTS);
    printf("                        Number of iterations: %d                      \n", NUM_ITER);
    printf("                        %d successes, %d failures                     \n\n", successes, failures);
    printf("                        Tests failed:                                 \n");
  

    // Loop through the failedTests array to print out which tests have failed
    if(failureIter == 0) // if failureIter is 0, no tests failed
    {
        printf("                        None\n");
    }
    for(int i = 0; i < failureIter; i++)
    {
        printf("                        %s\n", failedTests[i]);
    }
    printf("     -----------------------------------------------------------------\n\n");
    printf("-------------------- %s Testing Complete ----------------------------\n", TESTCARD);

	return 0;
}