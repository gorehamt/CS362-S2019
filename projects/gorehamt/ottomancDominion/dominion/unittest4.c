/****************************************************************************************
* Unit Tests for cutpurse card
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
    struct gameState state1, state2;
    int seed = 1000;
    int kingdomCards[10] = {adventurer, great_hall, village, minion, steward, cutpurse, embargo, tribute, smithy, council_room};    

    //initialize two of the same game states
    initializeGame(numPlayers, kingdomCards, seed, &state1); //sets curse = 10, estate = 8, duchy = 8, provice = 8, copper = 46, silver = 40, gold = 30, all kingdom cards = 8
    initializeGame(numPlayers, kingdomCards, seed, &state2);

    //Moved draw cards for second player
    int it;
    for (it = 0; it < 5; it++){
        drawCard(1, &state1);
    }

    for (it = 0; it < 5; it++){
        drawCard(1, &state2);
    }

    //add cutpurse card to first player's hand at position 2 of both game states
    int currentPlayer = 0;
    int handPos = 2; 
    int bonus = -1;
    state1.hand[currentPlayer][handPos] = cutpurse;
    state2.hand[currentPlayer][handPos] = cutpurse;

    //remove all coppers from other player's hand in state 1
    int i;
    for (i = 0; i < state1.handCount[1]; i++){ 
        state1.hand[1][i] = silver; //change all cards to silvers to ensure no coppers
    }
    //add a copper to other player's hand in state 1
    state1.hand[1][1] = copper;

    //remove all coppers from other player's hand in state 2
    for (i = 0; i < state2.handCount[1]; i++){ 
        state2.hand[1][i] = silver; //change all cards to silvers to ensure no coppers
    }

    /*---state 1: other player has a copper in his/her hand---*/
    //get current players coins, and other players hand count and discard count before
    int currentPCoinsBefore1 = state1.coins;
    int otherPHandCountBefore1 = state1.handCount[1];
    int otherPDiscardCountBefore1 = state1.discardCount[1];

    //play cutpurse card with state 1
    cardEffect(cutpurse, -1, -1, -1, &state1, handPos, &bonus);

    //get current players coins, and other players hand count and discard count after
    int currentPCoinsAfter1 = state1.coins;
    int otherPHandCountAfter1 = state1.handCount[1];
    int otherPDiscardCountAfter1 = state1.discardCount[1];

    printf("\n------Testing Cutpurse Card Implementation------\n");

    /*Test 1: Verify that the current player receives exactly 2 more coins*/
    printf("\nTesting that current player's number of coins increases by exactly 2 when playing cutpurse card.\n");
    if (currentPCoinsAfter1 == currentPCoinsBefore1 + 2){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Number of coins before was %d, and number of coins after was %d\n", currentPCoinsBefore1, currentPCoinsAfter1);
    }

    /*Test 2: If other player has copper in hand, verify that there is one less cards in hand after the cutpurse card is played (a copper is discarded)*/
    printf("\nTesting that there is one less cards in the other player's hand if copper is present in hand and cutpurse card is played (b/c discarded a copper).\n");
    if (otherPHandCountAfter1 == otherPHandCountBefore1 - 1){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Copper was not discarded because hand count before was %d, and hand count after was %d\n", otherPHandCountBefore1, otherPHandCountAfter1);
    }

    /*Test 3: Verify that the discarded copper is not in the player's discard pile because it should no longer be part of the players full deck of cards*/
    printf("\nTesting that the discarded copper is not in current player's discard pile (this card is no longer part of player's hand) when playing cutpurse card.\n");
    if (otherPDiscardCountAfter1 == otherPDiscardCountBefore1){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Discard count before was %d, and discard count after was %d\n", otherPDiscardCountBefore1, otherPDiscardCountAfter1);
    }


    /*---state 2: other player has no coppers in his/her hand---*/
    //get other players hand count before
    int otherPHandCountBefore2 = state2.handCount[1];
    
    //play cutpurse card with state 1
    cardEffect(cutpurse, -1, -1, -1, &state2, handPos, &bonus);

    //get other players hand count and discard count after
    int otherPHandCountAfter2 = state2.handCount[1];
    
    /*Test 4: If player has copper in hand, verify that there are two less cards in hand after the cutpurse card is played*/
    printf("\nTesting that there are still the same number of cards in the other player's hand if copper is NOT present in the second player's hand and the cutpurse card is played.\n");
    if (otherPHandCountAfter2 == otherPHandCountBefore2){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Hand count before was %d, and hand count after was %d\n", otherPHandCountBefore2, otherPHandCountAfter2);
    }

    /*Test 5: Verify no state changes to victory or kingdom card piles*/
    printf("\nTesting that there are no state changes to the victory and kingdom card piles after cutpurse card played.\n");
    if (checkSupplyCountSame(&state1, kingdomCards)){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: The supply count has changed for one or more kingdom cards or victory cards\n");
    }

    return 0;
}
