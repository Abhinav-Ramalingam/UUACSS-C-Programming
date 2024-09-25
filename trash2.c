//Problem 3.2

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MATRIX_SIZE 150

int galval[MATRIX_SIZE];

int populate_galval(char matrix[][MATRIX_SIZE], int row, int col){
    int i, j, count=0;
    for(i=0; i<row; i++){
        for(j=0; j<col; j++){
            if(matrix[i][j] == '#'){
                galval[count]= i+j;
                printf("%d\n", galval[count]);
                count++;
            }
        }
    }
    printf("Count = %d\n", count);
    return count;
}

int compute_sum(int row) {
    int sum = 0;
    int count = 0;
    for (int i = 0; i < row; i++) {
        for (int j = i + 1; j < row; j++) {
            count++;
            int difference = abs(galval[i] - galval[j]);
        
            printf("%d(%d,%d): %d - %d = %d\n", count, i, j, galval[i], galval[j], difference);
            sum += difference;
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

    // Print the matrix and calculate the sum
    print_matrix(matrix, row, col);
    printf("%d and %d\n", row, col);
    int count = populate_galval(matrix, row, col);
    int sum = compute_sum(count);
    //print_matrixd(galval, count, 2);
    printf("Sum is %d\n", sum);

    fclose(file);
    return 0;
}
