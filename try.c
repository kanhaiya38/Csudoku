#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <errno.h>
#include "stack.h"
#include "check.h"

#define SIZE 4
#define UNASSIGNED 0

values peek(stack *s) {
    values val = pop(s);
    push(s, val);
    printf("(%d, %d, %d) is the top\n", val.row, val.col, val.num);
    return val;
}

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

/* findemptycell finds the empty cell in the sodoku
 * and returns true if there is an empty cell and
 * the position of the empty cell.
 * If no cell in the sudoku is empty it returns false.
 */

bool findemptycell(int **arr, int len, int *row, int *col) {
    for(int x = 0; x < len; x++) {
        for(int y = 0; y < len; y++) {
            // printf("x - %d, y - %d\n", x, y);
            if(checkemptycell(arr, len, x, y)) {
                *row = x;
                *col = y;
                return true;
            }
        }
    }

    return false;
}

/* findsafenum finds the safe number for that empty cell and returns true.
 * if there's no safe number then it returns false. 
 */

bool findsafenum(int **arr, int len, int row, int col, int *i) {
    for(int j = *i + 1; j <= len; j++) {
        // printf("iterations %d\n", j);
        if(issafe(arr, len, row, col, j)) {
            *i = j;
            return true;
        }
    }
    // printf("now its false\n");
    return false;
}

/* sudokusolver solves the sudoku and 
 * returns true if the sudoku is solved.
 * else returns false means sudoku can't be solved
 */

bool sudokusolver(int **arr, int len) {
    int row, col;
    int i = 0;
    
    if(!findemptycell(arr, len, &row, &col)) {
        return true;
    }

    printf("(%d, %d) is an empty cell\n", row, col);
    
    if(!findsafenum(arr, len, row, col, &i)) {
        return false;
    }

    printf("%d is safe num\n", i);

    arr[row][col] = i;
    sudokusolver(arr, len);

    return true;
}

void printsudoku(int **arr, int len) {
    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
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
    
    sudoku[0][0] = 1;
    sudoku[0][2] = 3;
    sudoku[1][0] = 4;
    sudoku[1][2] = 2;
    sudoku[1][3] = 1;
    sudoku[2][1] = 1;
    sudoku[2][3] = 2;
    sudoku[3][0] = 2;
    sudoku[3][1] = 4;

    // {
    //     1, 0, 3, 0
    //     4, 0, 2, 1
    //     0, 1, 0, 2
    //     2, 4, 0, 0
    // }
        printsudoku(sudoku, SIZE);

    if(sudokusolver(sudoku, SIZE)) {
        printsudoku(sudoku, SIZE);
    } else {
        printf("error\n");
    }

    printf("Hello");
    
    free(sudoku);

    return 0;
}