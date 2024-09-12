#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int s2d(const char* str) {
    if (strstr(str, "one") != NULL) return 1;
    else if (strstr(str, "two") != NULL) return 2;
    else if (strstr(str, "three") != NULL) return 3;
    else if (strstr(str, "four") != NULL) return 4;
    else if (strstr(str, "five") != NULL) return 5;
    else if (strstr(str, "six") != NULL) return 6;
    else if (strstr(str, "seven") != NULL) return 7;
    else if (strstr(str, "eight") != NULL) return 8;
    else if (strstr(str, "nine") != NULL) return 9;
    else return -1; // Return -1 if no valid digit is found
}

int fald(char* str){
    int i, num_arr[2] = {99, 99};
    char buf[240]; 
    int count = 0, number = 99;
    for (i = 0; i < strlen(str); i++){
        if (isdigit(str[i])){
            number = (int)(str[i]) - 48;     
        }
        else {
            buf[count++] = str[i];
            buf[count] = '\0';
            //printf("%s... ",buf);
            int cmp = s2d(buf);
            
            if(cmp != - 1){
                number = cmp;
                //printf("-number %d\n",number);
                buf[0] = '\0';
                count = 0;
            }
        }
        if (num_arr[0] == 99) num_arr[0] = number; 
        else num_arr[1] = number;
    }

    if (num_arr[1] == 99) num_arr[1] = num_arr[0];
    int result = 10*num_arr[0] + num_arr[1];
    return result;
}

int main() {
    FILE *file;
    char str[240]; // Buffer to hold each string from the file
    int sum = 0;   // Variable to store the total sum

    // Open the file for reading
    file = fopen("C_1_Lab_Work/inputs/day1_Input.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }
    int count = 0;
    // Read each line from the file
    while (fgets(str, sizeof(str), file) != NULL) {
        // Remove trailing newline character if present
        str[strcspn(str, "\n")] = 0;

        // Add the result of fald() to the sum
        sum += fald(str);
        printf("result done in %d\n", (++count));
    }

    // Close the file after reading
    fclose(file);

    // Print the total sum
    printf("Total sum of integers: %d\n", sum);

    return 0;
}
