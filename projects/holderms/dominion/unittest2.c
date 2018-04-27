/*
Assignment 3, unit test 2
Testing kingdomCards

*
* Include the following lines in your makefile:
*
* unittest1: unittest2.c dominion.o rngs.o
*      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
//#include "dominion.c"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main() {
  int i, p, c, state = -5;
  int seed = 1000;
  int numPlayers = 4;
  struct gameState G, testBase;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  initializeGame(numPlayers, k, seed, &G);
  //make a copy to compare against
  //struct gameState tracking[6] = malloc(6 * sizeof(struct gameState));
  memcpy(&testBase, &G, sizeof(struct gameState));

  //stress test multiple times for failure (not shuffled or bad incrementing)
  for (i = 1; i <= 5; i ++) {
    for (p = 0; p < numPlayers; p++) {
      state = shuffle(p, &G);
      //check to see if basic shuffle failed
      if (state != 0) {
        printf("Failure in loop %d: Player %d\n", i, p);
      } else {
        printf("\t\tOK Loop: %d   Player %d\n", i, p);
      }
      // check deck size after shuffle
      if(G.deckCount[p] != testBase.deckCount[p]) {
        printf("SIZE ERROR: Player %d size is %d, should be %d\n", p, G.deckCount[p], testBase.deckCount[p]);
      }
      // check if this is repeat of original game state
      for (c = 0; c < G.deckCount[p]; c++) {
        if (G.deck[p][c] == testBase.deck[p][c]){
          printf("Duplicate pattern detected Player %d Card place %d: #%d\n", p, c, testBase.deck[p][c]);
        }
      }

    }
  }


//first shuffle is always the same, not truly random (not seeded)
return 0;
}
