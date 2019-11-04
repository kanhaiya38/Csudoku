#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "stack.h"
#include "check.h"
#include "sudokusolver.h"

#define UNASSIGNED 0

// int get_random_num(int max) {
//     return rand() % max + 1;
// }

/* fill_diagonal fills all the diagonal blocks as
 * all diagonal cells can be filled randomly
 * without any need to check to check if the number is safe or not
 * and always returns true as nothing can be wrong with it
 */
bool fill_diagonal(int **arr, int len) {
    
    int size;
    int max;
    int randomarr[len], randomnum, randomindex;
    int i, j, k;
    int swap;

    size = (int)sqrt(len);
    // printf("%d is size\n", size);

    srand(time(0));
    
    for(k = 0; k < len; k++) {
        randomarr[k] = k + 1;
    }

    for(i = 0; i < len; i++) {

        if(i % size == 0) {
            max = len;
        }

        for(j = (i / size) * size; j < (i / size + 1) * size; j++) {

            // printf("[");
            // for(k = 0; k < len; k++) {
            //     printf("%d ", randomarr[k]);
            // }
            // printf("]\n");

            randomindex = rand() % max;
            // printf("%d is random index\n", randomindex);
            randomnum = randomarr[randomindex];
            // printf("%d is randomnum\n", randomnum);
            // printf("%d is at randomarr[randomindex]:before\n", randomarr[randomindex]);
            // printf("%d is last:before\n", randomarr[max - 1]);
            swap = randomarr[randomindex];
            // printf("%d is swap\n", swap);
            // printf("%d is max\n", max);
            randomarr[randomindex] = randomarr[max - 1];
            // printf("%d is at randomarr[randomindex]\n", randomarr[randomindex]);
            randomarr[max - 1] = swap;
            // printf("%d is last\n", randomarr[max - 1]);
            max--;

            arr[i][j] = randomnum;
        }
    }

    return true;
}

bool fill_more_cells(int **arr, int len) {
    int size;
    int max;
    int randomarr[len], randomnum, randomindex;
    int i, j, k;
    int swap;

    size = (int)sqrt(len);

    srand(time(0));
    
    for(k = 0; k < len; k++) {
        randomarr[k] = k + 1;
    }

    for(i = 0; i < len; i++) {

        max = len;
        
        for(j = 0; j < len; j++) {
            if(arr[i][j] != UNASSIGNED) {
                continue;
            }
            randomindex = rand() % max;
            randomnum = randomarr[randomindex];
            if(!issafe(arr, len, i, j, randomnum)) {
                continue;
            }
            swap = randomarr[randomindex];
            randomarr[randomindex] = randomarr[max - 1];
            randomarr[max - 1] = swap;
            max--;

            arr[i][j] = randomnum;
        }
    }
    return true;
}

bool generate_sudoku(int **arr, int len, stack s) {
    
    fill_diagonal(arr, len);
    fill_more_cells(arr, len);
    printf("=================\n");
    for(int i = 0; i < len; i++){
        for(int j = 0; j < len; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("=================\n");
    printf("her\n");
    sudoku_solver(arr, len);
    
    // int i = 5;
    // while(i--) {
    //     printf("%d is \n", get_random_num(len));
    // }

    return true;
    
}