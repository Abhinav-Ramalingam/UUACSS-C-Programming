#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_LENGTH 150
#define MAX_NUMBERS 100 // Maximum numbers in a line

long long global_sum = 0; // Global variable to store the total sum

void process_line(char* line) {
    int numbers[MAX_NUMBERS];
    int count = 0;

    // Split the line into an array of numbers
    char* token = strtok(line, " ");
    while (token != NULL && count < MAX_NUMBERS) {
        numbers[count++] = atoi(token); // Convert string to integer
        token = strtok(NULL, " ");
    }

    int base_numbers[MAX_NUMBERS]; // To store the original numbers
    memcpy(base_numbers, numbers, count * sizeof(int)); // Copy to base_numbers
    int base_count = count;
/*
    // Print the Base array
        printf("Base: ");
        for (int i = 0; i < count; i++) {
            printf("%d ", base_numbers[i]);
        }
        printf("\n");
    */
    int extra_values[MAX_NUMBERS] = {0}; // To store last values of differences
    int extra_count = 0; // Count of extra values

    while (1) {
        int differences[MAX_NUMBERS]; // Store differences
        int diff_count = 0;

        // Calculate differences
        for (int i = 1; i < count; i++) {
            differences[diff_count++] = numbers[i] - numbers[i - 1];
        }
/*
        // Print the differences array
        printf("Differences: ");
        for (int i = 0; i < diff_count; i++) {
            printf("%d ", differences[i]);
        }
        printf("\n");
*/
        // Check if all differences are zero
        int all_zero = 1; // Assume all are zero initially
        for (int i = 0; i < diff_count; i++) {
            if (differences[i] != 0) {
                all_zero = 0; // Found a non-zero difference
                break;
            }
        }

        if (all_zero) {
            break; // Exit if all differences are zero
        }

        // Store the last value of differences
        extra_values[extra_count++] = differences[diff_count - 1];

        // Replace numbers with differences for the next iteration
        for (int i = 0; i < diff_count; i++) {
            numbers[i] = differences[i];
        }
        count = diff_count; // Update count to the new number of differences
    }

    // Append a zero as a seed
    extra_values[extra_count++] = 0;
/*
    // Print the Extra array
        printf("Extra: ");
        for (int i = 0; i < extra_count; i++) {
            printf("%d ", extra_values[i]);
        }
        printf("\n");
*/
    // Calculate the extrapolated value
    //("Actual no: %d\n", base_numbers[base_count - 1]);
    int extrapolated_value = base_numbers[base_count - 1]; // Start with the last base number
    for (int i = 0; i < extra_count; i++) {
        extrapolated_value += extra_values[i]; // Add extra values
    }
    global_sum += extrapolated_value; // Add to the global sum

  //  printf("Extrapolated value for the line: %d\n", extrapolated_value);
}


int main() {
    FILE *file;
    char line[MAX_LENGTH];

    // Open the file for reading
    file = fopen("C_1_Lab_Work/inputs/day9_Input.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    // Read the file line by line
    while (fgets(line, sizeof(line), file) != NULL) {
        //printf("%s\n", line);
        process_line(line); // Process each line
    }
    

    // After processing all lines, you can output the global sum
    printf("Total sum from processed lines: %lld\n", global_sum);

    fclose(file);
    return 0;
}
