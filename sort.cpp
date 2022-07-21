#include <utility>
#include "sort.h"

SortResult bubbleSort(std::vector<int> &data) {
    SortResult result = std::vector<SortStep>();
    std::vector<int> original(data.size());
    std::copy(data.begin(), data.end(), original.begin());
    result.push_back(SortStep{
            -1,
            original
    });
    int n = data.size() - 1;
    int k = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = n; j > i; j--) {
            if (data[j] < data[j - 1]) {
                std::iter_swap(data.begin() + j, data.begin() + j - 1);

                SortStep step = SortStep{
                        k,
                        std::vector<int>(data.size())
                };
                std::copy(data.begin(), data.end(), step.currentData.begin());
                result.push_back(step);
                k++;
            }
        }
    }
    return result;
}
