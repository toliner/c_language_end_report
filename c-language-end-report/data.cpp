#include "data.h"
#include <fstream>
#include "vector"
#include "string"
#include <algorithm>
#include <random>

std::vector<int> createDataArray() {
    std::vector<int> vector = std::vector<int>();
    for (int i = 0; i < 100; ++i) {
        vector.push_back(i);
    }
    std::random_device seed_gen;
    std::mt19937 engine(seed_gen());
    std::shuffle(vector.begin(), vector.end(), engine);
    return vector;
}

int readDataFromFile(std::string filePath, bool shuffle, std::vector<int> *vector) {
    std::string line;
    std::ifstream file(filePath);

    if (file.fail()) {
        fprintf_s(stderr, "Failed to open file: %s", filePath.data());
        return -1;
    }
    while (std::getline(file, line)) {
        vector->push_back(stoi(line));
    }
    if (shuffle) {
        std::random_device seed_gen;
        std::mt19937 engine(seed_gen());
        std::shuffle(vector->begin(), vector->end(), engine);
    }
    return 0;
}
