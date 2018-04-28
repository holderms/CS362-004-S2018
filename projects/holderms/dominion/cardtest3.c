/*
Assignment 3, card test3
Testing  embargo

*
* Include the following lines in your makefile:
*
* cardtest3: cardtest3.c dominion.o rngs.o
*      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
//#include "dominion.c"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main() {
  printf("!____________Card Test 3__________!\n");
  int c, state;
  int seed = 1000;
  int numPlayers = 2;
  struct gameState G, original;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  int bonus;
  initializeGame(numPlayers, k, seed, &G);

  printf("Before: Player %d  Hand size %d, Coins %d\n", whoseTurn(&G), G.handCount[0], G.coins);

  G.hand[0][0] = embargo; //set player 0 card 0 to embargo
  //set deck to something distinctive
  for (c = 0; c < G.deckCount[0]; c++) {
    G.deck[0][c] = smithy + 1 + c;
  }
  memcpy(&original, &G, sizeof(struct gameState));
// Test 1  --normal play
  printf("\nTest1 with default hand/deck\n");

  state = cardEffect(embargo, 1, 1, 1, &G, 0, &bonus);
  printf("After: Player %d  Hand size %d, Coins %d\n", whoseTurn(&G), G.handCount[0], G.coins);
  if(state < 0) {
    printf("embargoEffect failed\n");
  }

  printf("Current Hand:\t");
  for(c = 0; c < G.handCount[0]; c++) {
    printf("  %d", G.hand[0][c]);
  }
  printf("\nOriginal Hand:\t");
  for(c = 0; c < original.handCount[0]; c++) {
    printf("  %d", original.hand[0][c]);
  }
  printf("\n");

  //check new hand values
  if( original.handCount == 0 || G.coins != original.coins + 2) {
    printf("Incorrect number of new coins: Old: %d, New %d\n", original.coins, G.coins);
  }

// Test 2 --choice taken
    printf("\nTest2 with choice occupied\n");
    //reset to before test1
    memcpy(&G, &original, sizeof(struct gameState));
    //set choice 1 to "in play"
    G.supplyCount[1] = -1;
    state = cardEffect(embargo, 1, 1, 1, &G, 0, &bonus);
    printf("After: Player %d  Hand size %d, Coins %d\n", whoseTurn(&G), G.handCount[0], G.coins);
    if(state < 0) {
      printf("PASS: embargoEffect caught pile-not-in-use failure\n");
    }

    printf("Current Hand:\t");
    for(c = 0; c < G.handCount[0]; c++) {
      printf("  %d", G.hand[0][c]);
    }
    printf("\nOriginal Hand:\t");
    for(c = 0; c < original.handCount[0]; c++) {
      printf("  %d", original.hand[0][c]);
    }
    printf("\n");

    //check new hand values
    if( original.handCount == 0 || G.coins != original.coins) {
      printf("FAIL: Incorrect number of coins: Old: %d, New %d\n", original.coins, G.coins);
    }

  printf("!_____________________________!\n");
  return 0;
}
