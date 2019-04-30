/****************************************************************************************
* Unit Tests for adventurer card (for additional unit tests for adventurer card, 
* see unittest1.c)
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
    struct gameState state1;
    int seed = 1000;
    int kingdomCards[10] = {adventurer, great_hall, village, minion, steward, cutpurse, embargo, tribute, smithy, council_room};    

    //initialize three of the same game states
    initializeGame(numPlayers, kingdomCards, seed, &state1); //sets curse = 10, estate = 8, duchy = 8, provice = 8, copper = 46, silver = 40, gold = 30, all kingdom cards = 8

    //add adventurer card to first player's hand at position 2
    int currentPlayer = 0;
    int handPos = 2; 
    int bonus = -1;

    //remove all treasure cards from current player's hand
    int i;
    for (i = 0; i < state1.handCount[1]; i++){ 
        state1.hand[1][i] = estate; //change all cards to estates to ensure no treasure cards
    }
    //add adventurer card to the player's hand
    state1.hand[currentPlayer][handPos] = adventurer;

    //get current hand size, number of buys, etc. with state 1
    int currentPHandSizeBefore1 = state1.handCount[currentPlayer];
    int currentPDeckCountBefore1 = state1.deckCount[currentPlayer];
    int currentPDiscardCountBefore1 = state1.discardCount[currentPlayer];
    int otherPDeckCountBefore1 = state1.deckCount[1];
    int otherPHandCountBefore1 = state1.handCount[1];
    int otherPDiscardCountBefore1 = state1.discardCount[1];

    //play adventurer card
    cardEffect(adventurer, -1, -1, -1, &state1, handPos, &bonus);

    //get hand size, num of buys, etc. after card is played with state 1
    int currentPHandSizeAfter1 = state1.handCount[currentPlayer];
    int currentPDeckCountAfter1 = state1.deckCount[currentPlayer];
    int currentPDiscardCountAfter1 = state1.discardCount[currentPlayer];
    int otherPDeckCountAfter1 = state1.deckCount[1];
    int otherPHandCountAfter1 = state1.handCount[1];
    int otherPDiscardCountAfter1 = state1.discardCount[1];

    printf("\n------Testing Adventurer Card Implementation------\n");
    printf("\n------When there are not two treasure cards to add to player's hand------\n");

    /*Test 1: Verify that the current player does NOT add two cards to his/her hand.*/
    printf("\nTesting that current player's hand size does not increase because 2 treasure cards are not in the current player's hand).\n");
    if (currentPHandSizeAfter1 != currentPHandSizeBefore1 + 1){ 
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Hand size before was %d, and hand size after was %d\n", currentPHandSizeBefore1, currentPHandSizeAfter1);
    }

    /*Test 2: Verify that extra cards do not come from current player's pile*/
    printf("\nTesting that current player does not gain any extra cards in hand when adventurer card is played.\n");
    if (currentPDeckCountAfter1 == currentPDeckCountBefore1){ //this would mean that there was some change in the player's deck after the function was called
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Deck count before was %d, and deck count after was %d\n", currentPDeckCountBefore1, currentPDeckCountAfter1);
    }

    /*Test 3: Verify that no state changes occur for the other player*/
    printf("\nTesting that no state changes occur for the other player when playing adventurer card.\n");
    if ((otherPHandCountBefore1 == otherPHandCountAfter1) && (otherPDeckCountBefore1 == otherPDeckCountAfter1) && (otherPDiscardCountBefore1 == otherPDiscardCountAfter1)){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: The hand count, deck count, or discard count has changed for the other player.\n");
    }

    /*Test 4: Verify no state changes to victory or kingdom card piles*/
    printf("\nTesting that there are no state changes to the victory and kingdom card piles when adventurer card played.\n");
    if (checkSupplyCountSame(&state1, kingdomCards)){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: The supply count has changed for one or more kingdom cards or victory cards\n");
    }

    return 0;
}
