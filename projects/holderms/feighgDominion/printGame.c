#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>



int printGameState(struct gameState * thisGame) {
  // printf("num players in print: %d\n", thisGame->numPlayers);
  int p, curr = whoseTurn(thisGame);
  for (p = 0; p < thisGame->numPlayers; p++) {
    int c;
    printf("\nPlayer %d: \n", p);
    if (p == curr) printf("\t((Current player))\n");
    printf("Hand %d: \n\t", thisGame->handCount[p]);
    for (c = 0; c < thisGame->handCount[p]; c++) {
      printf("%d\t", thisGame->hand[p][c]);
    }
    printf("\nDeck %d: \n\t", thisGame->deckCount[p]);
    for (c = 0; c < thisGame->deckCount[p]; c++) {
      printf("%d\t", thisGame->deck[p][c]);
    }
    printf("\nDiscard %d: \n\t", thisGame->discardCount[p]);
    for (c = 0; c < thisGame->discardCount[p]; c++) {
      printf("%d\t", thisGame->discard[p][c]);
    }
    printf("\n");
    fflush(stdout);
  }

  // printf("\nSupply Counts\n");
  // int j;
  // for (j = 0; j < treasure_map + 1; j ++) {
  //   if(thisGame->supplyCount[j] > -1) printf("SCard %d = %d\n", j, thisGame->supplyCount[j]);
  // }
  printf("\n");
  fflush(stdout);
  return 0;
}

int printTwo(struct gameState * previousGame, struct gameState * thisGame) {
  printf("---Previous Game State---");
  printGameState(previousGame);
  printf("\n---Current Game State--");
  printGameState(thisGame);

  return 0;
}

void printTrace(char * string) {
  printf("%s\n", string);
  fflush(stdout);
}
