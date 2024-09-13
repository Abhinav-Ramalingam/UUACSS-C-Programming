#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int fald(char* str){
    int i, num_arr[2] = {99, 99};
    for (i = 0; i < strlen(str); i++){
        if (isdigit(str[i])){
            if (num_arr[0] == 99){
                num_arr[0] = (int)(str[i]) - 48;
            }
            else {
                num_arr[1] = (int)(str[i]) - 48;
            }
        }
    }
    if (num_arr[1] == 99) num_arr[1] = num_arr[0];
    int result = 10*num_arr[0] + num_arr[1];
    printf("%d\n", result);
    return result;
}

int main() {
    FILE *file;
    char str[100]; // Buffer to hold each string from the file
    int sum = 0;   // Variable to store the total sum

    // Open the file for reading
    file = fopen("C_1_Lab_Work/inputs/day1_Input.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    // Read each line from the file
    while (fgets(str, sizeof(str), file) != NULL) {
        // Remove trailing newline character if present
        str[strcspn(str, "\n")] = 0;

        // Add the result of fald() to the sum
        sum += fald(str);
    }

    // Close the file after reading
    fclose(file);

    // Print the total sum
    printf("Total sum of integers: %d\n", sum);

    return 0;
}
