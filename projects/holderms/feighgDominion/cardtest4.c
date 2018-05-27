/*
Assignment 3, card test4
Testing  council_room


* Include the following lines in your makefile:
*
* cardtest4: cardtest4.c dominion.o rngs.o
*      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
//#include "dominion.c"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main() {
  printf("!____________Card Test 4__________!\n");
  printf("!____________Council_room__________!\n");
  int c, p, state;
  int seed = 1000;
  int numPlayers = 2;
  struct gameState G, original;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  int bonus;
  initializeGame(numPlayers, k, seed, &G);
  //
  // printf("Before: Player %d  Hand size %d, Coins %d\n", whoseTurn(&G), G.handCount[0], G.coins);

  G.hand[0][0] = council_room; //set player 0 card 0 to council_room
  //set deck to something distinctive
  for (c = 0; c < G.deckCount[0]; c++) {
    G.deck[0][c] = smithy + 1 + c;
  }
  memcpy(&original, &G, sizeof(struct gameState));
// Test 1  --normal play
  printf("\nTest1 with default hand/deck\n");

  state = cardEffect(council_room, 1, 1, 1, &G, 0, &bonus);
  // printf("After: Player %d  Hand size %d, Coins %d\n", whoseTurn(&G), G.handCount[0], G.coins);
  if(state < 0) {
    printf("council_roomEffect failed\n");
  }

  printf("Player 0 stats\n");
  if(G.handCount[0] == original.handCount[0] + 4) printf("Hand count good %d\n", G.handCount[0]);
  if(G.numBuys == original.numBuys + 1) printf("Buy count good %d\n", G.numBuys);

  printf("Other %d players stats\n", G.numPlayers);
  for(p = 1; p < numPlayers; p++) {
    if(G.handCount[p] == original.handCount[p] + 1) printf("Player %d handCount is %d\n", p, G.handCount[p]);
  }
  printf("\n");


// Test 2 -- Stress test max value
    printf("\nTest2 with large number of players\n");
    initializeGame(MAX_PLAYERS, k, seed, &G);
    //
    // printf("Before: Player %d  Hand size %d, Coins %d\n", whoseTurn(&G), G.handCount[0], G.coins);

    G.hand[0][0] = council_room; //set player 0 card 0 to council_room
    //set deck to something distinctive
    for (c = 0; c < G.deckCount[0]; c++) {
      G.deck[0][c] = smithy + 1 + c;
    }
    memcpy(&original, &G, sizeof(struct gameState));
  // Test 1  --normal play
    printf("\nTest1 with default hand/deck\n");

    state = cardEffect(council_room, 1, 1, 1, &G, 0, &bonus);
    // printf("After: Player %d  Hand size %d, Coins %d\n", whoseTurn(&G), G.handCount[0], G.coins);
    if(state < 0) {
      printf("council_roomEffect failed\n");
    }

    printf("Player 0 stats\n");
    if(G.handCount[0] == original.handCount[0] + 4) printf("Hand count good %d\n", G.handCount[0]);
    if(G.numBuys == original.numBuys + 1) printf("Buy count good %d\n", G.numBuys);

    printf("Other %d players stats\n", G.numPlayers);
    for(p = 1; p < MAX_PLAYERS; p++) {
      if(G.handCount[p] == original.handCount[p] + 1) printf("Player %d handCount is %d\n", p, G.handCount[p]);
    }
    printf("\n");

  printf("!_____________________________!\n");
  return 0;
}
