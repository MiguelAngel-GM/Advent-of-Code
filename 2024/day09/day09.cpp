#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>

struct Disk {
    std::vector<int> blocks; // Each block will be an int with either a file ID or -1 to represent empty space
    std::queue<size_t> gapsIndices;
    std::stack<size_t> contentIndices;
};

bool readInput(const char *filename, Disk &disk) {
    std::ifstream inputStream(filename);
    if (!inputStream.is_open()) {
        return false;
    }

    std::string line;
    std::getline(inputStream, line);

    int fileIdx = 0;
    for (size_t i = 0; i < line.length(); i++) {
        int nBlocks = line[i] - '0';
        if (i % 2) {
            // empty spaces
            for (int j = 0; j < nBlocks; j++) {
                disk.blocks.push_back(-1);
                disk.gapsIndices.push(disk.blocks.size() - 1);
            }
        }
        else {
            for (int j = 0; j < nBlocks; j++) {
                disk.blocks.push_back(fileIdx);
                disk.contentIndices.push(disk.blocks.size() - 1);
            }
            fileIdx++;
        }
    }

    inputStream.close();
    return true;
}

long compactFiles(Disk &disk) { 
    // Compact and return updated chekcsum
    long checksum = 0;

    size_t nextBlockIdx = disk.contentIndices.top();
    size_t nextGapIdx = disk.gapsIndices.front();
    while (nextBlockIdx > nextGapIdx) {
        std::swap(disk.blocks[nextBlockIdx], disk.blocks[nextGapIdx]);

        disk.contentIndices.pop();
        disk.gapsIndices.pop();

        nextBlockIdx = disk.contentIndices.top();
        nextGapIdx = disk.gapsIndices.front();
    }

    int i = 0;
    while (disk.blocks[i] != -1) {
        checksum += disk.blocks[i] * i;
        i++;
    }

    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Error. No input file provided." << std::endl;
        return -1;
    }

    Disk disk;
    if (!readInput(argv[1], disk)) {
        std::cerr << "Error. Could not open input file." << std::endl;
        return -1;
    }

    std::cout << "Part 1 solution: " << compactFiles(disk) << std::endl; 
    
    return 0;
} 