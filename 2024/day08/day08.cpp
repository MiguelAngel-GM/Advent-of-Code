#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <unordered_map>

#define MAP_SIZE 50

struct MapPosition {
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

void getAntennasCoordinates(const char map[MAP_SIZE][MAP_SIZE], std::unordered_map<char, std::vector<MapPosition>> &antennas) {
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            if (map[i][j] != '.') {
                MapPosition antennaPos = {j, i};
                if (antennas.find(map[i][j]) == antennas.end()) {
                    antennas.insert(std::make_pair(map[i][j], std::vector<MapPosition>({antennaPos})));
                }
                else {
                    antennas.at(map[i][j]).push_back(antennaPos);
                }
            }
        }
    }
}

bool isInBounds(const MapPosition pos) {
    return pos.x >= 0 && pos.x < MAP_SIZE && pos.y >= 0 && pos.y < MAP_SIZE;
}

void calculateAntinodes(
    const MapPosition firstAntenna, 
    const MapPosition secondAntenna, 
    std::vector<MapPosition> &antinodes,
    bool considerHarmonics)    
{
    int dx = abs(firstAntenna.x - secondAntenna.x);
    int dy = abs(firstAntenna.y - secondAntenna.y);

    MapPosition antinode1;
    antinode1.x = firstAntenna.x < secondAntenna.x ? firstAntenna.x + 2 * dx : firstAntenna.x - 2 * dx;
    antinode1.y = firstAntenna.y < secondAntenna.y ? firstAntenna.y + 2 * dy : firstAntenna.y - 2 * dy;
    if (isInBounds(antinode1))
        antinodes.push_back(antinode1);

    MapPosition antinode2;
    antinode2.x = secondAntenna.x < firstAntenna.x ? secondAntenna.x + 2 * dx : secondAntenna.x - 2 * dx;
    antinode2.y = secondAntenna.y < firstAntenna.y ? secondAntenna.y + 2 * dy : secondAntenna.y - 2 * dy;
    if (isInBounds(antinode2))
        antinodes.push_back(antinode2);
}

int countAntinodes(char map[MAP_SIZE][MAP_SIZE], bool considerHarmonics) {
    int antinodes = 0;

    // Map with coordinates of every instance of each antenna
    std::unordered_map<char, std::vector<MapPosition>> antennas;
    getAntennasCoordinates(map, antennas);

    for (const auto &antennaType : antennas) {
        std::vector<MapPosition> positions = antennaType.second;
        for (int i = 0; i < positions.size(); i++) {
            for (int j = 0; j < positions.size(); j++) {
                if (i == j)
                    continue;
                
                std::vector<MapPosition> antinodesPos;
                calculateAntinodes(positions[i], positions[j], antinodesPos, considerHarmonics);
                
                for (const MapPosition antinode : antinodesPos) {
                    if (map[antinode.y][antinode.x] != '#') {
                        map[antinode.y][antinode.x] = '#';
                        antinodes++;
                    }
                }
            }

            if (considerHarmonics)
                antinodes++;
        }
    } 

    return antinodes;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Error. No input file provided." << std::endl;
        return -1;
    }

    char map[MAP_SIZE][MAP_SIZE];
    readInput(argv[1], map);

    std::cout << "Part 1 solution: " << countAntinodes(map, false) << std::endl;
    
    return 0;
}