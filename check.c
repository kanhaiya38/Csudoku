#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "check.h"

#define UNASSIGNED 0

/* checkemptycell checks if the passed location is empty.
 * if it is empty it returns true.
 * else it returns false.
 */

bool checkemptycell(int **arr, int len, int row, int col) {

    if(arr[row][col] == UNASSIGNED) {
        return true;
    }

    return false;
}

/* checkrow checks if number num is in row'th row.
 * if it is in row'th row then it returns true.
 * else it returns false.
 */

bool checkrow(int **arr, int len, int row, int num) {

    for(int i = 0; i < len; i++) {
        if(arr[row][i] == num) {
            return true;
        }
    }
    return false;

}

/* checkcol checks if number num is in col'th column.
 * if it is in col'th column then it returns true.
 * else it returns false.
 */

bool checkcol(int **arr, int len, int col, int num) {

    for(int i = 0; i < len; i++) {
        if(arr[i][col] == num) {
            return true;
        }
    }
    return false;

}

/* checkblock checks if number num is in the block.
 * if it is in the block then it returns true.
 * else it returns false.
 */

bool checkblock(int **arr, int len, int row, int col, int num) {
    
    int left, right, top, bottom;
    int size = (int)sqrt(len);

    /* to find the boundaries of the block.
    */

    left = (col / size) * size;
    right = left + size;
    top = (row / size) * size;
    bottom = top + size;
    
    /* to find if the num is in the block.
    */

    for(int i = top; i < bottom; i++) {
        for(int j = left; j < right; j++) {
            if(arr[i][j] == num) {
                return true;
            }
        }
    }

    return false;
}