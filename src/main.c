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
#include "../headers/menu.h"
#include "../headers/print.h"
#include "../headers/game.h"
#include "../headers/baseseed.h"


#define UNASSIGNED 0

static inline bool quit(char ch) {
    return ch == 'Q';
}

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






/********************************************************/

int main() {

    int **sudoku = NULL;
    char file_name[128];
    unsigned int sudokusize = 9;
    register int i;
    FILE *fp_problem;
    char ch;
    int ch_menu, ch_solver_menu;
    bool quit = false;

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
    /* while quit is false */
    while(!quit) {
        ch_menu = print_menu();
        switch(ch_menu) {
            /* Solve a sudoku */
            case 1:
                while(!quit) {
                    ch_menu = print_solver_menu();
                    switch(ch_menu) {
                        /* get sudoku from file */
                        case 1:
                            sudokusize = get_sudoku_size();
                            if(sudokusize == 0) {
                                quit = true;
                                break;
                            }

                            if(!get_sudoku_from_file(sudoku, sudokusize)) {
                                quit = true;
                                break;
                            }

                            if(!valid_sudoku(sudoku, sudokusize)) {
                                fprintf(stderr, "It is not a valid sudoku\n");
                                quit = true;
                                break;
                            }

                            if(!sudoku_solver(sudoku, sudokusize)) {
                                fprintf(stderr, "No solutions found\n");
                                quit = true;
                                break;
                            }

                            print_sudoku(sudoku, sudokusize);
                            
                            break;

                        /* enter sudoku */
                        case '2':
                            sudokusize = get_sudoku_size();
                            if(sudokusize == 0) {
                                quit = true;
                                break;
                            }

                            if(!get_input_sudoku(sudoku, sudokusize)) {
                                quit = true;
                                break;
                            }

                            print_sudoku(sudoku, sudokusize);

                            if(!valid_sudoku(sudoku, sudokusize)) {
                                fprintf(stderr, "It is not a valid sudoku\n");
                                quit = true;
                                break;
                            }

                            if(!sudoku_solver(sudoku, sudokusize)) {
                                fprintf(stderr, "No solutions found\n");
                                quit = true;
                                break;
                            }

                            print_sudoku(sudoku, sudokusize);
                            
                            break;
                        /* to go back */
                        case '0':
                            quit = true;
                            break;
                        /* NOTA */
                        default:
                            puts("Please choose one of the above");
                            break;
                    }
                    quit = false;
                }
                break;
            /* Generate a sudoku */
            case 2:
                while(!quit) {
                    ch_menu = print_generator_menu();
                    switch(ch_menu) {
                        /* easy */
                        case 1:
                            sudokusize = 4;
                            quit = true;
                            break;
                        case 2:
                            sudokusize = 9;
                            quit = true;
                            break;
                        case 3:
                            sudokusize = 16;
                            quit = true;
                            break;
                        case 4:
                            sudokusize = 25;
                            quit = true;
                            break;
                        case 0:
                            quit = true;
                            break;
                        default:
                            puts("Please choose one of the above or 0 to go back");
                            break;
                    }
                }
                quit = false;
                if(!sudoku_game(sudokusize)) {
                    quit = true;
                    break;
                } else {
                    print_sudoku(sudoku, sudokusize);
                }
                break;
            /* Quit */
            case '3':
                quit = true;
                break;
            /* NOTA */
            default:
                break;
        }
    }

    return EXIT_SUCCESS;
}