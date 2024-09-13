#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

#define MATRIX_SIZE 140

int isspec(char c){
    return !isalnum(c) && c!='.';
}

int pon(char matrix[][MATRIX_SIZE], int row, int col) {
    int i = 0, j = 0;
    char* endptr;
    long long sum = 0;
    int ntas = 0;
    char buf[MATRIX_SIZE] = "\0";
    int count = 0;

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (isdigit(matrix[i][j])) {
                // Check surrounding characters, ensuring we don't go out of bounds
                if ((i > 0 && isspec(matrix[i - 1][j])) ||  // Above
                (i < row - 1 && isspec(matrix[i + 1][j])) ||  // Below
                (j > 0 && isspec(matrix[i][j - 1])) ||  // Left
                (j < col - 1 && isspec(matrix[i][j + 1])) ||  // Right
                (i > 0 && j > 0 && isspec(matrix[i - 1][j - 1])) ||  // Top-left diagonal
                (i > 0 && j < col - 1 && isspec(matrix[i - 1][j + 1])) ||  // Top-right diagonal
                (i < row - 1 && j > 0 && isspec(matrix[i + 1][j - 1])) ||  // Bottom-left diagonal
                (i < row - 1 && j < col - 1 && isspec(matrix[i + 1][j + 1])))  // Bottom-right diagonal 
                {  
                    ntas = 1;
                }

                buf[count++] = matrix[i][j];
                buf[count] = '\0';
                
            } 
            else {
                // If there's something in the buffer, process it
                if (buf[0] != '\0') {
                    printf("%s is a %d\n",buf, ntas);
                    if (ntas == 1) {
                        sum += strtoll(buf,&endptr,10);  // Convert to integer and add to sum
                        ntas = 0;  // Reset special character flag
                    }
                    
                    count = 0;
                    buf[0] = '\0';  // Reset buffer
                    
                }
            }

        }
    }

    return sum;
}

void print_matrix(char matrix[][MATRIX_SIZE] , int row, int col) {
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%c ", matrix[i][j]);  // Print each character followed by a space
        }
        printf("\n");  // Newline after each row
    }
}

int main() {
    FILE *file;
    char matrix[MATRIX_SIZE][MATRIX_SIZE]; // 140x140 matrix of characters
    char ch;
    int row = 0, col = 0;

    // Open the file for reading
    file = fopen("C_1_Lab_Work/inputs/day3_Input.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    // Read the file character by character
    while ((ch = fgetc(file)) != EOF && row < MATRIX_SIZE) {
        if (ch == '\n') {
            row++;      // Move to the next row when a newline is encountered
            col = 0;    // Reset column to 0
        } else if (col < MATRIX_SIZE) {
            matrix[row][col] = ch;  // Store the character in the matrix
            col++;
        }
    }
    row++;
    //print_matrix(matrix,row,col);
    printf("Sum is %d\n",pon(matrix,row,col));
    fclose(file);

    

    return 0;
}
