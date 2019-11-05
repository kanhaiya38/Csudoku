# change application name here (executable output name)
TARGET = sudoku

# compiler
CC = gcc

# optimisation
OPT = -O

# warnings
WARN = -Wall

CCFLAGS=$(DEBUG) $(OPT) $(WARN)

# linker
LD = gcc

OBJS = main.o sudokusolver.o sudokugenerator.o \
check.o stack.o

all : $(OBJS)
	$(LD) -o $(TARGET) $(OBJS)

main.o : src/main.c
	$(CC) -c $(CCFLAGS) src/main.c

sudokusolver.o : src/sudokusolver.c headers/sudokusolver.h
	$(CC) -c $(CCFLAGS) src/sudokusolver.c

sudokugenerator.o : src/sudokugenerator.c headers/sudokugenerator.h
	$(CC) -c $(CCFLAGS) src/sudokugenerator.c

check.o : src/check.c headers/check.h
	$(CC) -c $(CCFLAGS) src/check.c

stack.o : src/stack.c headers/stack.h
	$(CC) -c $(CCFLAGS) src/stack.c

.PHONY : clean
clean:
	rm *.o $(TARGET)