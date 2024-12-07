#include <iostream>
#include <vector>
#include <fstream>
#include <regex>

void readInput(const char *filename, std::vector<std::vector<int>> &reports) {
    std::ifstream inputStream(filename);
    std::string line;

    while (std::getline(inputStream, line)) {
        std::vector<int> report;
        std::stringstream sstream(line);
        std::string value;

        while (std::getline(sstream, value, ' ')) 
            report.push_back(stoi(value));

        reports.push_back(report);
    }

    inputStream.close();
}

int countSafeReports(const std::vector<std::vector<int>> &reports) { 
    int nSafe = 0;

    for (const std::vector<int> &report : reports)
    {
        bool isSafe = true;
        bool ascending = report[0] < report[1];

        for(size_t i = 1; i < report.size(); i++) {
            bool maintainsTendency = (report[i-1] < report[i] && ascending) || (report[i-1] > report[i] && !ascending);
            
            int distance = abs(report[i-1] - report[i]);
            bool maintainsDistance = distance >= 1 && distance <= 3;

            if (!maintainsTendency || !maintainsDistance) {
                isSafe = false;
                break;
            }
        }

        if (isSafe) 
            nSafe++;
        
    }

    return nSafe;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Error. No input file provided." << std::endl;
        return -1;
    }

    std::vector<std::vector<int>> reports;
    readInput(argv[1], reports);

    std::cout << "Part 1 solution: " << countSafeReports(reports) << std::endl;

    return 0;
}