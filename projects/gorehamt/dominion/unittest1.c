/****************************************************************************************
* Unit Tests for isGameOver() function
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
    int kingdomCards[10] = {adventurer, great_hall, village, minion, mine, cutpurse, embargo, tribute, smithy, council_room};    

    initializeGame(numPlayers, kingdomCards, seed, &state);

    printf("------Testing isGameOver function------\n");

    /*Test 1: Game is over because province supply is 0. */
    state.supplyCount[province] = 0; 
    printf("\nTesting when province supply is 0.\n");
    if ((isGameOver(&state)) == 1){
        printf("TEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("TEST FAILED: Game was not over even though province supply was 0.\n");
    }

    /*Test 2: Game is over because 3 supply piles have 0 cards */

    /*Test 3: Game is not over because provice supply > 0 and < 3 supply piles have 0 cards */




    return 0;
}

