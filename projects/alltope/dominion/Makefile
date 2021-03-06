CFLAGS = -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	cardtest1
	gcov cardtest1.c -b

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	cardtest2
	gcov cardtest2.c -b

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	cardtest3
	gcov cardtest3.c -b

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	cardtest4
	gcov cardtest4.c -b

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	unittest1
	gcov unittest1.c -b

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	unittest2
	gcov unittest2.c -b

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	unittest3
	gcov unittest3.c -b

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	unittest4
	gcov unittest4.c -b

unittestresults.out: cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4 dominion.o rngs.o
	echo "Result for running unit tests:" > unittestresults.out

	echo "cardtest1.c:" >> unittestresults.out
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov cardtest1.c -b >> unittestresults.out
	
	echo "cardtest2.c:" >> unittestresults.out
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov cardtest2.c -b >> unittestresults.out
	
	echo "cardtest3.c:" >> unittestresults.out
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	cardtest3 >> unittestresults.out
	gcov cardtest3.c -b >> unittestresults.out
	
	echo "cardtest4.c:" >> unittestresults.out
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	cardtest4 >> unittestresults.out
	gcov cardtest4.c -b >> unittestresults.out
	
	echo "unittest1.c:" >> unittestresults.out
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	unittest1 >> unittestresults.out
	#gcov unittest1.c -b >> unittestresults.out
	gcov -abcfu dominion.c
	
	echo "unittest2.c:" >> unittestresults.out
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	unittest2 >> unittestresults.out
	gcov unittest2.c -b >> unittestresults.out
	
	echo "unittest3.c:" >> unittestresults.out
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	unittest3 >> unittestresults.out
	gcov unittest3.c -b >> unittestresults.out
	
	echo "unittest4.c:" >> unittestresults.out
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	unittest4 >> unittestresults.out
	gcov unittest4.c -b >> unittestresults.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittestresults.out cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4
