#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <algorithm>

struct DiskElement {
    size_t startIdx;
    int size;
};

struct Disk {
    std::vector<int> blocks; // Each block will be an int with either a file ID or -1 to represent empty space
    
    // Data structures for part 1
    std::queue<size_t> gapsIndices;
    std::stack<size_t> contentIndices;

    // Data structures for part 2
    std::vector<DiskElement> gaps;
    std::stack<DiskElement> files;
};

void printDisk(const Disk &disk) {
    for(int i = 0; i < disk.blocks.size(); i++) {
        std::cout << disk.blocks[i] << " ";
    }
    std::cout << std::endl;
}

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
            if (nBlocks > 0) {
                DiskElement gap = {disk.blocks.size(), nBlocks};
                disk.gaps.push_back(gap);
            }
            // empty spaces
            for (int j = 0; j < nBlocks; j++) {
                disk.blocks.push_back(-1);
                disk.gapsIndices.push(disk.blocks.size() - 1);
            }
        }
        else {
            DiskElement file = {disk.blocks.size(), nBlocks};
            disk.files.push(file);
            
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

long compactFiles(Disk disk) { 
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

int findAvailableGap(const std::vector<DiskElement> &gaps, const DiskElement &file) {
    for (size_t i = 0; i < gaps.size(); i++) {
        if (gaps[i].size >= file.size && gaps[i].startIdx < file.startIdx)
            return i;
    }

    return -1;
}

long compactFilesNoFrag(Disk disk) {
    long checksum = 0;

    while (!disk.files.empty()) {
        DiskElement currentFile = disk.files.top();
        int gapIdx = findAvailableGap(disk.gaps, currentFile);
        if (gapIdx != -1) {
            DiskElement gapToFill = disk.gaps[gapIdx];
            for (int i = 0; i < currentFile.size; i++) {
                std::swap(disk.blocks[currentFile.startIdx + i], disk.blocks[gapToFill.startIdx + i]);
            }

            if (gapToFill.size == currentFile.size) {
                disk.gaps.erase(disk.gaps.begin() + gapIdx);
            }
            else {
                disk.gaps[gapIdx].size -= currentFile.size;
                disk.gaps[gapIdx].startIdx += currentFile.size;
            }
        }
        disk.files.pop();
    }

    for (int i = 0; i < disk.blocks.size(); i++) {
        if (disk.blocks[i] == -1)
            continue;
        checksum += disk.blocks[i] * i;
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
    std::cout << "Part 2 solution: " << compactFilesNoFrag(disk) << std::endl; 

    return 0;
} 