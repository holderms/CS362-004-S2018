/*
Assignment 3, unit test 4
Testing  scoreFor

*
* Include the following lines in your makefile:
*
* unittest4: unittest4.c dominion.o rngs.o
*      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
//#include "dominion.c"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main() {
  printf("!+++++++++++++++++  Unit Test 4 +++++++++++++++++++!\n");
  int c, p;
  int seed = 1000;
  int numPlayers = 2;
  struct gameState G;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  // initialize game does not set up player hand or count correctly (commented out)
  initializeGame(numPlayers, k, seed, &G);

  //all hands should have 3 estates from intilization
  for(p = 0; p < numPlayers; p++) {
    printf("Player %d hand:", p);
    for (c = 0; c < G.handCount[p]; c++) {
      printf("  %d", G.hand[p][c]);
    }

    printf("\nPlayer %d discard:", p);
    for (c = 0; c < G.discardCount[p]; c++) {
      printf("  %d", G.discard[p][c]);
    }
    printf("\nPlayer %d deck:", p);
    for (c = 0; c < G.deckCount[p]; c++) {
      printf("  %d", G.deck[p][c]);
    }
    printf("\n");
  }

  //Score should be 3
  printf("Score should be 3 for both players\n");
  for(p = 0; p < numPlayers; p++) {
    int score = scoreFor(p, &G);
    if (scoreFor(p, &G) != 3) {
      printf("Fail player %d: Score is %d\n", p, score);
    }
  }

  printf("!+++++++++++++++++++++++!\n");
  return 0;
}
