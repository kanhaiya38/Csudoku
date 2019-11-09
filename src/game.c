#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../headers/sudokugenerator.h"
#include "../headers/game.h"
#include "../headers/print.h"
#include "../headers/menu.h"
#include "../headers/sudokusolver.h"

#define UNASSIGNED 0

typedef struct data {
    unsigned int row;
    unsigned int col;
    unsigned int num;
} data;

data get_data(char *cmd) {
    data token;

    // char token;
    token.row = cmd[0] - 'a';
    token.col = cmd[1] - 'a';
    token.num = cmd[2] - '0';

    return token;
}

unsigned int get_command_num(char *cmd) {
    if(!strcmp(cmd, "help"))
        return 1;
    if(!strcmp(cmd, "undo"))
        return 2;
    if(!strcmp(cmd, "redo"))
        return 3;
    if(!strcmp(cmd, "hint"))
        return 4;
    if(!strcmp(cmd, "clear"))
        return 5;
    if(!strcmp(cmd, "solve"))
        return 6;
    if(!strcmp(cmd, "new"))
        return 7;
    // if(!strcmp(cmd, ""))
    //     return 7;
    if(!strcmp(cmd, "quit"))
        return 0;
    return 9;
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

bool sudoku_game(int len) {
    register int i;
    int **problem_sudoku, **seed_sudoku, **sudoku;
    char choice;
    char command[32];
    int row, col, num;
    unsigned int cmd;
    data data;
    // print_sudoku_game_help();

    /* first allocating memory to store address of integer pointer
     * then allocating each integer pointer memory to store integer
     */
    problem_sudoku = (int **)malloc(len * sizeof(int *));
    if(problem_sudoku == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return false;
    }
    for (i = 0; i < len ; i++) {
        problem_sudoku[i] = (int *)malloc(len * sizeof(int));
        if(problem_sudoku[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return false;
        }
    }

    seed_sudoku = (int **)malloc(len * sizeof(int *));
    if(seed_sudoku == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return false;
    }
    for (i = 0; i < len ; i++) {
        seed_sudoku[i] = (int *)malloc(len * sizeof(int));
        if(seed_sudoku[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return false;
        }
    }

    sudoku = (int **)malloc(len * sizeof(int *));
    if(sudoku == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return false;
    }
    for (i = 0; i < len ; i++) {
        sudoku[i] = (int *)malloc(len * sizeof(int));
        if(sudoku[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return false;
        }
    }


    puts("Do you want to start?[y/n]");
    scanf("%c", &choice);
    if(choice == 'n') {
        return false;
    }
    sudoku_generator(problem_sudoku, seed_sudoku, len);
    copy_sudoku(problem_sudoku, sudoku, len);
    /* to clear terminal */
    printf("\e[1;1H\e[2J"); 
    print_game_commands();
    print_sudoku(sudoku, len);

    scanf("%s", command);
    cmd = get_command_num(command);

    while(cmd) {

        // scanf("%d", &row);
        // scanf("%d", &col);
        // scanf("%d", &num);
        scanf("%s", command);
        cmd = get_command_num(command);
        switch(cmd) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                data = get_data(command);
                if(problem_sudoku[data.row][data.col] != UNASSIGNED) {
                    puts("You cannot change element at this position");
                } else {
                    sudoku[data.row][data.col] = data.num;
                }
                printf("\e[1;1H\e[2J");
                print_game_commands(); 
                print_sudoku(sudoku, len);
                if(comparesudoku(sudoku, seed_sudoku, len)) {
                    puts("completed succesfully");
                    printf("\e[1;1H\e[2J");
                    return false;
                }
                break;
            case 0:
                break;
        }
        // if(cmd == 9) {
            
        // }
    }

    return false;
}