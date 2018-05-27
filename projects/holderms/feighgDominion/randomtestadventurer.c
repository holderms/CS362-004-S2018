/*
Samantha Holderman
Assignment 4
Random test for  Adventurer

*/

#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "printGame.h"


int main() {
  printTrace("!____________Random Card Test 3 - Adventurer__________!\n");
  int seed = 1000;
  srand(time(NULL));
  int numPlayers;

  //test with 2, 3, and 4 players
  for (numPlayers = 2; numPlayers <=4; numPlayers++) {
    printf("Testing with %d Players\n", numPlayers);
    fflush(stdout);
    struct gameState G, copy;
    int noUpdate = 0, currentError = 0, noDiscardTest = 0; //count number of failures
    // Deck is now supply cards 0 - 16
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    initializeGame(numPlayers, k, seed, &G);
    // printf("Initial game\n_______________________\n");
    // printGameState(&G);


    // while the gamestate is still playable
    // randomization comes from normal game play, deck could be changed by other
    // cards or players

    int i = 0;
    // while (isGameOver(&G) == 0 && i < 100) {
    while (isGameOver(&G) == 0) {
      // printf("Round: %d\n", i);
      // fflush(stdout);
      //stack coins to progress game faster (makes buying easier but not guaranteed)
      G.coins += 10;
      int playedC = 0;
      int j;

      // look for a adventurer card in hand to play
      for (j = 0; j < numHandCards(&G); j++) {
        if (handCard(j, &G) == adventurer) {
          int playerNum = G.whoseTurn;
          // Begin Testing
          //copy for comparisons
          memcpy(&copy, &G, sizeof(struct gameState));
          //printTrace("Playing Adventurer\n");
          //if ((j + 1) == numHandCards(&copy)) printf("%d: Attempting to discard illegal card\n", i);
          playCard(j, 0, 0, 0, &G);

          // check for fails
          if (memcmp(&copy, &G, sizeof(struct gameState)) == 0) {
            //failed, gameState should be different now
            printf("FAIL %d: Game state not updated: \n", i);
            fflush(stdout);
            // printTwo(&copy, &G);
            noUpdate ++;
          }

          // look through copy to see what may have been added
          // check deck first
          int d = 0, discardMin = 0, found = 0;

          while (d < copy.deckCount[playerNum] && found < 2) {
            int deckCheck = copy.deck[playerNum][d];
            if (deckCheck == gold || deckCheck == silver || deckCheck == copper) {
              found ++;
            }
            else {
              discardMin ++; // all other card types will be discarded
            }
            d++;
          }
          //see if it is possible to find another treasure in the current discards
          // not able to check number of total discard from here due to shuffling
          d = 0;
          while (d < copy.discardCount[playerNum] && found < 2) {
            int deckCheck = copy.discard[playerNum][d];
            if (deckCheck == gold || deckCheck == silver || deckCheck == copper) {
              found ++;
            }
            d++;
          }

          // see if right number of cards were added
          if ((copy.handCount[playerNum] + found ) != G.handCount[playerNum]) {
            printf("FAIL %d: CURRENT player cards not added correctly\n", i);
            fflush(stdout);
            printf("\tWas: %d\t Is: %d\n", copy.handCount[playerNum], G.handCount[playerNum]);
            fflush(stdout);
            currentError ++;
            //printTwo(&copy, &G);
          }


          // see if at least the verified number of cards have been Discarded
          // more may have been discarded from the reshuffled discard pile
          if (copy.discardCount[playerNum] + discardMin > G.discardCount[playerNum]) {
            printf("FAIL %d: Too many cards discarded\n", i);
            noDiscardTest ++;
          }

          buyCard(rand() % (great_hall + 1), &G); // buy a random card
          playedC = 1;
          // exit loop
          break;
        }
      }

      // No Adventurer card found
      if (playedC == 0 && numHandCards(&G) > 0) { //play a random card
        int playMe = rand() % numHandCards(&G);
        //printf("Random play: %d\n", handCard(playMe, &G));
        playCard(playMe, copper, silver, gold, &G);

        int buyMe = rand() % great_hall + 1;
        //printf("Random buy: %d\n", buyMe);
        buyCard(buyMe, &G); //try to buy a card
      }
      // advance turns
      endTurn(&G);
      // printf("\nGame State \n____________%d___________\n", i);
      // printGameState(&G);

      i ++;
    }
    // printf("Final Game State\n_______________________\n");
    // printGameState(&G);
    printTrace("\n Failure Counts\n");
    if (noUpdate)  printf("No updates: %d\n", noUpdate);
    // if (noDiscard1) printf("Bad discard 1st Half: %d\n", noDiscard1);
    // if (noDiscard2) printf("Bad discard 2nd Half: %d\n",noDiscard2);
    if (noDiscardTest) printf("Played card was not discarded: %d\n", noDiscardTest);
    if (currentError) printf("adventurer player error: %d\n", currentError);
    fflush(stdout);
    printTrace("_______________________\n");
  }
  return 0;
}
