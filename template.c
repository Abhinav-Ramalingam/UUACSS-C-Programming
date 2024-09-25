//Problem x.y

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MATRIX_SIZE 150

void print_matrix(char matrix[][MATRIX_SIZE] , int row, int col) {
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%c ", matrix[i][j]);  // Print each character followed by a space
        }
        printf("\n");  // Newline after each row
    }
}

int main(){
    
    return 0;
}