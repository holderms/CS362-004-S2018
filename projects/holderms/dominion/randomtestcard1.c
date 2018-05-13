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

// void printGameState(struct gameState * thisGame) {
//   // printf("num players in print: %d\n", thisGame->numPlayers);
//
//   printf("Played cards (For game, not a specific player): \n\t");
//   int i;
//   for (i = 0; i < thisGame->playedCardCount; i++) {
//     printf("%d\t", thisGame->playedCards[i]);
//   }
//
//   int p, curr = whoseTurn(thisGame);
//   for (p = 0; p < thisGame->numPlayers; p++) {
//     int c;
//     printf("\nPlayer %d: \n", p);
//     if (p == curr) printf("Current player\n");
//     printf("Hand %d: \n\t", thisGame->handCount[p]);
//     for (c = 0; c < thisGame->handCount[p]; c++) {
//       printf("%d\t", thisGame->hand[p][c]);
//     }
//     printf("\nDeck %d: \n\t", thisGame->deckCount[p]);
//     for (c = 0; c < thisGame->deckCount[p]; c++) {
//       printf("%d\t", thisGame->deck[p][c]);
//     }
//     printf("\nDiscard: \n\t");
//     for (c = 0; c < thisGame->discardCount[p]; c++) {
//       printf("%d\t", thisGame->discard[p][c]);
//     }
//   }
//
//   printf("\nSupply Counts\n");
//   int j;
//   for (j = 0; j < treasure_map + 1; j ++) {
//     if(thisGame->supplyCount[j] > -1) printf("SCard %d = %d\n", j, thisGame->supplyCount[j]);
//   }
//   printf("\n");
// }
//
// void printTwo(struct gameState * previousGame, struct gameState * thisGame) {
//   printf("Previous Game State\n");
//   printGameState(previousGame);
//   printf("\nCurrent Game State\n");
//   printGameState(thisGame);
// }

int main() {
  printf("!____________Random Card Test 1 - Council Room__________!\n");
  int seed = 1000;
  srand(time(NULL));
  int numPlayers = 2;
  struct gameState G, copy;
  int noUpdate = 0, currentError = 0, otherError = 0, noDiscard = 0; //count number of failures
  // Deck is now supply cards 0 - 16
  int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

    initializeGame(numPlayers, k, seed, &G);
    // printf("Initial game\n_______________________\n");
    // printGameState(&G);

    int i = 0;
    // while the gamestate is still playable, try testing 50 times
    // randomization comes from normal game play, deck could be changed by other
    // cards or players
    while (isGameOver(&G) == 0 && i < 50) {
      //stack coins to progress game faster (makes buying easier)
      G.coins += 3;
      int playedC = 0;
      int j, cards = numHandCards(&G);



        for (j = 0; j < cards; j++) {
          if (handCard(j, &G) == council_room) {
            int playerNum = G.whoseTurn;
            // Begin Testing
            memcpy(&copy, &G, sizeof(struct gameState));
            printf("Playing council_room\n");
            playCard(j, 0, 0, 0, &G);
            // check for fails
            if (memcmp(&copy, &G, sizeof(struct gameState)) == 0) {
              //failed, gameState should be different now
              printf("FAIL %d: Game state not updated: \n", i);
              // printTwo(&copy, &G);
              noUpdate ++;
            }
            if (copy.hand[playerNum] == G.hand[playerNum]) {
              printf("FAIL %d: Council Room may not have been discarded (or duplicate cards, not an error)\n", i);
              noDiscard ++;
              // printTwo(&copy, &G);
            }
            if ((copy.handCount[playerNum] + 3) != G.handCount[playerNum]) { // + 3 = +4 new cards - 1 discard
              printf("FAIL %d: CURRENT player cards not added correctly\n", i);
              currentError ++;
              // printTwo(&copy, &G);
            }
            int other;
            for (other = 0; other < G.numPlayers; other ++) {
              if (other != playerNum) {
                if ((copy.handCount[other] + 1) != G.handCount[other]) { // every player gets 1 more card in hand
                  printf("FAIL %d: Other players hand not added correctly\n", i);
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

        if (playedC == 0) { //play a random card, no council_room in the current hand
          playCard((rand() % cards), 0, 1, 2, &G);
          buyCard(council_room, &G); //try to buy a council_room card
        }
        // advance turns
        endTurn(&G);
        // printf("\nGame State \n____________%d___________\n", i);
        // printGameState(&G);

      i ++;
    }
    printf("Final Game State\n_______________________\n");
    printGameState(&G);
    printf("\n Failure Counts\n");
    printf("No updates: %d\nBad discard: %d\n", noUpdate, noDiscard);
    printf("Council player error: %d\nOther player error: %d\n", currentError, otherError);
    return 0;
  }
