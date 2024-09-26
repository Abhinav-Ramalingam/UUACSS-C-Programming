# Run this single file to get all the outputs

# Create output directory if it doesn't exist
mkdir -p C_1_Output/outputs/

# Compile and run Day 1, Part 1
gcc -w -o C_1_Output/day1_1 C_1_Lab_Work/day1_1.c
./C_1_Output/day1_1 > C_1_Output/outputs/output1_1.txt

# Compile and run Day 1, Part 2
gcc -w -o C_1_Output/day1_2 C_1_Lab_Work/day1_2.c
./C_1_Output/day1_2 > C_1_Output/outputs/output1_2.txt

# Compile and run Day 3, Part 1
gcc -w -o C_1_Output/day3_1 C_1_Lab_Work/day3_1.c
./C_1_Output/day3_1 > C_1_Output/outputs/output3_1.txt

# Compile and run Day 9, Part 1
gcc -w -o C_1_Output/day9_1 C_1_Lab_Work/day9_1.c
./C_1_Output/day9_1 > C_1_Output/outputs/output9_1.txt

# Compile and run Day 9, Part 2
gcc -w -o C_1_Output/day9_2 C_1_Lab_Work/day9_2.c
./C_1_Output/day9_2 > C_1_Output/outputs/output9_2.txt

# Compile and run Day 11, Part 1
gcc -w -o C_1_Output/day11_1 C_1_Lab_Work/day11_1.c
./C_1_Output/day11_1 > C_1_Output/outputs/output11_1.txt
