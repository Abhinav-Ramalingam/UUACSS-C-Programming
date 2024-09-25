#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MATRIX_SIZE 150
#define MAX_GALAXIES 19600 // Adjust this based on the expected number of galaxies

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

long long galval[MAX_GALAXIES][2]; // 2D array to store (i, j) coordinates of '#' positions
long long empty_lines[MATRIX_SIZE]; // Array to store empty rows
long long empty_columns[MATRIX_SIZE]; // Array to store empty columns

long long populate_galval(char matrix[][MATRIX_SIZE], long long row, long long col) {
    long long i, j, count = 0;
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
    printf("Count of galaxies found: %d\n", count);
    return count;
}

long long is_empty_row(char matrix[][MATRIX_SIZE], long long row, long long col) {
    for (long long j = 0; j < col; j++) {
        if (matrix[row][j] == '#') {
            return 0; // False
        }
    }
    return 1; // True
}

long long is_empty_column(char matrix[][MATRIX_SIZE], long long row, long long col_index) {
    for (long long i = 0; i < row; i++) {
        if (matrix[i][col_index] == '#') {
            return 0; // False
        }
    }
    return 1; // True
}

long long compute_sum(long long count, long long empty_lines_count, long long empty_columns_count) {
    long long sum = 0;
    long long i, j;

    for (i = 0; i < count; i++) {
        for (j = i + 1; j < count; j++) {
            // Calculate the base distance between the two galaxies
            long long base_distance = abs(galval[i][0] - galval[j][0]) + abs(galval[i][1] - galval[j][1]);
            sum += base_distance;

            // Check for empty rows between the galaxies
            for (long long l = 0; l < empty_lines_count; l++) {
                if (min(galval[i][0], galval[j][0]) < empty_lines[l] && empty_lines[l] < max(galval[i][0], galval[j][0])) {
                    sum += 999999; // Add distance for empty row
                }
            }

            // Check for empty columns between the galaxies
            for (long long c = 0; c < empty_columns_count; c++) {
                if (min(galval[i][1], galval[j][1]) < empty_columns[c] && empty_columns[c] < max(galval[i][1], galval[j][1])) {
                    sum += 999999; // Add distance for empty column
                }
            }
        }
    }

    printf("Total pairs processed: %d\n", (count * (count - 1)) / 2); // Total pairs
    return sum;
}

long long main() {
    FILE *file;
    char matrix[MATRIX_SIZE][MATRIX_SIZE]; // 150x150 matrix of characters
    char ch;
    long long row = 0, col = 0;

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

    // Preprocessing: Find empty rows
    long long empty_lines_count = 0;
    for (long long i = 0; i < row; i++) {
        if (is_empty_row(matrix, i, col)) {
            empty_lines[empty_lines_count++] = i; // Store empty row index
        }
    }

    // Preprocessing: Find empty columns
    long long empty_columns_count = 0;
    for (long long j = 0; j < col; j++) {
        if (is_empty_column(matrix, row, j)) {
            empty_columns[empty_columns_count++] = j; // Store empty column index
        }
    }

    // Prlong long the matrix and calculate the sum
    printf("%d and %d\n", row, col);
    long long count = populate_galval(matrix, row, col); // Populate galaxies
    long long sum = compute_sum(count, empty_lines_count, empty_columns_count); // Calculate the sum
    printf("Sum is %d\n", sum);

    fclose(file);
    return 0;
}
