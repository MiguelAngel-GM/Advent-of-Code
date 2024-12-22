#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <queue>

struct Equation {
    long result;
    std::vector<int> values;
};

void readInput(const char *filename, std::vector<Equation> &equations) {
    std::ifstream inputStream(filename);
    std::string line;
    
    std::regex re("[0-9]+");

    while (std::getline(inputStream, line)) {
        Equation equation;

        std::sregex_iterator reIterator(line.begin(), line.end(), re);
        std::smatch match = *reIterator; 
        equation.result = stol(match[0]);
        
        for (std::sregex_iterator it = ++reIterator; it != std::sregex_iterator(); it++) {
            match = *it;
            equation.values.push_back(stoi(match[0]));
        }
        equations.push_back(equation);
    }

    inputStream.close();
}

/*
    Process al possible values as a tree using a breadth-first search method.
    Each tree node is represented with a pair that contains the node value and the index of the next value in the equation in order to calculate its children.
*/
bool isEquationPossible(const Equation &equation, bool useConcat) {
    std::queue<std::pair<long, int>> possibleValues;
    possibleValues.push(std::make_pair(equation.values[0], 1));

    while (!possibleValues.empty()) {
        std::pair<long, int> currentNode = possibleValues.front();
        long currentValue = currentNode.first;
        int nextIdx = currentNode.second;
        
        if (nextIdx != equation.values.size()) {    // Compute children unless the node is a leaf
            long sum = currentValue + equation.values[nextIdx];
            if (nextIdx == equation.values.size() - 1 && sum == equation.result)
                return true;
            if (sum <= equation.result) 
                possibleValues.push(std::make_pair(sum, nextIdx + 1));

            long product = currentValue * equation.values[nextIdx];
            if (nextIdx == equation.values.size() - 1 && product == equation.result)
                return true;
            if (product <= equation.result)
                possibleValues.push(std::make_pair(product, nextIdx + 1));

            if (useConcat) {
                long concat = std::stol(std::to_string(currentValue) + std::to_string(equation.values[nextIdx]));
                if (nextIdx == equation.values.size() - 1 && concat == equation.result)
                    return true;
                if (concat <= equation.result)
                    possibleValues.push(std::make_pair(concat, nextIdx + 1));
            }
        }
        possibleValues.pop();
    }
    
    return false;
}

long sumPossibleEquations(const std::vector<Equation> &equations, bool useConcat) {
    long sum = 0;

    for (const Equation &equation : equations) {
        if (isEquationPossible(equation, useConcat))
            sum += equation.result;
    }

    return sum;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Error. No input file provided." << std::endl;
        return -1;
    }

    std::vector<Equation> equations;
    readInput(argv[1], equations);

    std::cout << "Part 1 solution: " << sumPossibleEquations(equations, false) << std::endl;
    std::cout << "Part 2 solution: " << sumPossibleEquations(equations, true) << std::endl;

    return 0;
}