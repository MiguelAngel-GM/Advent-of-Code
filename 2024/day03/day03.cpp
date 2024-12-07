#include <iostream>
#include <vector>
#include <fstream>
#include <regex>

int evalMulInstructions(const char *filename, bool useDo) {
    std::ifstream inputStream(filename);
    std::string line;
    
    bool mulEnabled = true;
    std::regex re;
    if (useDo)
        re = std::regex("mul\\(([0-9]+),\\s*([0-9]+)\\)|do\\(\\)|don't\\(\\)");
    else
        re = std::regex("mul\\(([0-9]+),\\s*([0-9]+)\\)");
    int sum = 0;

    while (std::getline(inputStream, line)) {
        std::sregex_iterator reIterator(line.begin(), line.end(), re);
        for (std::sregex_iterator i = reIterator; i != std::sregex_iterator(); i++) {
            std::smatch match = *i;
            if (match.str() == "do()")
                mulEnabled = true;
            else if (match.str() == "don't()")
                mulEnabled = false;
            else 
                sum += stoi(match[1].str()) * stoi(match[2].str()) * mulEnabled;
        }
    }

    inputStream.close();
    return sum;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Error. No input file provided." << std::endl;
        return -1;
    }

    std::cout << "Part 1 solution: " << evalMulInstructions(argv[1], false) << std::endl;
    std::cout << "Part 2 solution: " << evalMulInstructions(argv[1], true) << std::endl;

    return 0;
}