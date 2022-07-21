#include <vector>
#include "data.h"
#include "sort.h"

std::map<std::string, SortAlgorithm> sortAlgorithms = {
        std::make_pair("", &bubbleSort)
};

int main() {
    std::vector<int> data = createDataArray();
    printf_s("Original Data: \n");
    for (const auto &item: data) {
        printf_s("%d, ", item);
    }
    SortResult result = bubbleSort(data);
    printf_s("\nBubble Sorted. Steps: %d, Result: \n", result.size() - 1);
    for (const auto &item: (result.end() - 1)->currentData) {
        printf_s("%d, ", item);
    }
    return 0;
}
