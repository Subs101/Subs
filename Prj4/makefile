all: TSP.x Arr.o

TSP.x: TSP.c Arr.o
	gcc -g -o TSP.x TSP.c Arr.o -lrt -lm
	
Arr.o: Arr.c Arr.h
	gcc -g -c Arr.c -lrt
		
clean:
	rm *.o *.x
