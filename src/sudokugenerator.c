// #include <stdio.h>
// #include <stdbool.h>
// #include <stdlib.h>
// #include <math.h>
// #include <time.h>
// #include "../headers/stack.h"
// #include "../headers/check.h"
// #include "../headers/sudokusolver.h"
// #include "../headers/print.h"

// #define UNASSIGNED 0

// /* get_random_int returns a unique random integer from array randomarr
//  * which has unique numbers from 1 to len
//  * it generates random number-randomindex and returns
//  * number at index randomindex of randomarr
//  * and swaps that number with  
//  */

// unsigned int get_random_num(unsigned int max) {
//     /* 25 since max sudoku size is 25
//      */
//     static unsigned int randomarr[25];
//     unsigned int randomindex, swap, randomnum;
//     static bool flag = true;
//     register int k;
//     time_t tt;
//     srand(time(&tt));

//     if(flag) {
//         for(k = 0; k < max; k++) {
//             /* unique values from 1 to len are stored in randomarr
//             */
//             randomarr[k] = k + 1;
//         }
//         flag = false;
//     }

    
//     randomindex = rand() % max;
//     randomnum = randomarr[randomindex];
//     swap = randomarr[randomindex];
//     randomarr[randomindex] = randomarr[max - 1];
//     randomarr[max - 1] = swap;
//     return randomnum;
// }

// void copy_sudoku(int **seed_sudoku, int **problem_sudoku, int len) {
//     register int i , j;

//     for(i = 0; i < len; i++) {
//         for(j = 0; j < len; j++) {
//             problem_sudoku[i][j] = seed_sudoku[i][j];
//         }
//     }
// }

// /* fill_diagonal fills all the diagonal blocks as
//  * all diagonal cells can be filled randomly
//  * without any need to check to check if the number is safe or not
//  * and always returns true as nothing can be wrong with it
//  */
// bool fill_diagonal(int **arr, int len) {
    
//     unsigned int size;
//     unsigned int max;
//     unsigned int randomnum;
//     register int i, j, k;

//     size = (int)sqrt(len);

//     for(k = 0; k < size; k++) {
//         max = len;
//         for(i = k * size; i < (k + 1) * size; i++) {
//             for(j = k * size; j < (k + 1) * size; j++) {
//                 randomnum = get_random_num(max);
//                 max--;
//                 arr[i][j] = randomnum;
//             }
//         }
//     }

//     return true;
// }


// bool fill_some_cells(int **arr, int len) {
//     register int i, j;
//     unsigned int max;
//     unsigned int randomnum;
//     for(i = 0; i < 1; i++){
//         max = len;
//         for(j = 0; j < len; j++) {
//             randomnum = get_random_num(max);
//             if(issafe(arr, len, i, j, randomnum)) {
//                 arr[i][j] = randomnum;
//             }
//             max--;
//         }
//     }
//     return true;
// }

// bool generate_seed(int **arr, int len) {

//     register int i, j;
//     /* Initializes the 2d array.
//      */
//     for(i = 0; i < len; i++) {
//         for(j = 0; j < len; j++) {
//             arr[i][j] = UNASSIGNED;
//         }
//     }
    
//     if(len > 4){
//         fill_diagonal(arr, len);
//     } else {
//         fill_some_cells(arr, len);
//     }

//     // print_sudoku(arr, len);

//     // if(len < 25)

//     if(valid_sudoku(arr, len)) {
//         printf("sudoku is valid\n");
//         if(sudoku_solver(arr, len)) {
//             printf("sudoku solved\n");
//         } else {
//             printf("cannot solve sudoku\n");
//         }
//     } else {
//         printf("sudoku is not valid\n");
//     }
    
//     return true;
    
// }

// void remove_k_elements(int **arr, int len, unsigned int k) {
    
//     unsigned int row, col;

//     while(k) {
//         row = rand() % (len - 1) + 1;
//         col = rand() % (len - 1) + 1;
//         arr[row][col] = UNASSIGNED;
//         k--;
//     }
// }

// bool sudoku_generator(int **problem_sudoku, int **seed_sudoku, int len) {

//     unsigned int k;

//     generate_seed(seed_sudoku, len);

//     /* copying all elements of seed_sudoku to problem_sudoku
//      */
//     copy_sudoku(seed_sudoku, problem_sudoku, len);

//     k = (len * len / 2) + (len * len / 4);
//     k = 5;
//     // printf("removing %u elem\n", k);

//     remove_k_elements(problem_sudoku, len, k);

