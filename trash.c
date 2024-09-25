//Problem_3.2

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

#define MATRIX_SIZE 200

int isspec(char c){
    return !isalnum(c) && c != '.' && c != '\n';
}

// Function to extract the complete number when given a starting position
long long extract_number(char matrix[][MATRIX_SIZE], int row, int col, int max_rows, int max_cols) {
    char buf[MATRIX_SIZE] = "\0";
    int count = 0;
    
    // Go left to find the start of the number
    while (col >= 0 && isdigit(matrix[row][col])) {
        col--;
    }
    col++;  // Move one step right since we overshoot by one.

    // Now extract the full number
    while (col < max_cols && isdigit(matrix[row][col])) {
        buf[count++] = matrix[row][col];
        col++;
    }
    buf[count] = '\0';  // Null-terminate the string

    return strtoll(buf, NULL, 10);
}

long long pon(char matrix[][MATRIX_SIZE], int row, int col) {
    int i = 0, j = 0;
    long long sum = 0;

    // Directions to check for adjacent numbers
    int adjs[6][2] = {
        {-1, 0},  // top
        {-1, -1}, // top-left
        {-1, 1},  // top-right
        {1, 0},   // bottom
        {1, -1},  // bottom-left
        {1, 1}    // bottom-right
    };

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (matrix[i][j] == '*') {  // Found a gear ('*')
                long long number1 = 0, number2 = 0;

                // Check above the '*' for a number
                for (int k = 0; k < 3; k++) {  // First 3 directions (top, top-left, top-right)
                    int ni = i + adjs[k][0];
                    int nj = j + adjs[k][1];
                    printf("ni = %d and nj = %d\n", ni, nj);
                    if (ni >= 0 && ni < row && nj >= 0 && nj < col && isdigit(matrix[ni][nj])) {
                        number1 = extract_number(matrix, ni, nj, row, col);
                        printf("n1 = %lld\n", number1);
                        break;  // Stop after finding the first number
                    }
                }

                // Check below the '*' for a number
                for (int k = 3; k < 6; k++) {  // Last 3 directions (bottom, bottom-left, bottom-right)
                    int ni = i + adjs[k][0];
                    int nj = j + adjs[k][1];

                    if (ni >= 0 && ni < row && nj >= 0 && nj < col && isdigit(matrix[ni][nj])) {
                        number2 = extract_number(matrix, ni, nj, row, col);
                        printf("n2 = %lld\n", number2);
                        break;  // Stop after finding the second number
                    }
                }

                // If both numbers are found, multiply and add to sum
                if (number1 != 0 && number2 != 0) {
                    sum += (number1 * number2);
                }
            }
        }
    }

    return sum;
}

void print_matrix(char matrix[][MATRIX_SIZE], int row, int col) {
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
            // Insert explicit newline marker in the matrix
            matrix[row][col] = '\n';  
            row++;      // Move to the next row when a newline is encountered
            col = 0;    // Reset column to 0
        } else if (col < MATRIX_SIZE) {
            matrix[row][col] = ch;  // Store the character in the matrix
            col++;
        }
    }

    // If the file doesn't end with a newline, ensure to terminate the last row
    if (col > 0) {
        matrix[row][col] = '\n';  // Explicit newline marker for the last row if needed
        row++;
    }

    col++;
    printf("Sum is %lld\n", pon(matrix, row, col));

    fclose(file);
    return 0;
}
