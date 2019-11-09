#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
// #include <regex.h>
#include <ctype.h>
#include "../headers/sudokugenerator.h"
#include "../headers/game.h"
#include "../headers/print.h"
#include "../headers/menu.h"
#include "../headers/sudokusolver.h"
#include "../headers/stack.h"

#define UNASSIGNED 0

// typedef struct data {
//     unsigned int row;
//     unsigned int col;
//     unsigned int num;
// } data;

bool get_data(char *cmd, int strlen, values *token, int len) {
    // values token;

    // char token;
    register int i;
    bool row = true;
    bool col = false;
    bool num = false;
    int sum = 0;
    for(i = 0; i < strlen; i++) {
        if(isspace(cmd[i])) {
            continue;
        }
        if(isalpha(cmd[i])) {
            if(row) {
                token->row = cmd[i] - 'a';
                row = false;
                col = true;
                continue;
            } else if(col) {
                token->col = cmd[i] - 'a';
                col = false;
                num = true;
                continue;
            } else {
                return false;
            }
        }

        if(isdigit(cmd[i])) {
            if(num) {
                while(isdigit(cmd[i])) {
                    sum += num;
                }

                if(sum > len) {
                    return false;
                }
                token->num = sum;
            }
        }

    }
    token->row = cmd[0] - 'a';
    token->col = cmd[1] - 'a';
    token->num = cmd[2] - '0';
    return false;

    // return token;
}

unsigned int get_command_num(char *cmd) {
    // regex_t regex;
    // int check;
    
    // check = regcomp()

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
    values data;
    bool quit = false;
    stack undo, redo;
    init(&undo);
    init(&redo);
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

    // scanf("%s", command);
    // cmd = get_command_num(command);

    while(!quit) {

        // scanf("%d", &row);
        // scanf("%d", &col);
        // scanf("%d", &num);
        scanf("%s", command);
        cmd = get_command_num(command);
        

        switch(cmd) {
            case 1:
                break;
            case 2:
                if(!isempty(&undo)) {
                    data = pop(&undo);
                    if(!isfull(&redo)) {
                        push(&redo, data);
                    } else {
                        fprintf(stderr, "stack is full\n");
                    }
                    sudoku[data.row][data.col] = UNASSIGNED;
                    printf("\e[1;1H\e[2J");
                    print_game_commands();
                    print_sudoku(sudoku, len);
                } else {
                    fprintf(stderr, "Cannot undo\n");
                }
                break;
            case 3:
                if(!isempty(&redo)) {
                    data = pop(&redo);
                    if(!isfull(&undo)) {
                        push(&undo, data);
                    } else {
                        fprintf(stderr, "stack is full\n");
                    }
                    sudoku[data.row][data.col] = data.num;
                    printf("\e[1;1H\e[2J");
                    print_game_commands();
                    print_sudoku(sudoku, len);
                } else {
                    fprintf(stderr, "Cannot redo\n");
                }
                break;
            case 4:
                find_empty_cell(sudoku, len, &row, &col);
                printf("%d at position %d, %d\n", seed_sudoku[row][col], row, col);
                // sudoku[row][col] = seed_sudoku[row][col];
                break;
            case 5:
                sudoku = problem_sudoku;
                printf("\e[1;1H\e[2J");
                print_game_commands();
                print_sudoku(sudoku, len);
                break;
            case 6:
                sudoku = seed_sudoku;
                printf("\e[1;1H\e[2J");
                print_game_commands();
                print_sudoku(sudoku, len);
                puts("Sudoku solved");
                break;
            case 7:
                sudoku_generator(problem_sudoku, seed_sudoku, len);
                copy_sudoku(problem_sudoku, sudoku, len);
                printf("\e[1;1H\e[2J"); 
                print_game_commands();
                print_sudoku(sudoku, len);
                break;
            case 8:
                break;
            case 9:
                printf("\e[1;1H\e[2J");
                if(get_data(command, strlen(command), &data, len)) {
                    // continue;
                } else {
                    print_game_commands();
                    print_sudoku(sudoku, len);
                    puts("Not a command");
                    continue;
                }
                print_game_commands();
                if(problem_sudoku[data.row][data.col] != UNASSIGNED) {
                    puts("You cannot change element at this position");
                    puts("");
                    puts("");
                } else {
                    sudoku[data.row][data.col] = data.num;
                    if(!isfull(&undo)) {
                        push(&undo, data);
                    } else {
                        fprintf(stderr, "Stack is full");
                    }
                }
                print_sudoku(sudoku, len);
                if(comparesudoku(sudoku, seed_sudoku, len)) {
                    puts("completed succesfully");
                    printf("\e[1;1H\e[2J");
                    return false;
                }
                break;
            case 0:
                quit = true;
                break;
        }
    }
    free(sudoku);
    free(problem_sudoku);
    free(seed_sudoku);
    return false;
}