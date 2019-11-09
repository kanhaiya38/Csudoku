# change application name here (executable output name)
TARGET = sudoku

# compiler
CC = gcc

# gdb
DEBUG = -g

# optimisation
OPT = -O

# warnings
WARN = -Wall

CCFLAGS=$(DEBUG) $(OPT) $(WARN)

# linker
LD = -lm

OBJS = main.o sudokusolver.o sudokugenerator.o \
check.o stack.o file.o menu.o print.o game.o baseseed.o

all : $(OBJS)
	$(CC) -o $(TARGET) $(CCFLAGS) $(OBJS) $(LD)

print.o : src/print.c headers/print.h
	$(CC) -c $(CCFLAGS) src/print.c

main.o : src/main.c headers/print.h
	$(CC) -c $(CCFLAGS) src/main.c
	
menu.o : src/menu.c headers/menu.h
	$(CC) -c $(CCFLAGS) src/menu.c

file.o : src/file.c headers/file.h
	$(CC) -c $(CCFLAGS) src/file.c


game.o : src/game.c headers/game.h
	$(CC) -c $(CCFLAGS) src/game.c

sudokusolver.o : src/sudokusolver.c headers/sudokusolver.h
	$(CC) -c $(CCFLAGS) src/sudokusolver.c

baseseed.o : src/baseseed.c headers/baseseed.h
	$(CC) -c $(CCFLAGS) src/baseseed.c

sudokugenerator.o : src/sudokugenerator.c headers/sudokugenerator.h
	$(CC) -c $(CCFLAGS) src/sudokugenerator.c

check.o : src/check.c headers/check.h
	$(CC) -c $(CCFLAGS) src/check.c

stack.o : src/stack.c headers/stack.h
	$(CC) -c $(CCFLAGS) src/stack.c

.PHONY : clean
clean:
	rm *.o $(TARGET)
