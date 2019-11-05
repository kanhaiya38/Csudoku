#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "../headers/stack.h"
#include "../headers/check.h"


#define UNASSIGNED 0


/* issafe checks if the number num is safe to be filled in the cell.
 * if it is safe it returns true.
 * else returns false.
 */

bool issafe(int** arr, int len, int row, int col, int num) {

    /* check_row returns true if it is in row.
     * check_col returns true if it is in column.
     * check_block returns true if it is in block.
     */

    if(check_row(arr, len, row, num) || check_col(arr, len, col, num) || check_block(arr, len, row, col, num)) {

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

bool find_empty_cell(int **arr, int len, int *row, int *col) {

    for(int x = 0; x < len; x++) {
        for(int y = 0; y < len; y++) {
            if(check_empty_cell(arr, len, x, y)) {
             
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

bool find_safe_num(int **arr, int len, int row, int col, int *i) {

    for(int j = *i + 1; j <= len; j++) {

        if(issafe(arr, len, row, col, j)) {
            *i = j;
            return true;

        }
    }
    // printf("now its false\n");
    return false;
}

/* validatesudoku checks if the input sudoku is valid or not.
 * if it is valid it returns true
 * else it returns false.
 */
bool valid_sudoku(int **arr, int len) {
    int temp;
	for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            temp = arr[i][j];
            arr[i][j] = 0;
			if(temp == 0) {
				continue;
			}
            if(!issafe(arr, len, i, j, temp)) {
                printf("%d, %d is wrong\n", i, j);
				return false;
			}
            arr[i][j] = temp;
        }
    }
    return true;
}

/* sudokusolver solves the sudoku and 
 * returns true if the sudoku is solved.
 * else returns false means sudoku can't be solved
 */

bool sudoku_solver(int **arr, int len) {

    int row, col;
    static int i = 0;
    values temp;
    stack s;
    init(&s);

    /* to get index row, col of empty cell 
     */
    while(find_empty_cell(arr, len, &row, &col)) {
        // printf("(%d, %d) is an empty cell\n", row, col);

        /* to find safe number at location row, col
        */
        if(find_safe_num(arr, len, row, col, &i)) {

            // printf("%d is safe num\n", i);
            arr[row][col] = i;
            i = 0;

            temp.col = col;
            temp.row = row;
            temp.num = arr[row][col];


            if(!isfull(&s)) {
                push(&s, temp);
            } else {
                return false;
            }
        } else {
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
            
        }
    }
    return true;
}