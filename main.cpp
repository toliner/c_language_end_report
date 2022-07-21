#include <vector>
#include "data.h"
#include "sort.h"

std::map<std::string, SortAlgorithm> sortAlgorithms = {
        std::make_pair("", &bubbleSort)
};

int main() {
    std::vector<int> originalData = createDataArray();
    std::vector<int> data = std::vector<int>(originalData.size());
    printf_s("Original Data: \n");
    for (const auto &item: originalData) {
        printf_s("%d, ", item);
    }
    std::copy(originalData.begin(), originalData.end(), data.begin());
    SortResult result = bubbleSort(data);
    printf_s("\nBubble Sorted. Steps: %d, Result: \n", result.size() - 1);
    for (const auto &item: (result.end() - 1)->currentData) {
        printf_s("%d, ", item);
    }
    std::copy(originalData.begin(), originalData.end(), data.begin());
    result = selectSort(data);
    printf_s("\nSelect Sorted. Steps: %d, Result: \n", result.size() - 1);
    for (const auto &item: (result.end() - 1)->currentData) {
        printf_s("%d, ", item);
    }
    return 0;
}
