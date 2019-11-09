#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define N 32

void fastscan(int *number) 
{ 
    register int c; 
  
    *number = 0; 
  
    // extract current character from buffer 
    c = getchar(); 
    // if (c=='-') 
    // { 
    //     // number is negative 
    //     negative = true; 
  
    //     // extract the next character from the buffer 
    //     c = getchar(); 
    // } 
  
    // Keep on extracting characters if they are integers 
    // i.e ASCII Value lies from '0'(48) to '9' (57) 
    for (; (c>47 && c<58); c=getchar()) 
        *number = *number * 10 + c - 48; 
  
    // if scanned input has a negative sign, negate the 
    // value of the input number 
        // number *= -1; 
}

int print_menu() {
    int choice;
    // puts("What do you want to do?");
    puts("1. Solve a Sudoku");
    puts("2. Generate a Sudoku");
    puts("0. Quit");
    // scanf("%[^\n]%*c", choice);
    // getchar();
    fastscan(&choice);
    printf("%d  me\n", choice);
    return choice;
}

int print_solver_menu() {
    int choice;
    // puts("How do you want to enter the Sudoku");
    puts("1. Get sudoku from a file");
    puts("2. Enter a sudoku");
    puts("0. To go back");
    // scanf("%[^\n]%*c", choice);
    fastscan(&choice);
    return choice;
}

int get_sudoku_size() {
    int size;
    puts("Enter the size of the sudoku");
    // getchar();
    fastscan(&size);
    printf("size is %d", size);
    while(size != 4 && size != 9 && size != 16 && size != 25 && size != 0) {
        puts("Please enter a valid size or enter 0 to go back one stage");
        fastscan(&size);
    // printf("size is %u", size);
    }
    return size;
}

bool get_sudoku_from_file(int **arr, int len) {
    char file_name[128];
    FILE *fp_problem;
	char ch;

    puts("Enter file name");
    scanf("%s", file_name);
    /*opening the file.
     */
    fp_problem = fopen(file_name, "r");

    /* checking if the file is opened
     */
    while(fp_problem == NULL) {
        fprintf(stderr, "cannot open file %s\n", file_name);
        puts("Please enter a valid file or 0 to go back");
        scanf("%s", file_name);
        if(!strcmp(file_name, "0")) {
            return false;
        }
        fp_problem = fopen(file_name, "r");
    }

    /* getting input from a file in the sudoku
     */
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            while(!feof(fp_problem)) {
                ch = fgetc(fp_problem);
                if(isdigit(ch)) {
                    break;
                }
            }
            arr[i][j] = ch - '0';
        }
    }

    fclose(fp_problem);

    return true;
}

bool get_input_sudoku(int **arr, int len) {

    register int i, j;
    // int num;
            // getchar();
    for(i = 0; i < len; i++) {
        for(j = 0; j < len; j++) {
            fastscan(&arr[i][j]);
            // printf("%d skj", arr[i][j]);
        }
    }
    
    return true;
}

int print_generator_menu() {
    int choice;
    puts("Choose difficulty level");
    puts("1. Easy");
    puts("2. Medium");
    puts("3. Hard");
    puts("4. Expert");
    puts("0. Quit");
    // scanf("%[^\n]%*c", choice);
    // getchar();
    fastscan(&choice);
    printf("%d  me\n", choice);
    return choice;
}

void print_game_commands() {
    puts("Commands:");
    puts("");
    puts("    H - help");
    puts("    u - undo");
    puts("    r - redo");
    puts("    h - hint");
    puts("    c - clear");
    puts("    s - solve");
    puts("    n - start new");
    puts("    i - insert");
    puts("    Q - quit");
    puts("");
    puts("");
    // puts("");
    // puts("");
}