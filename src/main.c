#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include "../headers/stack.h"
#include "../headers/sudokusolver.h"
#include "../headers/sudokugenerator.h"
#include "../headers/check.h"
#include "../headers/file.h"


#define UNASSIGNED 0

// bool init_sudoku(int **arr, int len) {

//     /* first allocating memory to store address of integer pointer
//      * then allocating each integer pointer memory to store integer
//      */
//     arr = (int **)malloc(len * sizeof(int *));

//     if(arr == NULL) {
    
//         fprintf(stderr, "Memory allocation failed\n");
    
//         return false;
//     }

//     for (int i = 0; i < len ; i++) {
    
//         arr[i] = (int *)malloc(len * sizeof(int));

//         if(arr[i] == NULL) {
    
//             fprintf(stderr, "Memory allocation failed\n");
    
//             return false;
    
//         }
    
//     }

//     return true;

// }

void blue() {
    printf("\033[0;36m");
}

void green() {
    printf("\033[1;32m");
}

void reset() {
    printf("\033[0m");
}

/* print_sudoku prints len * len sudokuboard
 */
void print_sudoku(int **arr, int len) {

    register int i, j;

    int size = sqrt(len);

    for(i = 0; i <= 2 * len; i++){

        for(j = 0; j < len; j++) {

            if(i % (2 * size) == 0) {
                blue();
                printf("+---");
                if(size > 3) {
                    printf("-");
                }
                reset();
            } else if(i % 2 == 0) {
                if(j % size == 0) {
                    blue();
                    printf("+");
                    green();
                    printf("---");
                    if(size > 3) {
                        printf("-");
                    }
                    reset();
                } else {
                    green();
                    printf("+");
                    printf("---");
                    if(size > 3) {
                        printf("-");
                    }
                    reset();
                }
            } else {
                if(j % size == 0) {
                    blue();
                    printf("|");
                    reset();
                    if(size > 3) {
                        printf(" %2d ", arr[(i - 1) / 2][j]);
                    } else {
                        printf(" %d ", arr[(i - 1) / 2][j]);
                    }
                } else {
                    green();
                    printf("|");
                    reset();
                    if(size > 3) {
                        printf(" %2d ", arr[(i - 1) / 2][j]);
                    } else {
                        printf(" %d ", arr[(i - 1) / 2][j]);
                    }
                }
            }

        }
        if(i % 2 == 0) {
            blue();
            printf("+");
            reset();
        } else {
            blue();
            printf("|");
            reset();
        }
        printf("\n");
    }

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

    int **sudoku = NULL;
    char file_name[128];
    unsigned int sudokusize = 25;
    register int i;

    // scanf("%u", &sudokusize);
    
    strcpy(file_name, "2x2.txt");
    printf("%s is file name\n", file_name);
    if(argc > 2) {
        errno = EINVAL;
        perror("usage");
        return errno;
    }

    // if(!init_sudoku(sudoku, sudokusize)) {
    //     fprintf(stderr, "Not enough memory\n");
    //     return EXIT_FAILURE;
    // }
    
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

    if(argc == 2) {
        
        if(get_sudoku_from_file(sudoku, sudokusize, file_name)) {
            printf("File successfully opened\n");
        } else {
            printf("cannot open file\n");
            return EXIT_FAILURE;
        }
    }

    for(i = 0; i < sudokusize; i++) {
        for(int j = 0; j < sudokusize; j++) {
            sudoku[i][j] = UNASSIGNED;
        }
    }

    // print_sudoku(sudoku, sudokusize);

    // if(!valid_sudoku(sudoku, sudokusize)) {
	// 	printf("not a valid sudoku\n");
    //     return EXIT_FAILURE;
	// }

    // if(sudoku_solver(sudoku, sudokusize)) {

    //     print_sudoku(sudoku, sudokusize);

    // } else {

    //     fprintf(stderr, "Cannot solve input sudoku\n");
    //     return EXIT_FAILURE;

    // }

    // printf("Complete\n");

    if(generate_sudoku(sudoku, sudokusize)) {
        print_sudoku(sudoku, sudokusize);
    } else {
        printf("false\n");
    }

    // print_sudoku(sudoku, sudokusize);
    // if(valid_sudoku(sudoku, sudokusize))
    //     printf("gr8 amn\n");
    free(sudoku);
    return EXIT_SUCCESS;
}
