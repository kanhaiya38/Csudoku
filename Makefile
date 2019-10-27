try : try.o sudokusolver.o sudokugenerator.o check.o stack.o
	gcc -o try try.o sudokusolver.o sudokugenerator.o check.o stack.o -Wall

try.o : try.c
	gcc -c try.c -Wall

sudokusolver.o : sudokusolver.c sudokusolver.h
	gcc -c sudokusolver.c -Wall

sudokugenerator.o : sudokugenerator.c sudokugenerator.h
	gcc -c sudokugenerator.c -Wall

check.o : check.c check.h
	gcc -c check.c -Wall

stack.o : stack.c stack.h
	gcc -c stack.c -Wall