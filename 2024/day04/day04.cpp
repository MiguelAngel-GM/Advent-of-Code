#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <cstring>

#define WSSIZE 140

void readInput(const char *filename, char wordSearch[WSSIZE][WSSIZE]) {
    std::ifstream inputStream(filename);
    std::string line;
    int i = 0;

    while (std::getline(inputStream, line)) {
        memcpy(wordSearch[i], line.c_str(), WSSIZE);
        i++;
    }

    inputStream.close();
}

char charAt(char wordSearch[WSSIZE][WSSIZE], int row, int col) {
    if (row >= WSSIZE || row < 0 || col >= WSSIZE || col < 0)
        return '\0';
    return wordSearch[row][col];
}

int evaluateCoincidences(char wordSearch[WSSIZE][WSSIZE], int row, int col) {
    int coincidences = 0;
    std::vector<std::string> candidates(8, "");

    for (int i = 0; i < 4; i++) {
        candidates[0] += charAt(wordSearch, row + i, col);
        candidates[1] += charAt(wordSearch, row - i, col);
        candidates[2] += charAt(wordSearch, row, col + i);
        candidates[3] += charAt(wordSearch, row, col - i);
        candidates[4] += charAt(wordSearch, row + i, col + i);
        candidates[5] += charAt(wordSearch, row + i, col - i);
        candidates[6] += charAt(wordSearch, row - i, col + i);
        candidates[7] += charAt(wordSearch, row - i, col - i);
    }

    for (const std::string &candidate : candidates) {
        if (candidate == "XMAS")
            coincidences++;
    }
    
    return coincidences;
}

int countXMAS(char wordSearch[WSSIZE][WSSIZE]) {
    int count = 0;
    for (int i = 0; i < WSSIZE; i++) {
        for (int j = 0; j < WSSIZE; j++) {
            if (wordSearch[i][j] == 'X') {
                count += evaluateCoincidences(wordSearch, i, j);   
            }
        }
    }

    return count;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Error. No input file provided." << std::endl;
        return -1;
    }

    char wordSearch[WSSIZE][WSSIZE];
    readInput(argv[1], wordSearch);

    std::cout << "Part 1 solution: " << countXMAS(wordSearch) << std::endl;

    return 0;
}