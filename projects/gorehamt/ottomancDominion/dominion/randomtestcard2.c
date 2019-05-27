/***********************************************************************************
 *  Name: Traci Goreham
 *  Class: CS362, Assignment 4, Random Tester for Great Hall
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

void testGreatHall(struct gameState *post){

    //create a struct to save the gamestate prior to the cardEffect function being called
    //and copy the current gamestate into that struct
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));
    
    //create variables needed to call cardEffect
    int handPos = 0;
    int bonus = -1;
    int cardEffectResult;
    int player = post->whoseTurn; //assign player to the current player whose turn it is
    post->hand[player][handPos] = great_hall; //put the great hall card in the player's hand

    //call card effect function with the great hall card using the randomly generated gamestate
    cardEffectResult = cardEffect(great_hall, -1, -1, -1, post, handPos, &bonus); 
    
    //check that the great_hall card was implemented correctly by comparing the pre and post states
    assert(post->handCount[player] == pre.handCount[player]); //one card added to handcount but great_hall card discarded
    assert(post->numActions == pre.numActions + 1); //one action added
    
    //check that the cardEffect function returned without an error
    assert(cardEffectResult == 0);
}

int main(int argc, char *argv[]){
    //srand(time(NULL));

    //initialize variables
    int player;
    //create a gameState
    struct gameState G;
    
    printf("\n-----Random Testing of Great Hall Card-----\n");

    //begin randomization of gameState using the rngs.c functions
    //Reference: The code used below is based on the code in in the testDrawCard.c example file 
    //in the Dominion folder.
    SelectStream(2);
    PutSeed(3);

    int n; //number of times to run the random tester
    int i;
    for (n = 0; n < 2000; n++) { 
        //fill the gameState with randomly generated input
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        player = floor(Random() * 2);
        G.whoseTurn = player;
        G.deckCount[player] = floor(Random() * MAX_DECK);
        G.discardCount[player] = floor(Random() * MAX_DECK);
        G.handCount[player] = floor(Random() * MAX_HAND);
        G.playedCardCount = 0; //initialize played card count to 0 per how the game is initialized in dominion.c
        G.numActions = 1; //1 per the specifications of the dominion.h file
        testGreatHall(&G);
    }

    printf ("ALL TESTS OK\n");

    return 0;
}
