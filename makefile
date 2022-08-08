sdqm.x : sdqm.o matrix.o
	gcc -fopenmp -o sdqm.x sdqm.o matrix.o

sdqm.o : sdqm.c matrix.h
	gcc -fopenmp -c sdqm.c
matrix.o : matrix.c matrix.h
	gcc -fopenmp -c matrix.c
clean :
	rm *.o