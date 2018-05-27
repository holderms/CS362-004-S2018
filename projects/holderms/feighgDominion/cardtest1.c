/*
Assignment 3, card test 1
Testing  adventurer

*
* Include the following lines in your makefile:
*
* cardtest1: cardtest1.c dominion.o rngs.o
*      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
//#include "dominion.c"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main() {
  printf("!____________Card Test 1__________!\n");
  printf("!____________adventurer__________!\n");
  int c, state;
  int seed = 1000;
  int numPlayers = 2;
  struct gameState G, original, mod;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  int bonus;
  initializeGame(numPlayers, k, seed, &G);
  memcpy(&original, &G, sizeof(struct gameState));
// Test 1
  printf("\nTest1 with default hand/deck\n");
  state = cardEffect(adventurer, 1, 1, 1, &G, 0, &bonus);
  printf("Player %d  Deck size %d\n", whoseTurn(&G), G.deckCount[0]);
  if(state < 0) {
    printf("adventurerEffect failed\n");
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
  if( original.handCount == 0 || G.handCount[0] != original.handCount[0] + 2 ) {
    printf("Incorrect number of new cards: Old: %d, New %d\n", original.handCount[0], G.handCount[0]);
  }
  //check discard
  if(G.discardCount[0] != 3 ) {
    printf("Incorrect number of discards: Should be: 3, Is %d\n", G.discardCount[0]);
    for (c = 0; c < G.discardCount[0]; c++) {
      printf("%d\t", G.discard[0][c]);
    }
    printf("\n");
  }
  
  //reset
  initializeGame(numPlayers, k, seed, &G);
//Test2
  printf("\nTest2 with discards\n");
  printf("Player %d  Deck size %d\n", whoseTurn(&G), G.deckCount[0]);

  //manipulate deck to force discards
  for(c = 0; c < G.deckCount[0]; c++) {
    G.deck[0][c] = embargo;
  }
  G.deck[0][0] = gold;
  G.deck[0][2] = gold;
  memcpy(&mod, &G, sizeof(struct gameState));
  state = cardEffect(adventurer, 1, 1, 1, &G, 0, &bonus);
  if(state < 0) {
    printf("adventurerEffect failed\n");
  }

  printf("Current Hand:\t");
  for(c = 0; c < G.handCount[0]; c++) {
    printf("  %d", G.hand[0][c]);
  }
  printf("\nOriginal Hand:\t");
  for(c = 0; c < mod.handCount[0]; c++) {
    printf("  %d", mod.hand[0][c]);
  }
  printf("\n");

  //check hand
  printf("Test 2\tHand count should now include 2 gold cards: %d\n", G.handCount[0]);
  if( mod.handCount == 0 || G.handCount[0] != mod.handCount[0] + 2 ) {
    printf("Incorrect number of new cards: Old: %d, New %d\n", mod.handCount[0], G.handCount[0]);
  }
  //check discard
  if(G.discardCount[0] != 3 ) {
    printf("Incorrect number of discards: Should be: 3, Is %d\n", G.discardCount[0]);
    for (c = 0; c < G.discardCount[0]; c++) {
      printf("%d\t", G.discard[0][c]);
    }
    printf("\n");
  }
/*

//Test3

*/
  //reset
  initializeGame(numPlayers, k, seed, &G);

  printf("\nTest3 with None found\n");
  printf("Player %d  Deck size %d\n", whoseTurn(&G), G.deckCount[0]);

  //manipulate deck to force discards
  for(c = 0; c < G.deckCount[0]; c++) {
    G.deck[0][c] = embargo;
  }

  memcpy(&mod, &G, sizeof(struct gameState));

  state = cardEffect(adventurer, 1, 1, 1, &G, 0, &bonus);
  if(state < 0) {
    printf("adventurerEffect failed\n");
  }

  printf("Current Hand:\t");
  for(c = 0; c < G.handCount[0]; c++) {
    printf("  %d", G.hand[0][c]);
  }
  printf("\nOriginal Hand:\t");
  for(c = 0; c < mod.handCount[0]; c++) {
    printf("  %d", mod.hand[0][c]);
  }
  printf("\n");

  //check hand
  printf("Test 2\nDiscard should now include 10 cards %d\n", G.handCount[0]);
  if( mod.handCount == 0 || G.handCount[0] != mod.handCount[0]) {
    printf("Incorrect number of new cards: Old: %d, New %d\n", mod.handCount[0], G.handCount[0]);
  }
  //check discard
  if(G.discardCount[0] != 3 ) {
    printf("Incorrect number of discards: Should be: 5, Is %d\n", G.discardCount[0]);
    for (c = 0; c < G.discardCount[0]; c++) {
      printf("%d\t", G.discard[0][c]);
    }
    printf("\n");
  }

  printf("!_____________________________!\n");
  return 0;
}
