all: changedp.x changeslow.x changegreedy.x timeanalysis.x

change_alg.o: change_alg.c change_alg.h
	gcc -g -c change_alg.c -lrt
	
changedp.x: changedp.c Arr.o change_alg.o
	gcc -g -o changedp.x Arr.o change_alg.o changedp.c -lrt
	
changeslow.x: changeslow.c Arr.o change_alg.o
	gcc -g -o changeslow.x Arr.o change_alg.o changeslow.c -lrt

changegreedy.x: changegreedy.c Arr.o change_alg.o
	gcc -g -o changegreedy.x Arr.o change_alg.o changegreedy.c -lrt
	
timeanalysis.x: timeanalysis.c Arr.o change_alg.o
	gcc -g -o timeanalysis.x Arr.o change_alg.o timeanalysis.c -lrt
	
Arr.o: Arr.c change_alg.h
	gcc -g -c Arr.c -lrt
	

		
clean:
	rm *.o *.x
