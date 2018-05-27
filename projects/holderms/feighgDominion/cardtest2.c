/*
Assignment 3, card test2
Testing  smithy

*
* Include the following lines in your makefile:
*
* cardtest2: cardtest2.c dominion.o rngs.o
*      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
//#include "dominion.c"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main() {
  printf("!____________Card Test 2__________!\n");
  printf("!____________smithy__________!\n");
  int c, state;
  int seed = 1000;
  int numPlayers = 2;
  struct gameState G, original;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  int bonus;
  initializeGame(numPlayers, k, seed, &G);

  printf("Before: Player %d  Hand size %d, Deck size %d\n", whoseTurn(&G), G.handCount[0], G.deckCount[0]);

  G.hand[0][0] = smithy; //set player 0 card 0 to smithy
  //set deck to something distinctive
  for (c = 0; c < G.deckCount[0]; c++) {
    G.deck[0][c] = smithy + 1 + c;
  }
  memcpy(&original, &G, sizeof(struct gameState));
// Test 1
  printf("\nTest1 with default hand/deck\n");
  printf("Original Hand:\t");
  for(c = 0; c < G.handCount[0]; c++) {
    printf("  %d", G.hand[0][c]);
  }
  printf("\n");

  state = cardEffect(smithy, 1, 1, 1, &G, 0, &bonus);
  
  printf("Current Hand:\t");
  for(c = 0; c < G.handCount[0]; c++) {
    printf("  %d", G.hand[0][c]);
  }
  printf("\n");

  printf("After:  Player %d  Hand size %d\n", whoseTurn(&G), G.handCount[0]);
  if(state < 0) {
    printf("smithyEffect failed\n");
  }
  //check new hand values
  if( original.handCount == 0 || G.handCount[0] != original.handCount[0] + 3 - 1 ) {
    printf("Expected %d\n", original.handCount[0] + 3 - 1);
    printf("Incorrect number of new cards: Old: %d, New %d\n", original.handCount[0], G.handCount[0]);
  }

  printf("!_____________________________!\n");
  return 0;
}
