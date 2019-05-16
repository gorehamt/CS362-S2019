/***********************************************************************************
 *  Name: Traci Goreham
 *  Class: CS362, Assignment 4, Random Tester for Village Card
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

void testVillage(struct gameState *post){

    printf("In Village: A\n");
    //create a struct to save the gamestate prior to the cardEffect function being called
    //and copy the current gamestate into that struct
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));
    printf("In Village: B\n");
    
    //create variables needed to call cardEffect
    int handPos = 0;
    int bonus = -1;
    int cardEffectResult;
    printf("In Village: C\n");
    int player = post->whoseTurn; //assign player to the current player whose turn it is
    post->hand[player][handPos] = village; //put the village card in the player's hand
    
printf("In Village: D\n");
    //call card effect function with the village card using the randomly generated gamestate
    cardEffectResult = cardEffect(village, -1, -1, -1, post, handPos, &bonus); 
printf("In Village: E\n");
    //check that the village card was implemented correctly by comparing the pre and post states
    assert(post->handCount[player] == pre.handCount[player] + 1); //one card added to handcount
    printf("In Village: F\n");
    assert(post->numActions == pre.numActions + 2); //two actions were added
    printf("In Village: G\n");
    //check that the cardEffect function returned without an error
    assert(cardEffectResult == 0);

    printf("In Village: H\n");
}

int main(int argc, char *argv[]){
    //srand(time(NULL));

    //initialize variables
    int player;
    //create a gameState
    struct gameState G;
    
    printf("\n-----Random Testing of Village Card-----\n");

    //begin randomization of gameState using the rngs.c functions
    //Reference: The code used below is based on the code in in the testDrawCard.c example file 
    //in the Dominion folder.
    SelectStream(2);
    PutSeed(3);

    printf("In main: 1\n");

    int n; //number of times to run the random tester
    int i;
    for (n = 0; n < 1; n++) { 
        //fill the gameState with randomly generated input
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        printf("In main: 2\n");
        player = floor(Random() * 2);
        G.whoseTurn = player;
        printf("In main: 3\n");
        G.deckCount[player] = floor(Random() * MAX_DECK);
        G.discardCount[player] = floor(Random() * MAX_DECK);
        G.handCount[player] = floor(Random() * MAX_HAND);
        printf("In main: 4\n");
        G.numActions = 1; //1 per the specifications of the dominion.h file
        printf("In main: 5\n");
        testVillage(&G);
        printf("In main: 6\n");
    }

    printf ("ALL TESTS OK\n");

    return 0;
}
