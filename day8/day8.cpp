#include <iostream>
#include <vector>
#include <fstream>
#include <string>

void readInput(std::vector<std::vector<int>> &grid) {
    std::ifstream input;
    input.open("input.txt");

    std::string line;

    while(std::getline(input, line)) {
        std::vector<int> row;

        for(int i = 0; i < line.length(); i++) {
            row.push_back(line[i] - 48);    // line[i] - 48 gets the number represented by the ascii code of the char
        }

        grid.push_back(row);
    }

    input.close();
}

int isVisible(const std::vector<std::vector<int>> &grid, const int &row, const int &col) {
    int top = 1, bottom = 1, left = 1, right = 1;
    
    for(int i = 0; i < row; i++) {
        if(grid[i][col] >= grid[row][col]) {
            top = 0;
            break;
        }
    }

    for(int i = row + 1; i < grid.size(); i++) {
        if(grid[i][col] >= grid[row][col]) {
            bottom = 0;
            break;
        }
    }

    for(int j = 0; j < col; j++) {
        if(grid[row][j] >= grid[row][col]) {
            left = 0;
            break;
        }
    }

    for(int j = col + 1; j < grid[0].size(); j++) {
        if(grid[row][j] >= grid[row][col]) {
            right = 0;
            break;
        }
    }

    return top || bottom || left || right;
}

int getScenicScore(const std::vector<std::vector<int>> &grid, const int &row, const int &col) {
    int top = 0, bottom = 0, left = 0, right = 0;

    for(int i = row - 1; i >= 0; i--) {
        top++;
        if(grid[i][col] >= grid[row][col]) {
            break;
        }
    }

    for(int i = row + 1; i < grid.size(); i++) {
        bottom++;
        if(grid[i][col] >= grid[row][col]) {
            break;
        }
    }

    for(int j = col - 1; j >= 0; j--) {
        left++;
        if(grid[row][j] >= grid[row][col]) {
            break;
        }
    }

    for(int j = col + 1; j < grid[0].size(); j++) {
        right++;
        if(grid[row][j] >= grid[row][col]) {
            break;
        }
    }

    return top * bottom * left * right;
}

int part1(const std::vector<std::vector<int>> &grid) {
    int visible_trees;

    visible_trees = 2*grid.size() + 2*(grid[0].size()-2);

    for(int i = 1; i < grid.size()-1; i++) {
        for(int j = 1; j < grid[0].size()-1; j++) {
            visible_trees += isVisible(grid, i, j);
        }
    }

    return visible_trees;
}

int part2(const std::vector<std::vector<int>> &grid) {
    int max_score = 0, current_score;

    for(int i = 1; i < grid.size()-1; i++) {
        for(int j = 1; j < grid[0].size()-1; j++) {
            current_score = getScenicScore(grid, i, j);

            if(current_score > max_score) {
                max_score = current_score;
            }
        }
    }

    return max_score;
}

int main() {
    std::vector<std::vector<int>> grid;
    readInput(grid);

    std::cout << "Part 1 solution: " << part1(grid) << std::endl;
    std::cout << "Part 2 solution: " << part2(grid) << std::endl;
    
    return 0;
}