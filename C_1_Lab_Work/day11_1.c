#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MATRIX_SIZE 150
#define MAX_GALAXIES 19600 // Adjust this based on the expected number of galaxies

int galval[MAX_GALAXIES][2]; // 2D array to store (i, j) coordinates of '#' positions

int populate_galval(char matrix[][MATRIX_SIZE], int row, int col) {
    int i, j, count = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (matrix[i][j] != '.' && matrix[i][j] != '#') {
                printf("Unexpected character found: %c\n", matrix[i][j]);
            }
            if (matrix[i][j] == '#') {
                galval[count][0] = i; // Store row index
                galval[count][1] = j; // Store column index
                count++;
            }
        }
    }
    //printf("Count of galaxies found: %d\n", count);
    return count;
}

int compute_sum(int count) {
    int sum = 0;
    int pair_count = 0;
    int i,j;

    for (i = 0; i < count; i++) {
        j = i + 1;
        //printf("For j=%d - ", j);
        for (; j < count; j++) {
            pair_count++;
            // Calculate the absolute differences between coordinates
            int abs_diff_i = abs(galval[i][0] - galval[j][0]); // Row difference
            int abs_diff_j = abs(galval[i][1] - galval[j][1]); // Column difference
          
            sum += (abs_diff_i + abs_diff_j);
        }
        //printf("%d,%d taken\n", i, j);
    }

    //printf("Total pairs processed: %d\n", pair_count);
    return sum;
}

void print_matrix(char matrix[][MATRIX_SIZE], int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%c ", matrix[i][j]); // Print each character followed by a space
        }
        printf("\n"); // Newline after each row
    }
}

// Function to check if a row is empty (all dots)
int is_empty_row(char matrix[][MATRIX_SIZE], int row, int col) {
    for (int j = 0; j < col; j++) {
        if (matrix[row][j] == '#') {
            return 0; // False
        }
    }
    return 1; // True
}

// Function to check if a column is empty (all dots)
int is_empty_column(char matrix[][MATRIX_SIZE], int row, int col_index) {
    for (int i = 0; i < row; i++) {
        if (matrix[i][col_index] == '#') {
            return 0; // False
        }
    }
    return 1; // True
}

// Function to insert an empty row at a specific position
void insert_empty_row(char matrix[][MATRIX_SIZE], int *row, int col, int insert_at) {
    for (int i = *row; i > insert_at; i--) {
        for (int j = 0; j < col; j++) {
            matrix[i][j] = matrix[i - 1][j];
        }
    }
    for (int j = 0; j < col; j++) {
        matrix[insert_at][j] = '.'; // Fill new row with dots
    }
    (*row)++; // Increase row count after insertion
}

// Function to insert an empty column at a specific position
void insert_empty_column(char matrix[][MATRIX_SIZE], int row, int *col, int insert_at) {
    for (int i = 0; i < row; i++) {
        for (int j = *col; j > insert_at; j--) {
            matrix[i][j] = matrix[i][j - 1];
        }
        matrix[i][insert_at] = '.'; // Fill new column with dots
    }
    (*col)++; // Increase column count after insertion
}

int main() {
    FILE *file;
    char matrix[MATRIX_SIZE][MATRIX_SIZE]; // 150x150 matrix of characters
    char ch;
    int row = 0, col = 0;

    // Open the file for reading
    file = fopen("C_1_Lab_Work/inputs/day11_Input.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    // Read the file character by character
    while ((ch = fgetc(file)) != EOF && row < MATRIX_SIZE) {
        if (ch == '\n') {
            matrix[row][col] = '\n';
            row++;
            col = 0;
        } else if (col < MATRIX_SIZE) {
            matrix[row][col] = ch; // Store the character in the matrix
            col++;
        }
    }

    // If the file doesn't end with a newline, ensure to terminate the last row
    if (col > 0) {
        matrix[row][col] = '\n'; // Explicit newline marker for the last row if needed
        row++;
    }

    // Preprocessing: Find and insert empty rows
    for (int i = row - 1; i >= 0; i--) {
        if (is_empty_row(matrix, i, col)) {
            insert_empty_row(matrix, &row, col, i);
        }
    }

    // Preprocessing: Find and insert empty columns
    for (int j = col - 1; j >= 0; j--) {
        if (is_empty_column(matrix, row, j)) {
            insert_empty_column(matrix, row, &col, j);
        }
    }

    // Print the matrix and calculate the sum
    //printf("%d and %d\n", row, col);
    int count = populate_galval(matrix, row, col); // Your existing populate_galval function
    int sum = compute_sum(count); // Your existing compute_sum function
    printf("Sum is %d\n", sum);

    fclose(file);
    return 0;
}