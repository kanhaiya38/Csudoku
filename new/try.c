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


//////////////////////////////////////////////////////////////////////////



#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../headers/stack.h"
#include "../headers/check.h"
#include "../headers/sudokusolver.h"
#include "../headers/print.h"

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

    randomnum = rand() % (max + min + 1) + min;

    return randomnum;
}

void copy_sudoku(int **seed_sudoku, int **problem_sudoku, int len) {
    register int i , j;

    for(i = 0; i < len; i++) {
        for(j = 0; j < len; j++) {
            problem_sudoku[i][j] = seed_sudoku[i][j];
        }
    }
}

void abc() {
    int sudoku25[25][25] = {
	15, 9, 11, 4, 22, 6, 19, 18, 7, 3, 23, 10, 16, 5, 17, 8, 20, 2, 13, 24, 25, 1, 21, 14, 12,
	12, 25, 1, 21, 14, 15, 9, 11, 4, 22, 6, 19, 18, 7, 3, 23, 10, 16, 5, 17, 8, 20, 2, 13, 24,
	24, 8, 20, 2, 13, 12, 25, 1, 21, 14, 15, 9, 11, 4, 22, 6, 19, 18, 7, 3, 23, 10, 16, 5, 17,
	17, 23, 10, 16, 5, 24, 8, 20, 2, 13, 12, 25, 1, 21, 14, 15, 9, 11, 4, 22, 6, 19, 18, 7, 3,
	3, 6, 19, 18, 7, 17, 23, 10, 16, 5, 24, 8, 20, 2, 13, 12, 25, 1, 21, 14, 15, 9, 11, 4, 22,
	22, 15, 9, 11, 4, 3, 6, 19, 18, 7, 17, 23, 10, 16, 5, 24, 8, 20, 2, 13, 12, 25, 1, 21, 14,
	14, 12, 25, 1, 21, 22, 15, 9, 11, 4, 3, 6, 19, 18, 7, 17, 23, 10, 16, 5, 24, 8, 20, 2, 13,
	13, 24, 8, 20, 2, 14, 12, 25, 1, 21, 22, 15, 9, 11, 4, 3, 6, 19, 18, 7, 17, 23, 10, 16, 5,
	5, 17, 23, 10, 16, 13, 24, 8, 20, 2, 14, 12, 25, 1, 21, 22, 15, 9, 11, 4, 3, 6, 19, 18, 7,
	7, 3, 6, 19, 18, 5, 17, 23, 10, 16, 13, 24, 8, 20, 2, 14, 12, 25, 1, 21, 22, 15, 9, 11, 4,
	4, 22, 15, 9, 11, 7, 3, 6, 19, 18, 5, 17, 23, 10, 16, 13, 24, 8, 20, 2, 14, 12, 25, 1, 21,
	21, 14, 12, 25, 1, 4, 22, 15, 9, 11, 7, 3, 6, 19, 18, 5, 17, 23, 10, 16, 13, 24, 8, 20, 2,
	2, 13, 24, 8, 20, 21, 12, 12, 25, 1, 4, 22, 15, 9, 11, 7, 3, 6, 19, 18, 5, 17, 23, 10, 16,
	16, 5, 17, 23, 10, 2, 13, 24, 8, 20, 21, 14, 12, 25, 1, 4, 22, 15, 9, 11, 7, 3, 6, 19, 18,
	18, 7, 3, 6, 19, 16, 5, 17, 23, 10, 2, 13, 24, 8, 20, 21, 14, 12, 25, 1, 4, 22, 15, 9, 11,
	11, 4, 22, 15, 9, 18, 7, 3, 6, 19, 16, 5, 17, 23, 10, 2, 13, 24, 8, 29, 21, 14, 12, 25, 1,
	1, 21, 14, 12, 25, 11, 4, 22, 15, 9, 18, 7, 3, 6, 19, 16, 5, 17, 23, 10, 2, 13, 24, 8, 20,
	20, 2, 13, 24, 8, 1, 21, 14, 12, 25, 11, 4, 22, 15, 9, 18, 7, 3, 6, 19, 16, 5, 17, 23, 10,
	10, 16, 5, 17, 23, 20, 2, 13, 24, 8, 1, 21, 14, 12, 25, 11, 4, 22, 15, 9, 18, 7, 3, 6, 19,
	19, 18, 7, 3, 6, 10, 16, 5, 17, 23, 20, 2, 13, 24, 8, 1, 21, 14, 12, 25, 11, 4, 22, 15, 9,
	9, 11, 4, 22, 15, 19, 18, 7, 3, 6, 10, 16, 5, 17, 23, 20, 2, 13, 24, 8, 1, 21, 14, 12, 25,
	25, 1, 21, 14, 12, 9, 11, 4, 22, 15, 19, 18, 7, 3, 6, 10, 16, 5, 17, 23, 20, 2, 13, 24, 8,
	8, 20, 2, 13, 24, 25, 1, 21, 14, 12, 9, 11, 4, 22, 15, 19, 18, 7, 3, 6, 10, 16, 5, 17, 23,
	23, 10, 16, 5, 17, 8, 20, 2, 13, 24, 25, 1, 21, 14, 12, 9, 11, 4, 22, 15, 19, 18, 7, 3, 6,
	6, 19, 18, 7, 3, 23, 10, 16, 5, 17, 8, 20, 2, 13, 24, 25, 1, 21, 14, 12, 9, 11, 4, 22, 15 
};
}


bool generate_seed(int **arr, int len) {

    register int i, j;
    /* Initializes the 2d array.
     */
    for(i = 0; i < len; i++) {
        for(j = 0; j < len; j++) {
            arr[i][j] = UNASSIGNED;
        }
    }
    
    if(len > 4){
        fill_diagonal(arr, len);
    } else {
        fill_some_cells(arr, len);
    }

    // print_sudoku(arr, len);

    // if(len < 25)

    if(valid_sudoku(arr, len)) {
        printf("sudoku is valid\n");
        if(sudoku_solver(arr, len)) {
            printf("sudoku solved\n");
        } else {
            printf("cannot solve sudoku\n");
        }
    } else {
        printf("sudoku is not valid\n");
    }
    
    return true;
    
}

void remove_k_elements(int **arr, int len, unsigned int k) {
    
    unsigned int row, col;

    while(k) {
        row = rand() % (len - 1) + 1;
        col = rand() % (len - 1) + 1;
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
    k = 5;
    // printf("removing %u elem\n", k);

    remove_k_elements(problem_sudoku, len, k);

    return true;
}