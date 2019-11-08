// #include <stdio.h>
// #include <string.h>
// #include <stdbool.h>
// #include <ctype.h>


// bool get_sudoku_from_file(int **arr, int len, char *file_name) {
//     FILE *fp_problem;
// 	char ch;
//     // char file[128];

//     // strcat(file, file_name);

//     /*opening the file.
//      */
//     fp_problem = fopen(file_name, "r");

//     /* checking if the file is opened
//      */
//     if(fp_problem == NULL) {
//         fprintf(stderr, "cannot open file %s\n", file_name);
//         return false;
//     }

//     /* getting input from a file in the sudoku
//      */
//     for(int i = 0; i < len; i++) {
//         for(int j = 0; j < len; j++) {
//             while(!feof(fp_problem)) {
//                 ch = fgetc(fp_problem);
//                 if(isdigit(ch)) {
//                     break;
//                 }
//             }
//             arr[i][j] = ch - '0';
//         }
//     }

//     fclose(fp_problem);

//     return true;
// }