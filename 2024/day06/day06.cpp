#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

#define MAP_SIZE 130

enum GuardDirection {
    FRONT,
    BACK,
    LEFT,
    RIGHT
};

struct Position {
    int x;
    int y;
};

void readInput(const char *filename, char map[MAP_SIZE][MAP_SIZE]) {
    std::ifstream inputStream(filename);
    std::string line;
    int i = 0;

    while (std::getline(inputStream, line)) {
        memcpy(map[i], line.c_str(), MAP_SIZE);
        i++;
    }

    inputStream.close();
}

void getInitialGuardPos(char map[MAP_SIZE][MAP_SIZE], Position &pos) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[i][j] == '^') {
                pos.x = j;
                pos.y = i;
                return;
            }
        }
    }
}

int countVisitedPositions(char map[MAP_SIZE][MAP_SIZE]) {
    Position guardPos;
    GuardDirection guardDirection = GuardDirection::FRONT;

    getInitialGuardPos(map, guardPos);
    int visitedPositions = 0;

    while (guardPos.x >= 0 && guardPos.x < MAP_SIZE && guardPos.y >= 0 && guardPos.y < MAP_SIZE) {
        if (map[guardPos.y][guardPos.x] != 'X') {
            map[guardPos.y][guardPos.x] = 'X';
            visitedPositions++;
        }
        
        Position nextPos = {guardPos.x, guardPos.y};
        switch (guardDirection) {
            case GuardDirection::FRONT:
                if (guardPos.y - 1 == MAP_SIZE || map[guardPos.y - 1][guardPos.x] != '#') {
                    nextPos.y--;
                }
                else {
                    guardDirection = GuardDirection::RIGHT;
                }
            break;
            case GuardDirection::BACK:
                if (guardPos.y + 1 < 0 || map[guardPos.y + 1][guardPos.x] != '#') {
                    nextPos.y++;
                }
                else {
                    guardDirection = GuardDirection::LEFT;
                }
            break;
            case GuardDirection::LEFT:
                if (guardPos.x - 1 < 0 || map[guardPos.y][guardPos.x - 1] != '#') {
                    nextPos.x--;
                }
                else {
                    guardDirection = GuardDirection::FRONT;
                }
            break;
            case GuardDirection::RIGHT:
                if (guardPos.x + 1 == MAP_SIZE || map[guardPos.y][guardPos.x + 1] != '#') {
                    nextPos.x++;
                }
                else {
                    guardDirection = GuardDirection::BACK;
                }
            break;
        }
        
        guardPos = nextPos;
    }

    return visitedPositions;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Error. No input file provided." << std::endl;
        return -1;
    }

    char map[MAP_SIZE][MAP_SIZE];
    readInput(argv[1], map);

    std::cout << "Part 1 solution: " << countVisitedPositions(map) << std::endl;
    
    return 0;
}