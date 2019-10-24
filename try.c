#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include "stack.h"
#include "sudokusolver.h"
#include "check.h"


#define UNASSIGNED 0

// values peek(stack *s) {

//     values val = pop(s);
//     push(s, val);
//     printf("(%d, %d, %d) is the top\n", val.row, val.col, val.num);
//     return val;

// }


void printsudoku(int **arr, int len) {

    printf("=================\n");
    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("=================\n");

}

/* validatesudoku checks if the input sudoku is valid or not.
 * if it is valid it returns true
 * else it returns false.
 */
bool validatesudoku(int **arr, int len) {
    int temp;
	for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            temp = arr[i][j];
            arr[i][j] = 0;
			if(temp == 0) {
				continue;
			}
            if(!issafe(arr, len, i, j, temp)) {
				return false;
			}
            arr[i][j] = temp;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {

    int** sudoku;
    stack s;
    FILE *fp;
	char ch;
    unsigned int sudokusize;

    if(argc > 2) {
        errno = EINVAL;
        perror("usage");
        return errno;
    }

    /*opening the file.
     */
    fp = fopen(argv[1], "r");

    /* checking if the file is opened
     */
    if(fp == NULL) {
        fprintf(stderr, "cannot open file %s\n", argv[1]);
        return errno;
    }

    while(!feof(fp)) {
        ch = fgetc(fp);
        if(isdigit(ch)) {
            break;
        }
    }
    sudokusize = ch - '0';
    printf("%d is sudoku size\n", sudokusize);

    /* first allocating memory to store address of integer pointer
     * then allocating each integer pointer memory to store integer
     */
    sudoku = (int **)malloc(sudokusize * sizeof(int *));
    for (int i = 0; i < sudokusize ; i++) {
        sudoku[i] = (int *)malloc(sudokusize * sizeof(int));
    }

    /* Initializes the 2d array.
     */
    for(int i = 0; i < sudokusize; i++) {
        for(int j = 0; j < sudokusize; j++) {
            sudoku[i][j] = UNASSIGNED;
        }
    }
    
    /* getting input from a file in the sudoku
     */
	for(int i = 0; i < sudokusize; i++) {
		for(int j = 0; j < sudokusize; j++) {
			while(!feof(fp)) {
				ch = fgetc(fp);
				if(isdigit(ch)) {
					break;
				}
			}
            sudoku[i][j] = ch - '0';
		}
	}

    init(&s);
    
    printsudoku(sudoku, sudokusize);

	if(!validatesudoku(sudoku, sudokusize)) {
		printf("not a valid sudoku\n");
        exit(EXIT_FAILURE);
	}


    if(sudokusolver(sudoku, sudokusize, s)) {

        printsudoku(sudoku, sudokusize);

    } else {

        printf("error\n");
        exit(EXIT_FAILURE);

    }
    // int row = 0, col = 0;
    // while(findemptycell(sudoku, sudokusize, &row, &col)) {
    //     printf("(%d, %d) is an empty cell\n", row, col);
    //     sudoku[row][col] = 5;
    // }

    printf("Complete\n");
    
    free(sudoku);

    fclose(fp);

    return 0;
}