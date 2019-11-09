#include <stdio.h>
#include <math.h>
#include "../headers/print.h"

#define UNASSIGNED 0

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

        if(i == 0) {
            printf(" ");
            for(int p = 0; p < len; p++) {
                printf("   %c", 'a' + p);
                if(len > 9)
                    printf(" ");
            }
            printf("\n");
        }

        for(j = 0; j < len; j++) {

            if(i % (2 * size) == 0) {
                if(j == 0)
                    printf("  ");
                blue();
                printf("+---");
                if(size > 3) {
                    printf("-");
                }
                reset();
            } else if(i % 2 == 0) {
                if(j == 0) {
                    printf("  ");
                }
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
                if(j == 0)
                    printf("%c ", 'a' + (i - 1) / 2);
                if(j % size == 0) {
                    blue();
                    printf("|");
                    reset();
                    if(size > 3) {
                        // if(arr[(i - 1) / 2][j] == UNASSIGNED) {
                        //     printf(" xx ");
                        // } else {
                            printf(" %2d ", arr[(i - 1) / 2][j]);
                        // }
                    } else {
                        // if(arr[(i - 1) / 2][j] == UNASSIGNED) {
                        //     printf(" x ");
                        // } else {
                            printf(" %d ", arr[(i - 1) / 2][j]);
                        // }
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