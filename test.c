#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "check.h"
#include "stack.h"

// #define SIZE 4
// #define UNASSIGNED 0

// bool issafe(int** arr, int len, int row, int col, int num) {

//     /* checkrow returns true if it is in row.
//      * checkcol returns true if it is in column.
//      * checkblock returns true if it is in block.
//      */


//     if(checkrow(arr, len, row, num) || checkcol(arr, len, col, num) || checkblock(arr, len, row, col, num)) {
//         return false;
//     }

//     /* if it isn't in row, column, block it returns true.
//      */
    
//     return true;
// }

// bool checkblock(int **arr, int len, int row, int col, int num) {
//     int left, right, top, bottom;
//     int size = (int)sqrt(len);

//     /* to find the boundaries of the block.
//     */

//     left = (col / size) * size;
//     right = left + size;
//     top = (row / size) * size;
//     bottom = top + size;
    
//     /* to find if the num is in the block.
//     */

//     for(int i = top; i < bottom; i++) {
//         for(int j = left; j < right; j++) {
//             if(arr[i][j] == num) {
//                 return true;
//             }
//         }
//     }

//     return false;
// }

// bool findsafenum(int **arr, int len, int row, int col, int *i) {
//     for(int j = *i + 1; j <= len; j++) {
//         printf("iterations %d\n", j);
//         if(issafe(arr, len, row, col, j)) {
//             *i = j;
//             return true;
//         }
//     }
//     printf("now its false\n");
//     return false;
// }

// int main(int argc, char* argv[]) {

//     int** sudoku;

//     /* first allocating memory to store address of integer pointer
//      * then allocating each integer pointer memory to store integer
//      */
//     sudoku = (int **)malloc(SIZE * sizeof(int *));
//     for (int i = 0; i < SIZE ; i++) {
//         sudoku[i] = (int *)malloc(SIZE * sizeof(int));
//     }

//     /* Initializes the 2d array.
//      */

//     for(int i = 0; i < SIZE; i++) {
//         for(int j = 0; j < SIZE; j++) {
//             sudoku[i][j] = UNASSIGNED;
//         }
//     }
    
//     sudoku[0][0] = 1;
//     sudoku[0][2] = 3;
//     sudoku[1][0] = 4;
//     sudoku[1][2] = 2;
//     sudoku[1][3] = 1;
//     sudoku[2][1] = 1;
//     sudoku[2][3] = 2;
//     sudoku[3][0] = 2;
//     sudoku[3][1] = 4;

//     // {
//     //     1, 0, 3, 0
//     //     4, 0, 2, 1
//     //     0, 1, 0, 2
//     //     2, 4, 0, 0
//     // }
//     int i = 0;

//     // for(int a = 0; a < SIZE; a++) {
//     //     for(int b = 0; b < SIZE; b++) {
//     //         checkblock(sudoku, SIZE, a, b, 1);
//     //     }
//     // }

//     if(checkblock(sudoku, SIZE, 0, 3, 4))
//         printf("true\n");
//     else 
//         printf("false\n");

//     // if(findsafenum(sudoku, SIZE, 0, 3, &i))
//     //     printf("%d is safe num\n");
    
//     free(sudoku);

//     return 0;
// }
values peek(stack *s) {
    values val = pop(s);
    push(s, val);
    printf("(%d, %d, %d) is the top\n", val.row, val.col, val.num);
    return val;
}
int main() {
    stack s;
    values val;
    init(&s);
    val.row = 1;
    val.col = 2;
    val.num = 3;

    push(&s, val);
    val.row = 3;
    val.col = 4;
    val.num = 5;

    push(&s, val);
    peek(&s);
    pop(&s);
    return 0;
}