/*
Assignment 3, unit test 3
Testing playcard which should play action cards and return -1 for others

*
* Include the following lines in your makefile:
*
* unittest3: unittest3.c dominion.o rngs.o
*      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
//#include "dominion.c"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main() {
  printf("!+++++++++++++++  Unit Test 3  +++++++++++++++_!\n");
  int i, c, state = -5;
  int seed = 1000;
  int numPlayers = 2;
  struct gameState G, testBase;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};

  // initialize a game state and player cards
  // initialize game does not set up player hand or count correctly (commented out)
  initializeGame(numPlayers, k, seed, &G);
  //set up some different card types for testing
  G.deck[0][0] = adventurer; //edge case 1 for action card
  G.deck[0][1] = treasure_map; //edge case 2 for action cards
  G.deck[0][2] = gold; //fail edge case 3 for action cards
  G.deck[0][3] = treasure_map + 1; //fail edge case 4 invalid card
  G.deck[0][4] = steward; //check card that uses choices
  //fill remaining deck with coppers
  for (i = 5; i < 10; i++) {
    G.deck[0][i] = copper;
  }

  //set up hand with test cards
  for (c = 0; c < 5; c++) {
    G.hand[0][c] = G.deck[0][c];
  }
  G.handCount[0] = 5;
  // save a copy before testing
  memcpy(&testBase, &G, sizeof(struct gameState));

  //Test 1 - Check that a valid card (adventurer) works correctly
  printf("----------------------\nUnit Test 3.1 --- adventurer playCard\n");
  //verify phase & G.numActions are valid to ensure card is checked
  if(G.phase != 0) G.phase = 0;
  if(G.numActions!= 1) G.numActions= 1;

  state = playCard(0, 1, 1, 1, &G);
  //check card was not changed (discard handled by endTurn)
  assert(G.hand[0][0] == adventurer);
  if (state == -1)  printf("Unit test 3.1 failed --- invalid card\n");
  else if (state == -5 ) printf("Unit test 3.1 State not updated\n");
  else {
    //check if coins updates
    // should be True, deck is stacked with coppers
    if(G.coins != testBase.coins) printf("Coins updated, change is 2? == %d\n", (G.coins - testBase.coins));
    //Check G.numActions was updated correctly
    if(G.numActions != testBase.numActions - 1) printf("Fail: G.numActions is %d\n", G.numActions);
    if(G.numActions == 0 && G.phase == 0) printf("Fail: No actions remaining but still in action phase\n");

  }

  //Set up for test 2
  memcpy(&G, &testBase, sizeof(struct gameState));
  state = -5;

  //Test 2 - Check that a valid card (treasure_map) works correctly
  printf("----------------------\nUnit Test 3.2 --- treasure_map playCard\n");
  //verify phase & G.numActions are valid to ensure card is checked
  if(G.phase != 0) G.phase = 0;
  if(G.numActions!= 1) G.numActions= 1;

  state = playCard(1, 1, 1, 1, &G);
  //check card was not changed (discard handled by endTurn)
  assert(G.hand[0][1] == treasure_map);
  if (state == -1)  printf("Unit test 3.2 failed --- invalid card\n");
  else if (state == -5 ) printf("Unit test 3.2 State not updated\n");
  else {
    //check if coins updates
    // should be no change, no other treasure_maps
    if(G.coins != testBase.coins) printf("Test 3.2 Coins updated, change is 0? == %d\n", (G.coins - testBase.coins));
    //Check G.numActions was updated correctly
    if(G.numActions != testBase.numActions - 1) printf("Test 3.2 Fail: G.numActions is %d\n", G.numActions);
    if(G.numActions == 0 && G.phase == 0) printf("Test 3.2 Fail: No actions remaining but still in action phase\n");
  }

  //Set up for test 3
  memcpy(&G, &testBase, sizeof(struct gameState));
  state = -5;

  //Test 3 - Check that a invalid card (gold) fails correctly
  printf("----------------------\nUnit Test 3.3 --- gold playCard\n");
  //verify phase & G.numActions are valid to ensure card is checked
  if(G.phase != 0) G.phase = 0;
  if(G.numActions!= 1) G.numActions= 1;

  state = playCard(2, 1, 1, 1, &G);
  //check card was not changed (discard handled by endTurn)
  assert(G.hand[0][2] == gold);
  if (state == -1)  {
    //check for other updates
    printf("OK Unit test 3.3 failed --- invalid card\n");
    //Check for coin updates
    if(G.coins != testBase.coins) printf("Test 3.3 Coins updated, change is 0? == %d\n", (G.coins - testBase.coins));
    //Check G.numActions was updated correctly
    if(G.numActions != testBase.numActions) printf("Test 3.3 Fail: G.numActions was updated is %d\n", G.numActions);
    if(G.numActions == 0 && G.phase == 0) printf("Test 3.3 Fail: No actions remaining but still in action phase\n");
}

  else if (state == -5 ) printf("Unit test 3.3 State not updated\n");
  else {
    printf("!!! This should not print !!! Test 3.3\n");
  }

  //Set up for test 4
  memcpy(&G, &testBase, sizeof(struct gameState));
  state = -5;

  //Test 4 - Check that a invalid card (greater than treasure_map) fails correctly
  printf("----------------------\nUnit Test 3.4 --- invalid playCard\n");
  //verify phase & G.numActions are valid to ensure card is checked
  if(G.phase != 0) G.phase = 0;
  if(G.numActions!= 1) G.numActions= 1;

  state = playCard(3, 1, 1, 1, &G);
  //check card was not changed (discard handled by endTurn)
  assert(G.hand[0][3] == treasure_map + 1);

  if (state == -1) {
    printf("OK Unit test 3.4 failed --- invalid card\n");
    //Check for other updates
    //check if coins updates
    if(G.coins != testBase.coins) printf("Test 3.4 Coins updated, change is 0? == %d\n", (G.coins - testBase.coins));
    //Check G.numActions was updated correctly
    if(G.numActions != testBase.numActions) printf("Test 3.4 Fail: G.numActions is %d\n", G.numActions);
    if(G.numActions == 0 && G.phase == 0) printf("Test 3.4 Fail: No actions remaining but still in action phase\n");
  }
  else if (state == -5 ) printf("Unit test 3.4 State not updated\n");
  else {
    printf("!!! This should not print !!! Test 3.4\n");
  }


  //Set up for test 5
  memcpy(&G, &testBase, sizeof(struct gameState));
  state = -5;

  //Test 4 - Check that a valid card which uses the "choices" works
  printf("----------------------\nUnit Test 3.5 --- steward playCard\n");
  //verify phase & G.numActions are valid to ensure card is checked
  if(G.phase != 0) G.phase = 0;
  if(G.numActions!= 1) G.numActions= 1;

  state = playCard(4, 3, 0, 1, &G);
  //steward removes cards, make sure removed
  assert(G.hand[0][0] != adventurer);
  assert(G.hand[0][1] != treasure_map);

  if (state == -1)  printf("Unit test 3.5 failed --- invalid card\n");
  else if (state == -5 ) printf("Unit test 3.5 State not updated\n");
  else {
    //check if coins updates
    // should be false, no other treasure_maps
    if(G.coins == testBase.coins) printf("Test 3.5 Coins not updated, change is 0? == %d\n", (G.coins - testBase.coins));
    //Check G.numActions was updated correctly
    if(G.numActions != testBase.numActions - 1) printf("Test 3.5 Fail: G.numActions is %d\n", G.numActions);
    if(G.numActions == 0 && G.phase == 0) printf("Test 3.5 Fail: No actions remaining but still in action phase\n");
  }

  //Set up for test 6
  memcpy(&G, &testBase, sizeof(struct gameState));
  state = -5;

  printf("----------------------\nUnit Test 3.6 --- bad phase \n");
  G.phase = 1;
  if(G.numActions!= 1) G.numActions= 1;

  state = playCard(4, 3, 0, 1, &G);

  if (state == -1)  printf("OK - Unit test 3.6 failed --- invalid phase\n");
  else if (state == -5 ) printf("Unit test 3.6 State not updated\n");
  else {
    printf("FAIL 3.6 - card should not be played\n");
  }


  //Set up for test 7
  memcpy(&G, &testBase, sizeof(struct gameState));
  state = -5;

  printf("----------------------\nUnit Test 3.7 --- bad num actions \n");

   G.phase = 0;
   G.numActions= 0;

  state = playCard(4, 3, 0, 1, &G);

  if (state == -1)  printf("OK - Unit test 3.7 failed --- invalid actions\n");
  else if (state == -5 ) printf("Unit test 3.7 State not updated\n");
  else {
    printf("FAIL 3.7 - card should not be played\n");
  }

  printf("!+++++++++++++++++++++++++++++++++!\n");
  return 0;
}
