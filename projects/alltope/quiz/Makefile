
CFLAGS = -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme -g testme.c $(CFLAGS)
	testme
	gcov testme.c -b

all: testme

clean:
	rm -f *.o testme *.gcov *.gcda *.gcno
