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

/*****************************************************************************************************************************************
 * Function name: checkSupplyCountSame
 * Description: This function returns 1 if there is a change to the supply count for one of the kingdom cards or one of the victory cards. 
 * It returns 0 if there are no changes.
******************************************************************************************************************************************/
int checkSupplyCountSame (struct gameState *state, int kingdomCards[10]){
    //NOTE: initialize game sets sets curse = 10, estate = 8, duchy = 8, provice = 8, copper = 46, silver = 40, gold = 30, all kingdom cards = 8

    //verify the kingdomCards counts have not changed
    int i;
    for (i = 0; i < 10; i++){
        if(state->supplyCount[kingdomCards[i]] != 8){
            return 1; //state of a kingdom card changed
        }
    }

    //verify the victory card piles have not changed
    if ((state->supplyCount[estate] != 8) || (state->supplyCount[duchy] != 8) || (state->supplyCount[province] != 8)){
        return 1;
    }

    return 0;
}


int main(){

    //setup game
    int numPlayers = 2;
    struct gameState state;
    int seed = 1000;
    int kingdomCards[10] = {adventurer, great_hall, village, minion, steward, cutpurse, embargo, tribute, smithy, council_room};    

    initializeGame(numPlayers, kingdomCards, seed, &state); //sets curse = 10, estate = 8, duchy = 8, provice = 8, copper = 46, silver = 40, gold = 30, all kingdom cards = 8

    //add council_room card to first player's hand at position 2
    int currentPlayer = 0;
    int handPos = 2; 
    int bonus = -1;
    state.hand[currentPlayer][handPos] = council_room;

    //get current hand size, number of buys, etc.
    int currentPHandSizeBefore = state.handCount[currentPlayer];
    int currentPNumBuysBefore = state.numBuys;
    int otherPHandSizeBefore = state.handCount[1];
    int currentPDeckCountBefore = state.deckCount[currentPlayer];
    int otherPDeckCountBefore = state.deckCount[1];

    //play council_room card
    cardEffect(council_room, -1, -1, -1, &state, handPos, &bonus);

    //get hand size, num of buys, etc. after card is played
    int currentPHandSizeAfter = state.handCount[currentPlayer];
    int currentPNumBuysAfter = state.numBuys;
    int otherPHandSizeAfter = state.handCount[1];
    int currentPDeckCountAfter = state.deckCount[currentPlayer];
    int otherPDeckCountAfter = state.deckCount[1];

    printf("\n------Testing Council Room Card Implementation------\n");

    /*Test 1: Verify that the current player receives exactly four cards.*/

    printf("\nTesting that current player's hand size increases by exactly 3 cards after council room card is played (+4 b/c council room played, -1 b/c council room was discarded, for a total of 3 extra cards).\n");
    if (currentPHandSizeAfter == currentPHandSizeBefore + 3){ //3 because of discard
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

    /*Test 4: Verify that cards come from current player's pile*/
    printf("\nTesting that the extra cards come from current player's deck.\n");
    if (currentPDeckCountAfter == currentPDeckCountBefore - 4){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Deck count before was %d, and deck count after was %d\n", currentPDeckCountBefore, currentPDeckCountAfter);
    }

    /*Test 5: Verify that the extra card come from other player's pile*/
    printf("\nTesting that the extra card come from the other player's deck.\n");
    if (otherPDeckCountAfter == otherPDeckCountBefore - 1){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Deck count before was %d, and deck count after was %d\n", otherPDeckCountBefore, otherPDeckCountAfter);
    }


    /*Test 6: Verify no state changes to victory or kingdom card piles*/
    printf("\nTesting that there are no state changes to the victory and kingdom card piles.\n")
    if (checkSupplyCountSame(&state, kingdomCards)){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: The supply count has changed for one or more kingdom cards or victory cards\n");
    }

    return 0;
}

