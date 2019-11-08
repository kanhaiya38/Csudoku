#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../headers/stack.h"
#include "../headers/check.h"
#include "../headers/sudokusolver.h"

#define UNASSIGNED 0

/* get_random_int returns a unique random integer from array randomarr
 * which has unique numbers from 1 to len
 * it generates random number-randomindex and returns
 * number at index randomindex of randomarr
 * and swaps that number with  
 */

int get_random_num(int max) {
    /* 25 since max sudoku size is 25
     */
    static unsigned int randomarr[25];
    unsigned int randomindex, swap, randomnum;
    static bool flag = true;
    register int k;

    srand(time(0));

    if(flag) {
        for(k = 0; k < max; k++) {
            /* unique values from 1 to len are stored in randomarr
            */
            randomarr[k] = k + 1;
        }
        flag = false;
    }

    
    randomindex = rand() % max;
    randomnum = randomarr[randomindex];
    swap = randomarr[randomindex];
    randomarr[randomindex] = randomarr[max - 1];
    randomarr[max - 1] = swap;
    return randomnum;
}

/* fill_diagonal fills all the diagonal blocks as
 * all diagonal cells can be filled randomly
 * without any need to check to check if the number is safe or not
 * and always returns true as nothing can be wrong with it
 */
bool fill_diagonal(int **arr, int len) {
    
    unsigned int size;
    unsigned int max;
    unsigned int randomnum;
    register int i, j, k;

    size = (int)sqrt(len);

    for(k = 0; k < size; k++) {
        max = len;
        for(i = k * size; i < (k + 1) * size; i++) {
            for(j = k * size; j < (k + 1) * size; j++) {
                randomnum = get_random_num(max);
                max--;
                arr[i][j] = randomnum;
            }
        }
    }

    return true;
}


bool fill_some_cells(int **arr, int len) {
    register int i, j;
    unsigned int max;
    unsigned int randomnum;
    for(i = 0; i < len; i++){
        max = len;
        for(j = 0; j < len; j++) {
            randomnum = get_random_num(max);
            if(issafe(arr, len, i, j, randomnum)) {
                arr[i][j] = randomnum;
            }
            max--;
        }
    }
    return true;
}

bool generate_seed(int **arr, int len) {

    register int i, j;
    /* Initializes the 2d array.
     */
    for(i = 0; i < len; i++) {
        for(j = 0; j < len; j++) {
            arr[i][j] = UNASSIGNED;
        }
    }
    
    if(len > 4){
        fill_diagonal(arr, len);
    } else {
        fill_some_cells(arr, len);
    }

    // if(len < 25)

    if(valid_sudoku(arr, len)) {
        printf("sudoku is valid\n");
        if(sudoku_solver(arr, len)) {
            printf("sudoku solved\n");
        } else {
            printf("cannot solve sudoku\n");
        }
    } else {
        printf("sudoku is not valid\n");
    }
    
    return true;
    
}

bool remove_k_elements(int **seed_sudoku, int **sudoku, int len) {
    
    
    // get_random_num(max);
    return true;
}

bool sudoku_generator(int **arr, int len) {
    int **seed_sudoku, **sudoku;

    int sudokusize = len;
    register int i;

    /* first allocating memory to store address of integer pointer
     * then allocating each integer pointer memory to store integer
     */
    sudoku = (int **)malloc(sudokusize * sizeof(int *));
    if(sudoku == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return false;
    }
    for (i = 0; i < sudokusize ; i++) {
        sudoku[i] = (int *)malloc(sudokusize * sizeof(int));
        if(sudoku[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return false;
        }
    }


    /* first allocating memory to store address of integer pointer
     * then allocating each integer pointer memory to store integer
     */
    seed_sudoku = (int **)malloc(sudokusize * sizeof(int *));
    if(seed_sudoku == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return false;
    }
    for (i = 0; i < sudokusize ; i++) {
        seed_sudoku[i] = (int *)malloc(sudokusize * sizeof(int));
        if(seed_sudoku[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return false;
        }
    }

    generate_seed(seed_sudoku, len);

    remove_k_elements(sudoku, seed_sudoku, len);


}