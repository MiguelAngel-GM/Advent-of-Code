#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

int parseLine(const char *buffer, size_t line_length, const int part) {
    char all_digits[line_length];
    char first_last[2];
    int digit_count = 0;
    
    for(size_t i = 0; i < line_length; i++) {
        if(isdigit(buffer[i])) {
            all_digits[digit_count] = buffer[i];
            digit_count++;
        }
    }

    first_last[0] = all_digits[0];
    first_last[1] = all_digits[digit_count-1];

    return atoi(first_last);
}

int sumCalibrationValues(const char *filename, const int part) {
    FILE *input = fopen(filename, "r");
    if(input == NULL) {
        fprintf(stderr, "Could not open file %s", filename);
        exit(-1);
    }

    int sum = 0;
    size_t buffer_size = 256, line_length = 0;
    char *buffer = (char*)malloc(sizeof(char) * buffer_size);

    while((line_length = getline(&buffer, &buffer_size, input)) != EOF) {
        int value = parseLine(buffer, line_length, part);
        sum += value;
    }

    free(buffer);
    fclose(input);

    return sum;
}

int main() {
    printf("Part 1 solution: %d\n", sumCalibrationValues("input.txt", 1));

    return 0;
}