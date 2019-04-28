/****************************************************************************************
* Unit Tests for village card
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

    //add village card to first player's hand at position 2
    int currentPlayer = 0;
    int handPos = 2; 
    int bonus = -1;
    state.hand[currentPlayer][handPos] = village;

    //get current hand size, number of buys, etc.
    int currentPHandSizeBefore = state.handCount[currentPlayer];
    int currentPNumActionsBefore = state.numActions;
    int currentPDeckCountBefore = state.deckCount[currentPlayer];
    int otherPDeckCountBefore = state.deckCount[1];
    int otherPHandCountBefore = state.handCount[1];
    int otherPDiscardCountBefore = state.discardCount[1];

    //play village card
    cardEffect(village, -1, -1, -1, &state, handPos, &bonus);

    //get hand size, num of buys, etc. after card is played
    int currentPHandSizeAfter = state.handCount[currentPlayer];
    int currentPNumActionsAfter = state.numActions;
    int currentPDeckCountAfter = state.deckCount[currentPlayer];
    int otherPDeckCountAfter = state.deckCount[1];
    int otherPHandCountAfter = state.handCount[1];
    int otherPDiscardCountAfter = state.discardCount[1];

    printf("\n------Testing Village Card Implementation------\n");

    /*Test 1: Verify that the current player receives exactly one card.*/
    printf("\nTesting that current player's hand size increases by exactly 0 cards after village card is played (+1 b/c village played, -1 b/c village was discarded, for a total of 0 extra cards).\n");
    if (currentPHandSizeAfter == currentPHandSizeBefore){ 
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Hand size before was %d, and hand size after was %d\n", currentPHandSizeBefore, currentPHandSizeAfter);
    }

    /*Test 2: Verify that the current player receives exactly 2 more actions*/
    printf("\nTesting that current player's number of actions increases by exactly 2 after village card is played.\n");
    if (currentPNumActionsAfter == currentPNumActionsBefore + 2){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Number of actions before was %d, and number of actions after was %d\n", currentPNumActionsBefore, currentPNumActionsAfter);
    }

    /*Test 3: Verify that extra card comes from current player's pile*/
    printf("\nTesting that the extra cards come from current player's deck.\n");
    if (currentPDeckCountAfter == currentPDeckCountBefore - 1){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Deck count before was %d, and deck count after was %d\n", currentPDeckCountBefore, currentPDeckCountAfter);
    }

    /*Test 4: Verify that no state changes occur for the other player*/
    printf("\nTesting that no state changes occur for the other player.\n");
    if ((otherPHandCountBefore == otherPHandCountAfter) && (otherPDeckCountBefore == otherPDeckCountAfter) && (otherPDiscardCountBefore == otherPDiscardCountAfter)){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: The hand count, deck count, or discard count has changed for the other player.\n");
    }

    /*Test 5: Verify no state changes to victory or kingdom card piles*/
    printf("\nTesting that there are no state changes to the victory and kingdom card piles.\n");
    if (checkSupplyCountSame(&state, kingdomCards)){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: The supply count has changed for one or more kingdom cards or victory cards\n");
    }

    return 0;
}

