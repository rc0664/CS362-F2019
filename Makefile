all:
	gcc	-o	testme	testme.c -ftest-coverage -fprofile-arcs
	./testme
	gcov testme.c -b -f
clean:
	rm	-f testme *.exe *.gcda *.gcno *.c.gcov