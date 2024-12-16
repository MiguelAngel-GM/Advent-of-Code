#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

void readInput(const char *filename, std::unordered_map<int, std::vector<int>> &rules, std::vector<std::vector<int>> &updates) {
    std::ifstream inputStream(filename);
    std::string line;
    bool parseAsRule = true;

    while (std::getline(inputStream, line)) {
        if (line == "") {
            parseAsRule = false;
            continue;
        }
        
        if (parseAsRule) {
            size_t separatorIdx = line.find('|');
            int left = stoi(line.substr(0, separatorIdx + 1));
            int right = stoi(line.substr(separatorIdx + 1, line.length() - separatorIdx));
            if (rules.find(left) == rules.end())
                rules.insert(std::make_pair(left, std::vector<int>({right})));
            else 
                rules.at(left).push_back(right);
        }
        else {
            std::vector<int> update;
            std::stringstream sstream(line);
            std::string value;

            while (std::getline(sstream, value, ','))
                update.push_back(stoi(value));

            updates.push_back(update);
        }
    }

    inputStream.close();
}

bool compliesWithRules(const std::unordered_map<int, std::vector<int>> &rules, const std::vector<int> &update) {
    for (size_t i = 0; i < update.size(); i++) {
        for (size_t j = 0; j < i; j++) {
            std::vector<int> valuesAfter = rules.at(update[i]);
            auto it = std::find(valuesAfter.begin(), valuesAfter.end(), update[j]);
            if (it != valuesAfter.end())
                return false;
        }
    }

    return true;
}

int checkOrders(const std::unordered_map<int, std::vector<int>> &rules, const std::vector<std::vector<int>> &updates) {
    int midPageSum = 0;

    for (const std::vector<int> &update : updates) {
        if (compliesWithRules(rules, update))
            midPageSum += update[std::round(update.size() / 2)];
    }

    return midPageSum;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Error. No input file provided." << std::endl;
        return -1;
    }

    std::unordered_map<int, std::vector<int>> rules;
    std::vector<std::vector<int>> updates;
    readInput(argv[1], rules, updates);

    std::cout << "Part 1 solution: " << checkOrders(rules, updates) << std::endl;

    return 0;
}