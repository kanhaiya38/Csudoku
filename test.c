#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "check.h"
#include "stack.h"

#define SIZE 4
#define UNASSIGNED 0

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

int main(){
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
    
    sudoku[0][0] = 1;
    sudoku[0][2] = 3;
    sudoku[1][2] = 2;
    sudoku[1][3] = 1;
    sudoku[2][1] = 1;
    sudoku[2][3] = 2;
    sudoku[3][0] = 2;
    sudoku[3][1] = 4;

    // {
    //     1, 0, 3, 0
    //     0, 0, 2, 1
    //     0, 1, 0, 2
    //     2, 4, 0, 0
    // }

    if(issafe(sudoku, SIZE, 0, 3, 4)) {
        printf("Okay\n");
    }
    // stack s;
    // init(&s);
    // values temp;
    // temp.row = 1;
    // temp.col = 7;
    // temp.num = 3;
    // push(&s, temp);
    // pop(&s);
    
    // return 0;
}