/****************************************************************************************
* Unit Tests for fullDeckCount() function
* Written by: Traci Goreham, CS361
****************************************************************************************/

//include header files
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//include relevant libraries
#include <string.h>
#include <stdio.h>

int main(){

    //setup game
    int numPlayers = 2;
    struct gameState state;
    int seed = 1000;
    int kingdomCards[10] = {adventurer, great_hall, village, minion, steward, cutpurse, embargo, tribute, smithy, council_room};    

    initializeGame(numPlayers, kingdomCards, seed, &state);

    //add council_room card to first player's hand at position 2
    int player = 0;
    int handPos = 2; 
    int bonus = -1;
    state.hand[player][handPos] = council_room;
    cardEffect(council_room, -1, -1, -1, &state, handPos, &bonus);

    printf("\n------Testing Council Room Card Implementation------\n");

    /*Test 1: Verify that the current player receives exactly four cards.*/

/*
    printf("\nTesting when deck count = 0, hand count = 0, and discard count = 10.\n");
    if ((fullDeckCount(player, card, &state)) == 10){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Full deck count was not equal to 10.\n");
    }

  */ 

    return 0;
}

