CFLAGS= -Wall -fpic -coverage -lm -std=c99
testme: testme.c
	gcc	-o	testme	testme.c -g $(CFLAGS)
	testme >> testmeresult.out
results: testme.c
	gcov -b -f testme.c >> testmegcov.out
all: testme results
clean:
	rm	-f testme *.exe *.gcda *.gcno *.c.gcov