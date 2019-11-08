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

// int main(int argc, char* argv[]) {

//     int **sudoku = NULL;
//     char file_name[128];
//     unsigned int sudokusize = 25;
//     register int i;
//     FILE *fp_problem;
//     char ch;

//     // scanf("%u", &sudokusize);
    
//     strcpy(file_name, "2x2.txt");
//     printf("%s is file name\n", file_name);
//     if(argc > 2) {
//         errno = EINVAL;
//         perror("usage");
//         return errno;
//     }

//     // if(!init_sudoku(sudoku, sudokusize)) {
//     //     fprintf(stderr, "Not enough memory\n");
//     //     return EXIT_FAILURE;
//     // }
    
//     /* first allocating memory to store address of integer pointer
//      * then allocating each integer pointer memory to store integer
//      */
//     sudoku = (int **)malloc(sudokusize * sizeof(int *));
//     if(sudoku == NULL) {
//         fprintf(stderr, "Memory allocation failed\n");
//         return false;
//     }
//     for (i = 0; i < sudokusize ; i++) {
//         sudoku[i] = (int *)malloc(sudokusize * sizeof(int));
//         if(sudoku[i] == NULL) {
//             fprintf(stderr, "Memory allocation failed\n");
//             return false;
//         }
//     }

//     // if(argc == 2) {
        
//     //     if(get_sudoku_from_file(sudoku, sudokusize, file_name)) {
//     //         printf("File successfully opened\n");
//     //     } else {
//     //         printf("cannot open file\n");
//     //         return EXIT_FAILURE;
//     //     }
//     // }

//     //     /*opening the file.
//     //  */
//     // fp_problem = fopen(argv[1], "r");

//     // /* checking if the file is opened
//     //  */
//     // if(fp_problem == NULL) {
//     //     fprintf(stderr, "cannot open file %s\n", argv[1]);
//     //     return false;
//     // }

//     // /* getting input from a file in the sudoku
//     //  */
//     // for(int i = 0; i < sudokusize; i++) {
//     //     for(int j = 0; j < sudokusize; j++) {
//     //         while(!feof(fp_problem)) {
//     //             ch = fgetc(fp_problem);
//     //             if(isdigit(ch)) {
//     //                 break;
//     //             }
//     //         }
//     //         sudoku[i][j] = ch - '0';
//     //     }
//     // }

//     // fclose(fp_problem);


//     // for(i = 0; i < sudokusize; i++) {
//     //     for(int j = 0; j < sudokusize; j++) {
//     //         sudoku[i][j] = UNASSIGNED;
//     //     }
//     // }

//     // print_sudoku(sudoku, sudokusize);
//     // int **temp = sudoku;
//     // for(i = 0; i < 1; i++) {
//     // if(!valid_sudoku(sudoku, sudokusize)) {
// 	// 	printf("not a valid sudoku\n");
//     //     return EXIT_FAILURE;
// 	// }

//     // if(sudoku_solver(sudoku, sudokusize)) {

//     //     print_sudoku(sudoku, sudokusize);

//     // } else {

//     //     fprintf(stderr, "Cannot solve input sudoku\n");
//     //     return EXIT_FAILURE;

//     // }
//     // sudoku = temp;
//     // }

//     // printf("Complete\n");

//     if(generate_sudoku(sudoku, sudokusize)) {
//         print_sudoku(sudoku, sudokusize);
//     } else {
//         printf("false\n");
//     }

//     // print_sudoku(sudoku, sudokusize);
//     if(valid_sudoku(sudoku, sudokusize))
//         printf("gr8 amn\n");
//     free(sudoku);
//     return EXIT_SUCCESS;
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
                // while(!quit) {
                //     ch_menu = print_generator_menu();
                //     switch(ch_menu) {
                //         /* get sudoku from file */
                //         case 1:
                //             sudokusize = 4;
                //             // if(sudokusize == 0) {
                //             //     quit = true;
                //             //     break;
                //             // }

                //             if(!generate_sudoku(sudoku, sudokusize)) {
                //                 quit = true;
                //                 break;
                //             }

                //             // if(!valid_sudoku(sudoku, sudokusize)) {
                //             //     fprintf(stderr, "It is not a valid sudoku\n");
                //             //     quit = true;
                //             //     break;
                //             // }

                //             // if(!sudoku_solver(sudoku, sudokusize)) {
                //             //     fprintf(stderr, "No solutions found\n");
                //             //     quit = true;
                //             //     break;
                //             // }

                //             // print_sudoku(sudoku, sudokusize);
                            
                //             break;

                //         /* enter sudoku */
                //         case '2':
                //             sudokusize = get_sudoku_size();
                //             if(sudokusize == 0) {
                //                 quit = true;
                //                 break;
                //             }

                //             if(!get_input_sudoku(sudoku, sudokusize)) {
                //                 quit = true;
                //                 break;
                //             }

                //             print_sudoku(sudoku, sudokusize);

                //             if(!valid_sudoku(sudoku, sudokusize)) {
                //                 fprintf(stderr, "It is not a valid sudoku\n");
                //                 quit = true;
                //                 break;
                //             }

                //             if(!sudoku_solver(sudoku, sudokusize)) {
                //                 fprintf(stderr, "No solutions found\n");
                //                 quit = true;
                //                 break;
                //             }

                //             print_sudoku(sudoku, sudokusize);
                            
                //             break;
                //         /* to go back */
                //         case '0':
                //             quit = true;
                //             break;
                //         /* NOTA */
                //         default:
                //             puts("Please choose one of the above");
                //             break;
                //     }
                //     quit = false;
                // }
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