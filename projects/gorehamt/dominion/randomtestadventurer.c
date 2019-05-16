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

void testAdventurer(struct gameState *post){

    //create a struct to save the gamestate prior to the cardEffect function being called
    //and copy the current gamestate into that struct
    struct gameState pre;
    memcpy(&pre, post, sizeof(struct gameState));
    
    //create variables needed to call cardEffect, but not needed for the adventurer implementation
    int handPos = 2;
    int bonus = -1;
    int cardEffectResult;
    int player = post->whoseTurn;

    //call card effect function with the adventurer card using the randomly generated gamestate
    cardEffectResult = cardEffect(adventurer, -1, -1, -1, post, handPos, &bonus); 

    //check that the adventurer card was implemented correctly by comparing the pre and post states
    assert(post->handCount[player] == pre.handCount[player] + 2); //two treasure cards were added to the handcount

    //check that the cardEffect function returned without an error
    assert(cardEffectResult == 0);
}

int main(int argc, char *argv[]){
    //srand(time(NULL));

    //initialize variables
    int player;
    //create a gameState
    struct gameState G;
    
    printf("\n-----Random Testing of Adventurer Card-----\n");

    //begin randomization of gameState using the rngs.c functions
    //Reference: The code used below is based on the code in in the testDrawCard.c example file 
    //in the Dominion folder.
    SelectStream(2);
    PutSeed(3);

    int n; //number of times to run the random tester
    int i;
    for (n = 0; n < 2000; n++) { //TRACI--change this to a larger number later
        //fill the gameState with randomly generated input
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = floor(Random() * 256);
        }
        player = floor(Random() * 2);
        G.whoseTurn = player;
        G.deckCount[player] = floor(Random() * (MAX_DECK - 8)) + 8; //to ensure room for 7 coppers

        //need to add 7 coppers to the player's deck to work with the way adventurer code is written
        int k, j;
        for (k = 0; k < 7; k++){
            j = floor(Random() * G.deckCount[player]);
            G.deck[player][j] = copper;
        }
      
        G.discardCount[player] = floor(Random() * MAX_DECK);
        G.handCount[player] = floor(Random() * MAX_HAND);
        testAdventurer(&G);
    }

    printf ("ALL TESTS OK\n");

    return 0;
}
