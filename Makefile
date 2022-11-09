all: Zad1
Zad1: Zad1.o
	gcc -o Zad1 Zad1.o 
Zad1.o: Zad1.c 
	gcc -c Zad1.c

clean: 
	rm -f Zad1 *.o
