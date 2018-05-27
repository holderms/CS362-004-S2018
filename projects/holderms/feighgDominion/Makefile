CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

runAll: cardtest1 cardtest2	cardtest3	cardtest4 unittest1 unittest2 unittest3 unittest4 randomtestcard1 randomtestcard2 randomtestadventurer
	
cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)
	./cardtest1 &> cardtest1.out
	gcov -b dominion.c >> cardtest1.out
	cat dominion.c.gcov >> cardtest1.out

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)
	./cardtest2 &> cardtest2.out
	gcov -b dominion.c >> cardtest2.out
	cat dominion.c.gcov >> cardtest2.out

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)
	./cardtest3 &> cardtest3.out
	gcov -b dominion.c >> cardtest3.out
	cat dominion.c.gcov >> cardtest3.out

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)
	./cardtest4 &> cardtest4.out
	gcov -b dominion.c >> cardtest4.out
	cat dominion.c.gcov >> cardtest4.out

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
	./unittest1 &> unittest1.out
	gcov -b dominion.c >> unittest1.out
	cat dominion.c.gcov >> unittest1.out

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
	./unittest2 &> unittest2.out
	gcov -b dominion.c >> unittest2.out
	cat dominion.c.gcov >> unittest2.out

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)
	./unittest3 &> unittest3.out
	gcov -b dominion.c >> unittest3.out
	cat dominion.c.gcov >> unittest3.out

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)
	./unittest4 &> unittest4.out
	gcov -b dominion.c >> unittest4.out
	cat dominion.c.gcov >> unittest4.out

printGame: printGame.h printGame.c dominion.o rngs.o
	gcc -o prinprintGametable -g printGame.c dominion.o rngs.o

randomtestcard1: randomtestcard1.c dominion.o rngs.o printGame.o
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o printGame.o $(CFLAGS)
	./randomtestcard1 &> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2: randomtestcard2.c dominion.o rngs.o printGame.o
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o printGame.o $(CFLAGS)
	./randomtestcard2 &> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o printGame.o
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o printGame.o $(CFLAGS)
	./randomtestadventurer &> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
# interface.o: interface.h interface.c
# 	gcc -c interface.c -g  $(CFLAGS)
#
# runtests: testDrawCard
# 	./testDrawCard &> unittestresult.out
# 	gcov dominion.c >> unittestresult.out
# 	cat dominion.c.gcov >> unittestresult.out
#
# player: player.c interface.o
# 	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)
#
# playdom: dominion.o playdom.c
# 	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
# #To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
# testDrawCard: testDrawCard.c dominion.o rngs.o
# 	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)
#
# badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
# 	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)
#
# testBuyCard: testDrawCard.c dominion.o rngs.o
# 	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)
#
# testAll: dominion.o testSuite.c
# 	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)
# all: playdom player

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
