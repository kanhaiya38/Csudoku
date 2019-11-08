#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../headers/sudokugenerator.h"
#include "../headers/game.h"
#include "../headers/print.h"

bool sudoku_game(int len) {
    register int i;
    int **problem_sudoku, **seed_sudoku;
    // print_sudoku_game_help();

    /* first allocating memory to store address of integer pointer
     * then allocating each integer pointer memory to store integer
     */
    problem_sudoku = (int **)malloc(len * sizeof(int *));
    if(problem_sudoku == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return false;
    }
    for (i = 0; i < len ; i++) {
        problem_sudoku[i] = (int *)malloc(len * sizeof(int));
        if(problem_sudoku[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return false;
        }
    }


    /* first allocating memory to store address of integer pointer
     * then allocating each integer pointer memory to store integer
     */
    seed_sudoku = (int **)malloc(len * sizeof(int *));
    if(seed_sudoku == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return false;
    }
    for (i = 0; i < len ; i++) {
        seed_sudoku[i] = (int *)malloc(len * sizeof(int));
        if(seed_sudoku[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return false;
        }
    }

    sudoku_generator(problem_sudoku, seed_sudoku, len);
    print_sudoku(problem_sudoku, len);
    puts("yeah");
    return false;
}