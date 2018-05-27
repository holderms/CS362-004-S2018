/*
Samantha Holderman
Assignment 4
Random test for  council_room

*/

#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "printGame.h"


int main() {
  printTrace("!____________Random Card Test 1 - Council Room__________!\n");
  int seed = 1000;
  srand(time(NULL));
  int numPlayers;

  for (numPlayers = 2; numPlayers <=4; numPlayers++) {
    printf("Testing with %d Players\n", numPlayers);
    fflush(stdout);
    struct gameState G, copy;
    int noUpdate = 0, currentError = 0, otherError = 0, noDiscard1 = 0, noDiscard2 = 0, noDiscardTest = 0; //count number of failures
    // Deck is now supply cards 0 - 16
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

      initializeGame(numPlayers, k, seed, &G);
      // printf("Initial game\n_______________________\n");
      // printGameState(&G);

      int i = 0; // for purposes of tracking the turns
      // while the gamestate is still playable, try testing 50 times
      // randomization comes from normal game play, deck could be changed by other
      // cards or players
      while (isGameOver(&G) == 0) {
        //stack coins to progress game faster (makes buying easier but not guaranteed)
        G.coins += 3;
        int playedC = 0;
        int j, cards = numHandCards(&G);



          for (j = 0; j < cards; j++) {
            if (handCard(j, &G) == council_room) {
              int playerNum = G.whoseTurn;
              // Begin Testing
              memcpy(&copy, &G, sizeof(struct gameState));
              //printTrace("Playing council_room\n");
              playCard(j, 0, 0, 0, &G);
              // check for fails
              if (memcmp(&copy, &G, sizeof(struct gameState)) == 0) {
                //failed, gameState should be different now
                printf("FAIL %d: Game state not updated: \n", i);
                fflush(stdout);
                // printTwo(&copy, &G);
                noUpdate ++;
              }
              // see if the right card was discarded
              if (copy.hand[playerNum][j] == G.hand[playerNum][j]) {
                int c, error1, error2;
                // see if the there was a duplicate card or if the wrong one was discarded
                for (c = 0; c < j; c++) { //only check through j to make sure the firstt c cards are the same
                  // see if cards are the same. no card at c should be discarded except the one at j
                  if (copy.hand[playerNum][c] != G.hand[playerNum][c]) {
                    printf("FAIL %d: Discarded earlier card\n", i);
                    fflush(stdout);
                    noDiscard1 ++;
                    error1 = 1;
                  }
                }
                // Skip card at j. see if next cards after j - end of copy hand match G (j should be discarded)
                for (c = j+1; c < copy.handCount[numPlayers]; c++) {
                  if(copy.hand[playerNum][c] != G.hand[playerNum][c-1]) {
                    printf("FAIL %d: Discarded later card\n", i);
                    fflush(stdout);
                    noDiscard2 ++;
                    error2 = 1;
                  }
                }
                if (error1 || error2) {
                  printf("FAIL %d: council_room was not discarded\n", i);
                  fflush(stdout);
                  noDiscardTest ++;
                }
                // printTwo(&copy, &G);
              }
              //see if right number of cards were added
              // Only check if there are enough drawable cards, else there will be a false error
              if(copy.discardCount[playerNum] + copy.deckCount[playerNum] >= 4) {
                if ((copy.handCount[playerNum] + 3) != G.handCount[playerNum]) { // + 3 = +4 new cards - 1 discard
                  printf("FAIL %d: CURRENT player cards not added correctly\n", i);
                  fflush(stdout);
                  printf("\tWas: %d\t Is: %d\n", copy.handCount[playerNum], G.handCount[playerNum]);
                  fflush(stdout);
                  currentError ++;
                  // printTwo(&copy, &G);
                }
              }
              int other;
              for (other = 0; other < G.numPlayers; other ++) {
                if (other != playerNum) {
                  if ((copy.handCount[other] + 1) != G.handCount[other]) { // every player gets 1 more card in hand
                    printf("FAIL %d: Other players hand not added correctly\n", i);
                    fflush(stdout);
                    otherError ++;
                    printTwo(&copy, &G);
                  }
                }
              }

              buyCard(rand() % (great_hall + 1), &G); // buy a random card
              playedC = 1;
              // exit loop
              break;
            }
          }

          if (playedC == 0 && numHandCards(&G) > 0) { //play a random card, no council_room in the current hand
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
      if (noDiscard1) printf("Bad discard 1st Half: %d\n", noDiscard1);
      if (noDiscard2) printf("Bad discard 2nd Half: %d\n",noDiscard2);
      if (noDiscardTest) printf("Played card was not discarded: %d\n", noDiscardTest);
      if (currentError) printf("Smithy player error: %d\n", currentError);
      fflush(stdout);
      printTrace("_______________________\n");
    }
    return 0;
  }
