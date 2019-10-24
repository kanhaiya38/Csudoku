#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "stack.h"
#include "check.h"

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

/* findemptycell finds the empty cell in the sodoku
 * and returns true if there is an empty cell and
 * the position of the empty cell.
 * If no cell in the sudoku is empty it returns false.
 */

bool findemptycell(int **arr, int len, int *row, int *col) {

    for(int x = 0; x < len; x++) {
        for(int y = 0; y < len; y++) {
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

bool sudokusolver(int **arr, int len, stack s) {

    int row, col;
    static int i = 0;
    values temp;

    /* to get index row, col of empty cell 
     */
    if(!findemptycell(arr, len, &row, &col)) {

        return true;

    }

    // printf("(%d, %d) is an empty cell\n", row, col);

    /* to find safe number at location row, col
    */
    if(!findsafenum(arr, len, row, col, &i)) {

        /* if there is no safe number at that position,
        * it backtracks.
        * but if the stack becomes empty it returns false
        * means the sudoku cannot be solved
        */
        if(!isempty(&s)) {
            temp = pop(&s);
        } else {
            return false;
        }

        arr[temp.row][temp.col] = UNASSIGNED;
        i = temp.num;
        sudokusolver(arr, len, s);

    }

    // printf("%d is safe num\n", i);
    arr[row][col] = i;

    temp.col = col;
    temp.row = row;
    temp.num = arr[row][col];

    if(!isfull(&s)) {
        push(&s, temp);
    } else {
        return false;
    }

    i = 0;
    sudokusolver(arr, len, s);

    return true;
}