//     return true;
// }

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../headers/stack.h"
#include "../headers/check.h"
#include "../headers/sudokusolver.h"
#include "../headers/print.h"
#include "../headers/baseseed.h"

#define UNASSIGNED 0

/* get_random_int returns a unique random integer from array randomarr
 * which has unique numbers from 1 to len
 * it generates random number-randomindex and returns
 * number at index randomindex of randomarr
 * and swaps that number with  
 */

unsigned int get_random_num(unsigned int min, unsigned int max) {
    /* 25 since max sudoku size is 25
     */
    unsigned int randomnum;

    randomnum = rand() % (max - min + 1) + min;

    return randomnum;
}

void copy_sudoku(int **source, int **copy, int len) {
    register int i , j;

    for(i = 0; i < len; i++) {
        for(j = 0; j < len; j++) {
            copy[i][j] = source[i][j];
        }
    }
}



void rotate_sudoku(int **mat, int len) 
{
    register int i, j, temp;
    for (i = 0; i < len / 2; i++) {

        // Consider elements in group of 4 in
        // current square
        for (j = i; j < len - i - 1; j++) {

            // store current cell in temp variable
            temp = mat[i][j];

            // move values from right to top
            mat[i][j] = mat[j][len - 1 - i];

            // move values from bottom to right
            mat[j][len - 1 - i] = mat[len - 1 - i][len - 1 - j];

            // move values from left to bottom
            mat[len - 1 - i][len - 1 - j] = mat[len - 1 - j][i];

            // assign temp to left
            mat[len - 1 - j][i] = temp;
        }
    }
}

void swap_rows(int **arr, int len, unsigned int row1, unsigned int row2) {
    int *temp;
    temp = arr[row1];
    arr[row1] = arr[row2];
    arr[row2] = temp;
}

void shuffle_sudoku(int **arr, int len) {
    unsigned int shuffle, size;
    int temp;
    unsigned int row1, row2;
    unsigned int min, max;
    size = (int)sqrt(len);
    shuffle = get_random_num(size * size, size *size *2);
    printf("%d is shuffle\n", shuffle);
    for(int i = 0; i < shuffle; i++) {
        //swap or rotate
        temp = get_random_num(0, 1);
        printf("%d is swap or rotate\n", temp);
        if(temp) {
            // block no.
            temp = get_random_num(0, size - 1);
            printf("%d is block num\n", temp);

            min = temp * size;
            max = (temp + 1) * size - 1;
            // printf("%d is block start\n", min);
            // printf("%d is block end\n", max);

            row1 = get_random_num(min, max);
            row2 = get_random_num(min, max);
            swap_rows(arr, len, row1, row2);
        } else {
            rotate_sudoku(arr, len);
        }
    }
    rotate_sudoku(arr, len);
    swap_rows(arr, len, 0, 1);
}

bool generate_seed(int **arr, int len) {
    base_seed(arr, len);
    shuffle_sudoku(arr, len);
}

void remove_k_elements(int **arr, int len, unsigned int k) {
    
    unsigned int row, col;

    while(k) {
        col = get_random_num(0, len - 1);
        row = get_random_num(0, len - 1);
        arr[row][col] = UNASSIGNED;
        k--;
    }
}

bool sudoku_generator(int **problem_sudoku, int **seed_sudoku, int len) {

    srand(time(0));

    unsigned int k;

    generate_seed(seed_sudoku, len);

    /* copying all elements of seed_sudoku to problem_sudoku
     */
    copy_sudoku(seed_sudoku, problem_sudoku, len);

    k = (len * len / 2) + (len * len / 4);
    // k = 5;
    // printf("removing %u elem\n", k);

    remove_k_elements(problem_sudoku, len, k);

    return true;
}

// int main() {
//     srand(time(0));
//     register int i, j;
//     int **sudoku;
//     int len = 4;
//     unsigned int k;
//     scanf("%d", &len);
//     sudoku = (int **)malloc(len * sizeof(int *));
//     if(sudoku == NULL) {
//         fprintf(stderr, "Memory allocation failed\n");
//         return false;
//     }
//     for (i = 0; i < len ; i++) {
//         sudoku[i] = (int *)malloc(len * sizeof(int));
//         if(sudoku[i] == NULL) {
//             fprintf(stderr, "Memory allocation failed\n");
//             return false;
//         }
//     }


//     generate_seed(sudoku, len);
//     k = (len * len) / 2 + (len * len) / 4;
//     remove_k_elements(sudoku, len , k);
//     print_sudoku(sudoku, len);
//     if(valid_sudoku(sudoku, len)) {
//         printf("valid\n");
//     }
//     return 0;
// }