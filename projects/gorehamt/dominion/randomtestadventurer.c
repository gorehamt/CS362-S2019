/***********************************************************************************
 *  Name: Traci Goreham
 *  Class: CS362, Assignment 4, Random Tester
 *  Reference: The code used to generate the random tester for this assignment is 
 *  based on the code in the testDrawCard.c example file in the Dominion folder. 
 * *********************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h> //floor
#include "rngs.h"

/***********************************************************************************
 * Function Name: generateRandomNumber
 * Function Description: This function generates a random number within a given 
 * range. It takes two integers as parameters, the lower limit and the upper limit
 * of the range.
 * *********************************************************************************/
/*int generateRandomNumber(int lowerLimit, int upperLimit){
    int randomNum;
    return randomNum = rand() % ((upperLimit - lowerLimit + 1) + lowerLimit);
}
*/

void testAdventurer(int player, struct gameState *G){
    
    int handPos = 2;
    //call card effect function with the adventurer card using the randomly generated inputs
    cardEffect(adventurer, -1, -1, -1, &G, handPos, -1); //no choices or bonus for adventurer, thus -1

}

int main(int argc, char *argv[]){
    //srand(time(NULL));

    //initialize variables
    int player, deckCount, discardCount, handCount;
    //initialize cards
    int k[10] = {adventurer, great_hall, village, minion, steward, cutpurse, embargo, tribute, smithy, council_room};
    //create a gameState
    struct gameState G;

    printf("\n-----Random Testing of Adventurer Card-----\n");

    //begin randomization of gameState using the rngs.c functions
    SelectStream(2);
    PutSeed(3);

    int n; //number of times to run the random tester
    int i;
    for (n = 0; n < 2; n++) { //TRACI--change this to a larger number later
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        player = floor(Random() * 2);
        G.deckCount[player] = floor(Random() * MAX_DECK);
        G.discardCount[player] = floor(Random() * MAX_DECK);
        G.handCount[player] = floor(Random() * MAX_HAND);
        testAdventurer(player, &G);
    }

    printf ("ALL TESTS OK\n");

    return 0;
}
