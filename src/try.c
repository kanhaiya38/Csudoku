#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include "stack.h"
#include "sudokusolver.h"
#include "sudokugenerator.h"
#include "check.h"


#define UNASSIGNED 0


void print_sudoku(int **arr, int len) {

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
    FILE *fpproblem, *fpsolution;
	char ch;
    unsigned int sudokusize = 9;

    if(argc > 2) {
        errno = EINVAL;
        perror("usage");
        return errno;
    }

    /*opening the file.
     */
    fpproblem = fopen(argv[1], "r");
    // fpsolve = fopen(argv[2], "r");

    /* checking if the file is opened
     */
    if(fpproblem == NULL) {
        fprintf(stderr, "cannot open file %s\n", argv[1]);
        return errno;
    }

    // if(fpsolve == NULL) {
    //     fprintf(stderr, "cannot open file %s\n", argv[1]);
    //     return errno;
    // }

    while(!feof(fpproblem)) {
        ch = fgetc(fpproblem);
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
			while(!feof(fpproblem)) {
				ch = fgetc(fpproblem);
				if(isdigit(ch)) {
					break;
				}
			}
            sudoku[i][j] = ch - '0';
		}
	}
    
    print_sudoku(sudoku, sudokusize);

    if(!valid_sudoku(sudoku, sudokusize)) {
		printf("not a valid sudoku\n");
        exit(EXIT_FAILURE);
	}

    if(sudoku_solver(sudoku, sudokusize)) {

        print_sudoku(sudoku, sudokusize);

    } else {

        fprintf(stderr, "Cannot solve input sudoku\n");
        exit(EXIT_FAILURE);

    }

    printf("Complete\n");

    // solution = (int **)malloc(sudokusize * sizeof(int *));
    // for (int i = 0; i < sudokusize ; i++) {
    //     solution[i] = (int *)malloc(sudokusize * sizeof(int));
    // }

	// for(int i = 0; i < sudokusize; i++) {
	// 	for(int j = 0; j < sudokusize; j++) {
	// 		while(!feof(fpsolve)) {
	// 			ch = fgetc(fpsolve);
	// 			if(isdigit(ch)) {
	// 				break;
	// 			}
	// 		}
    //         solution[i][j] = ch - '0';
	// 	}
	// }

    // if(comparesudoku(sudoku, solution, sudokusize)) {
    //     printf("correctly solved\n");
    // }
    free(sudoku);
    // free(solution);

    fclose(fpproblem);



    // if(generate_sudoku(sudoku, sudokusize)) {
    //     printsudoku(sudoku, sudokusize);
    // } else {
    //     printf("false\n");
    // }

    return 0;
}
