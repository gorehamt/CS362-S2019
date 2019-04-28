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

    //get current hand size, number of buys, etc.
    int currentPHandSizeBefore = state.handCount[currentPlayer];
    int currentPNumBuysBefore = state.numBuys;
    int otherPHandSizeBefore = state.handCount[1];

    //play council_room card
    cardEffect(council_room, -1, -1, -1, &state, handPos, &bonus);

    //get hand size, num of buys, etc. after card is played
    int currentPHandSizeAfter = state.handCount[currentPlayer];
    int currentPNumBuysAfter = state.numBuys;
    int otherPHandSizeAfter = state.handCount[1];

    printf("\n------Testing Council Room Card Implementation------\n");

    /*Test 1: Verify that the current player receives exactly four cards.*/

    printf("\nTesting that current player's hand size increases by exactly 4 cards after council room card is played.\n");
    if (currentPHandSizeAfter == currentPHandSizeBefore + 3){ //3 because of discard.
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Hand size before was %d, and hand size after was %d\n", currentPHandSizeBefore, currentPHandSizeAfter);
    }

    /*Test 2: Verify that the current player receives exactly one more buy*/
    printf("\nTesting that current player's number of buys increases by exactly 1 after council room card is played.\n");
    if (currentPNumBuysAfter == currentPNumBuysBefore + 1){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Number of buys before was %d, and number of buys after was %d\n", currentPNumBuysBefore, currentPNumBuysAfter);
    }

    /*Test 3: Verify that the other players receives exactly one more card*/
    printf("\nTesting that the other player's number of cards increases by exactly 1 after council room card is played.\n");
    if (otherPHandSizeAfter == otherPHandSizeBefore + 1){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Number of cards in hand before was %d, and number of cards in hand after was %d\n", otherPHandSizeBefore, otherPHandSizeAfter);
    }

    return 0;
}

