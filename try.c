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



bool comparesudoku(int **arr1, int **arr2, int len) {
    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            if(arr1[i][j] != arr2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char* argv[]) {

    int **sudoku, **solution;
    stack s;
    FILE *fp, *fpsolve;
	char ch;
    unsigned int sudokusize;

    if(argc > 3) {
        errno = EINVAL;
        perror("usage");
        return errno;
    }

    /*opening the file.
     */
    fp = fopen(argv[1], "r");
    fpsolve = fopen(argv[2], "r");

    /* checking if the file is opened
     */
    if(fp == NULL) {
        fprintf(stderr, "cannot open file %s\n", argv[1]);
        return errno;
    }

    if(fpsolve == NULL) {
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

    // /* Initializes the 2d array.
    //  */
    // for(int i = 0; i < sudokusize; i++) {
    //     for(int j = 0; j < sudokusize; j++) {
    //         sudoku[i][j] = UNASSIGNED;
    //     }
    // }
    
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


    if(sudokusolver(sudoku, sudokusize, s)) {

        printsudoku(sudoku, sudokusize);

    } else {

        printf("error\n");
        exit(EXIT_FAILURE);

    }

    printf("Complete\n");

    solution = (int **)malloc(sudokusize * sizeof(int *));
    for (int i = 0; i < sudokusize ; i++) {
        solution[i] = (int *)malloc(sudokusize * sizeof(int));
    }

	for(int i = 0; i < sudokusize; i++) {
		for(int j = 0; j < sudokusize; j++) {
			while(!feof(fpsolve)) {
				ch = fgetc(fpsolve);
				if(isdigit(ch)) {
					break;
				}
			}
            solution[i][j] = ch - '0';
		}
	}

    if(comparesudoku(sudoku, solution, sudokusize)) {
        printf("correctly solved\n");
    }
    free(sudoku);
    free(solution);

    fclose(fp);

    return 0;
}
