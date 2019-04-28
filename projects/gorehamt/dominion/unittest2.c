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
    int currentPlayer = 0;
    int handPos = 2; 
    int bonus = -1;
    state.hand[currentPlayer][handPos] = council_room;

    //get current hand size
    int p1HandSizeBefore = state.handCount[currentPlayer];

    //play council_room card
    cardEffect(council_room, -1, -1, -1, &state, handPos, &bonus);

    //get hand size after card is played
    int p1HandSizeAfter = state.handCount[currentPlayer];


    printf("\n------Testing Council Room Card Implementation------\n");

    /*Test 1: Verify that the current player receives exactly four cards.*/

    printf("\nTesting that current player's hand size increases by exactly 4 cards after council room card is played.\n");
    if ((p1HandSizeAfter == p1HandSizeBefore + 4){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Hand size before was % d, and hand size after was % d\n", p1HandSizeBefore, p1HandSizeAfter);
    }

    /*Test 2: Verify that the current playeer receives exactly one more buy*/

    return 0;
}

