/*
Assignment 3, unit test 1
Testing kingdomCards

*
* Include the following lines in your makefile:
*
* unittest1: unittest1.c dominion.o rngs.o
*      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
//#include "dominion.c"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


int main() {
  //--- Test 1, equals
  int cards[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9 , 10};
  int* kTest = kingdomCards(cards[0], cards[1], cards[2], cards[3], cards[4], cards[5], cards[6], cards[7], cards[8], cards[9]);
  int i;
  int success = 0;
  for (i = 0; i < 10; i ++) {
    if (!(cards[i] == kTest[i])) {
      printf("Assert U1.1 failed %d != %d\n", cards[i], kTest[i]);
      success = -1;
    }
  }
  if (success != -1) printf("All clear unittest1.1\n");

  //--- Test 2, not equal

  int* kTest2 = kingdomCards(cards[1], cards[1], cards[2], cards[4], cards[4], cards[5], cards[6], cards[7], cards[8], cards[9]);
  int i;
  int success = 0;
  for (i = 0; i < 10; i ++) {
    if (!(cards[i] == kTest[i])) {
      printf("Assert U1.2 failed %d != %d\n", cards[i], kTest[i]);
      success = -1;
    }
  }
  if (success != -1) printf("All clear unittest1.2\n");
  return 0;
}
