#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <unordered_map>

void readInput(const char *filename, std::vector<int> &leftList, std::vector<int> &rightList) {
    std::ifstream inputStream(filename);
    std::string line;
    std::regex re("([0-9]+)\\s+([0-9]+)");   // Matches an integer, whitespaces and another integer

    while (std::getline(inputStream, line)) {
        std::smatch match;
        std::regex_match(line, match, re);
        if (match.size() == 3) {
            leftList.push_back(stoi(match[1].str()));
            rightList.push_back(stoi(match[2].str()));
        }
    }

    inputStream.close();
}

int getTotalDistance(std::vector<int> leftList, std::vector<int> rightList) {
    int totalDistance = 0;
    
    std::sort(leftList.begin(), leftList.end());
    std::sort(rightList.begin(), rightList.end());

    for (size_t i = 0; i < leftList.size(); i++) {
        totalDistance += abs(leftList[i] - rightList[i]);
    }
    
    return totalDistance;
}

int getSimilarityScore(std::vector<int> leftList, std::vector<int> rightList) {
    int similarityScore = 0;
    
    std::unordered_map<int, int> occurenceMap;
    for (const int nRight : rightList) {
        if (occurenceMap.find(nRight) == occurenceMap.end()) {
            occurenceMap.insert(std::make_pair(nRight, 1));
        }
        else {
            occurenceMap.at(nRight)++;
        }
    }

    for (const int nLeft : leftList) {
        if (occurenceMap.find(nLeft) == occurenceMap.end())
            continue;
        similarityScore += nLeft * occurenceMap.at(nLeft);
    }

    return similarityScore;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Error. No input file provided." << std::endl;
        return -1;
    }
    std::vector<int> leftList, rightList;
    readInput(argv[1], leftList, rightList);

    std::cout << "Part 1 solution: " << getTotalDistance(leftList, rightList) << std::endl;
    std::cout << "Part 2 solution: " << getSimilarityScore(leftList, rightList) << std::endl;

    return 0;
}