#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <errno.h>
#include "stack.h"
#include "check.h"

#define SIZE 9
#define UNASSIGNED 0

/* issafe checks if the number num is safe to be filled in the cell.
 * if it is safe it returns true.
 * else returns false.
 */

bool issafe(int** arr, int len, int row, int col, int num) {

    /* checkrow returns true if it is in row.
     * checkcol returns true if it is in column.
     * checkblock returns true if it is in block.
     */

    if(checkrow(arr, len, row, num) || checkcol(arr, len, col, num) || checkblock(arr, len, row, col, num)) {
        return false;
    }

    /* if it isn't in row, column, block it returns true.
     */
    
    return true;
}

int main(int argc, char* argv[]) {

    int** sudoku;

    /* first allocating memory to store address of integer pointer
     * then allocating each integer pointer memory to store integer
     */
    sudoku = (int **)malloc(SIZE * sizeof(int *));
    for (int i = 0; i < SIZE ; i++) {
        sudoku[i] = (int *)malloc(SIZE * sizeof(int));
    }

    /* Initializes the 2d array.
     */

    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            sudoku[i][j] = UNASSIGNED;
        }
    }
    
    sudoku[0][0] = 3;
    sudoku[0][2] = 6;
    sudoku[0][3] = 5;
    sudoku[0][6] = 8;
    sudoku[0][7] = 4;
    sudoku[1][0] = 5;
    sudoku[1][1] = 2;
    sudoku[2][1] = 8;
    sudoku[2][2] = 7;

    // 3, 0, 6, 5, 0, 8, 4, 0, 0
    // 5, 2, 0, 0, 0, 0, 0, 0, 0
    // 0, 8, 7, 0, 0, 0, 0, 3, 1
    // 0, 0, 3, 0, 1, 0, 0, 8, 0
    // 9, 0, 0, 8, 6, 3, 0, 0, 5
    // 0, 5, 0, 0, 9, 0, 6, 0, 0
    // 1, 3, 0, 0, 0, 0, 2, 5, 0
    // 0, 0, 0, 0, 0, 0, 0, 7, 4
    // 0, 0, 5, 2, 0, 6, 3, 0, 0

    if(issafe(sudoku, SIZE, 0, 1, 4)) {
        printf("true\n");
    } else {
        printf("false\n");
    }


    free(sudoku);

    return 0;
}