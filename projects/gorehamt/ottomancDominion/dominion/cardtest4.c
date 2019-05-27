/****************************************************************************************
* Unit Tests for steward card
* Written by: Traci Goreham, CS361
****************************************************************************************/

//include header files
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//include relevant libraries
#include <string.h>
#include <stdio.h>
#include <limits.h> //INT_MAX


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
    struct gameState state1, state2, state3, state4, state5, state6;
    int seed = 1000;
    int kingdomCards[10] = {adventurer, great_hall, village, minion, steward, cutpurse, embargo, tribute, smithy, council_room};    

    //initialize three of the same game states
    initializeGame(numPlayers, kingdomCards, seed, &state1); //sets curse = 10, estate = 8, duchy = 8, provice = 8, copper = 46, silver = 40, gold = 30, all kingdom cards = 8
    initializeGame(numPlayers, kingdomCards, seed, &state2);
    initializeGame(numPlayers, kingdomCards, seed, &state3);
    initializeGame(numPlayers, kingdomCards, seed, &state4);
    initializeGame(numPlayers, kingdomCards, seed, &state5);
    initializeGame(numPlayers, kingdomCards, seed, &state6);

    //add steward card to first player's hand at position 2 of all three game states
    int currentPlayer = 0;
    int handPos = 2; 
    int bonus = -1;
    state1.hand[currentPlayer][handPos] = steward;
    state2.hand[currentPlayer][handPos] = steward;
    state3.hand[currentPlayer][handPos] = steward;
    state4.hand[currentPlayer][handPos] = steward;
    state5.hand[currentPlayer][handPos] = steward;
    state6.hand[currentPlayer][handPos] = steward;

    /*---state 1: choosing to add two cards to hand---*/
    //get current hand size, number of buys, etc. with state 1
    int currentPHandSizeBefore1 = state1.handCount[currentPlayer];
    int currentPDeckCountBefore1 = state1.deckCount[currentPlayer];
    int otherPDeckCountBefore1 = state1.deckCount[1];
    int otherPHandCountBefore1 = state1.handCount[1];
    int otherPDiscardCountBefore1 = state1.discardCount[1];

    //play steward card with choice 1 of drawing two cards with state 1
    cardEffect(steward, 1, -1, -1, &state1, handPos, &bonus);

    //get hand size, num of buys, etc. after card is played with state 1
    int currentPHandSizeAfter1 = state1.handCount[currentPlayer];
    int currentPDeckCountAfter1 = state1.deckCount[currentPlayer];
    int otherPDeckCountAfter1 = state1.deckCount[1];
    int otherPHandCountAfter1 = state1.handCount[1];
    int otherPDiscardCountAfter1 = state1.discardCount[1];

    printf("\n------Testing Steward Card Implementation------\n");

    /*Test 1: Verify that if the current player chooses choice 1, he/she gets two extra cards in his/her hand.*/
    printf("\nTesting that current player's hand size increases by exactly 1 card after choice 1 of steward card is chosen (+2 b/c steward played, -1 b/c steward was discarded, for a total of 1 extra cards).\n");
    if (currentPHandSizeAfter1 == currentPHandSizeBefore1 + 1){ 
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Hand size before was %d, and hand size after was %d\n", currentPHandSizeBefore1, currentPHandSizeAfter1);
    }

    /*Test 2: Verify that extra cards comes from current player's pile*/
    printf("\nTesting that the extra cards come from current player's deck when selecting choice 1 with steward card.\n");
    if (currentPDeckCountAfter1 == currentPDeckCountBefore1 - 2){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Deck count before was %d, and deck count after was %d\n", currentPDeckCountBefore1, currentPDeckCountAfter1);
    }

    /*Test 3: Verify that no state changes occur for the other player*/
    printf("\nTesting that no state changes occur for the other player when selecting choice 1 with steward card.\n");
    if ((otherPHandCountBefore1 == otherPHandCountAfter1) && (otherPDeckCountBefore1 == otherPDeckCountAfter1) && (otherPDiscardCountBefore1 == otherPDiscardCountAfter1)){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: The hand count, deck count, or discard count has changed for the other player.\n");
    }

    /*Test 4: Verify no state changes to victory or kingdom card piles*/
    printf("\nTesting that there are no state changes to the victory and kingdom card piles in choice 1 of steward.\n");
    if (checkSupplyCountSame(&state1, kingdomCards)){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: The supply count has changed for one or more kingdom cards or victory cards\n");
    }

    /*---state 2: choosing to add two coins to coin count---*/
    //get current hand size, number of buys, etc. with state 2
    int currentPCoinsBefore2 = state2.coins;
    int otherPDeckCountBefore2 = state2.deckCount[1];
    int otherPHandCountBefore2 = state2.handCount[1];
    int otherPDiscardCountBefore2 = state2.discardCount[1];

    //play steward card with choice 1 of drawing two cards with state 2
    cardEffect(steward, 2, -1, -1, &state2, handPos, &bonus);

    //get hand size, num of buys, etc. after card is played with state 2
    //int currentPHandSizeAfter = state2.handCount[currentPlayer];
    int currentPCoinsAfter2 = state2.coins;
    int otherPDeckCountAfter2 = state2.deckCount[1];
    int otherPHandCountAfter2 = state2.handCount[1];
    int otherPDiscardCountAfter2 = state2.discardCount[1];

    /*Test 5: Verify that the current player receives exactly 2 more coins*/
    printf("\nTesting that current player's number of coins increases by exactly 2 when selecting choice 2 with steward card.\n");
    if (currentPCoinsAfter2 == currentPCoinsBefore2 + 2){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Number of coins before was %d, and number of coins after was %d\n", currentPCoinsBefore2, currentPCoinsAfter2);
    }

    /*Test 6: Verify that no state changes occur for the other player*/
    printf("\nTesting that no state changes occur for the other player when selecting choice 2 with steward card.\n");
    if ((otherPHandCountBefore2 == otherPHandCountAfter2) && (otherPDeckCountBefore2 == otherPDeckCountAfter2) && (otherPDiscardCountBefore2 == otherPDiscardCountAfter2)){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: The hand count, deck count, or discard count has changed for the other player.\n");
    }

    /*Test 7: Verify no state changes to victory or kingdom card piles*/
    printf("\nTesting that there are no state changes to the victory and kingdom card piles in choice 2 of steward.\n");
    if (checkSupplyCountSame(&state2, kingdomCards)){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: The supply count has changed for one or more kingdom cards or victory cards\n");
    }


    /*---state 3: choosing to discard two cards---*/
    //get current hand size, number of buys, etc. with state 3
    int currentPHandSizeBefore3 = state3.handCount[currentPlayer];
    int currentPDiscardCountBefore3 = state3.discardCount[currentPlayer];
    int otherPDeckCountBefore3 = state3.deckCount[1];
    int otherPHandCountBefore3 = state3.handCount[1];
    int otherPDiscardCountBefore3 = state3.discardCount[1];

    //play steward card with choice 1 of drawing two cards with state 3
    cardEffect(steward, 3, 0, 1, &state3, handPos, &bonus);

    //get hand size, num of buys, etc. after card is played with state 3
    int currentPHandSizeAfter3 = state3.handCount[currentPlayer];
    int currentPDiscardCountAfter3 = state3.discardCount[currentPlayer];
    int otherPDeckCountAfter3 = state3.deckCount[1];
    int otherPHandCountAfter3 = state3.handCount[1];
    int otherPDiscardCountAfter3 = state3.discardCount[1];

    /*Test 8: Verify that if the current player chooses choice 3, he/she gets discards two cards from his/her hand.*/
    printf("\nTesting that current player's hand size decreases by exactly 3 cards after choice 3 of steward card is chosen (-2 b/c steward played, -1 b/c steward itself was discarded, for a total of 3 fewer cards).\n");
    if (currentPHandSizeAfter3 == currentPHandSizeBefore3 - 3){ 
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Hand size before was %d, and hand size after was %d\n", currentPHandSizeBefore3, currentPHandSizeAfter3);
    }

    /*Test 9: Verify that discarded cards are not in the player's discard pile because they should no longer be part of the players full deck of cards*/
    printf("\nTesting that the discarded cards are not in current player's discard pile (these cards are no longer part of player's hand) when selecting choice 3 with steward card.\n");
    if (currentPDiscardCountAfter3 == currentPDiscardCountBefore3){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Discard count before was %d, and discard count after was %d\n", currentPDiscardCountBefore3, currentPDiscardCountAfter3);
    }

    /*Test 10: Verify that no state changes occur for the other player*/
    printf("\nTesting that no state changes occur for the other player when selecting choice 3 with steward card.\n");
    if ((otherPHandCountBefore3 == otherPHandCountAfter3) && (otherPDeckCountBefore3 == otherPDeckCountAfter3) && (otherPDiscardCountBefore3 == otherPDiscardCountAfter3)){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: The hand count, deck count, or discard count has changed for the other player.\n");
    }

    /*Test 11: Verify no state changes to victory or kingdom card piles*/
    printf("\nTesting that there are no state changes to the victory and kingdom card piles in choice 3 of steward.\n");
    if (checkSupplyCountSame(&state3, kingdomCards)){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: The supply count has changed for one or more kingdom cards or victory cards\n");
    }


    /*---state 4: making an invalid choice, negative/boundary testing, negative number---*/
    //get hand size, discard count for current player before
    int currentPHandSizeBefore4 = state4.handCount[currentPlayer];
    int currentPDiscardCountBefore4 = state4.discardCount[currentPlayer];

    //play steward card with invalid choice of -1
    cardEffect(steward, -1, 0, 1, &state4, handPos, &bonus);

    //get hand size, discard count for current player after
    int currentPHandSizeAfter4 = state4.handCount[currentPlayer];
    int currentPDiscardCountAfter4 = state4.discardCount[currentPlayer];

    /*Test 12: Verify that if the current player chooses choice -1, the program will handle it gracefully and cause the player to discard two cards.*/
    printf("\nTesting invalid choice of -1: should handle input as if discarding two cards was chosen.\n");
    if (currentPHandSizeAfter4 == currentPHandSizeBefore4 - 3){ 
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Hand size before was %d, and hand size after was %d\n", currentPHandSizeBefore4, currentPHandSizeAfter4);
    }

    /*Test 13: Verify that discarded cards are not in the player's discard pile because they should no longer be part of the players full deck of cards*/
    printf("\nTesting that the discarded cards are not in current player's discard pile (these cards are no longer part of player's hand) when making invalid choice of -1.\n");
    if (currentPDiscardCountAfter4 == currentPDiscardCountBefore4){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Discard count before was %d, and discard count after was %d\n", currentPDiscardCountBefore4, currentPDiscardCountAfter4);
    }

    /*---state 5: making an invalid choice, negative/boundary testing, choice of INT_MAX---*/
    //get hand size, discard count for current player before
    int currentPHandSizeBefore5 = state5.handCount[currentPlayer];
    int currentPDiscardCountBefore5 = state5.discardCount[currentPlayer];

    //play steward card with invalid choice of INT_MAX
    cardEffect(steward, INT_MAX, 0, 1, &state5, handPos, &bonus);

    //get hand size, discard count for current player after
    int currentPHandSizeAfter5 = state5.handCount[currentPlayer];
    int currentPDiscardCountAfter5 = state5.discardCount[currentPlayer];

    /*Test 14: Verify that if the current player chooses choice INT_MAX, the program will handle it gracefully and cause the player to discard two cards.*/
    printf("\nTesting invalid choice of -1: should handle input as if discarding two cards was chosen.\n");
    if (currentPHandSizeAfter5 == currentPHandSizeBefore5 - 3){ 
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Hand size before was %d, and hand size after was %d\n", currentPHandSizeBefore5, currentPHandSizeAfter5);
    }

    /*Test 15: Verify that discarded cards are not in the player's discard pile because they should no longer be part of the players full deck of cards*/
    printf("\nTesting that the discarded cards are not in current player's discard pile (these cards are no longer part of player's hand) when making invalid choice of INT_MAX.\n");
    if (currentPDiscardCountAfter5 == currentPDiscardCountBefore5){
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Discard count before was %d, and discard count after was %d\n", currentPDiscardCountBefore5, currentPDiscardCountAfter5);
    }

    /*---state 6: making an invalid choice, negative testing, player chooses to discard a card not in his/her hand---*/
    //get hand size, discard count for current player before
    int currentPHandSizeBefore6 = state6.handCount[currentPlayer];

    //play steward card with invalid choice of INT_MAX
    cardEffect(steward, 3, 25, 1, &state6, handPos, &bonus);  //25 is not a valid number for a card to discard

    //get hand size, discard count for current player after
    int currentPHandSizeAfter6 = state6.handCount[currentPlayer];

    /*Test 16: Verify that a card is not removed from a player's hand if the card chosen is invalid.*/
    printf("\nTesting invalid choice of card to discard. A card should not be removed from the current player's hand.\n");
    if (currentPHandSizeAfter6 != currentPHandSizeBefore6 - 3){ 
        printf("\tTEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("\tTEST FAILED: Hand size before was %d, and hand size after was %d\n", currentPHandSizeBefore6, currentPHandSizeAfter6);
    }

    return 0;
}
