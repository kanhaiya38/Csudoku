#include <stdio.h>
#include <math.h>
#include "../headers/print.h"

static inline void green() {
    printf("\033[0;36m");
}

static inline void blue() {
    printf("\033[1;32m");
}

static inline void reset() {
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