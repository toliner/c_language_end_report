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
            }
            SortStep step = SortStep{
                    j,
                    std::vector<int>(data.size())
            };
            std::copy(data.begin(), data.end(), step.currentData.begin());
            result.push_back(step);
            k++;
        }
    }
    return result;
}

SortResult selectSort(std::vector<int> &data) {
    SortResult result = std::vector<SortStep>();
    std::vector<int> original(data.size());
    std::copy(data.begin(), data.end(), original.begin());
    result.push_back(SortStep{
            -1,
            original
    });

    int n = data.size();

    for (int i = 0; i < n; i++) {
        int min = i;
        for(int j = i + 1; j < n; j++) {
            if (data[min] > data[j]) {
                min = j;
            }
            SortStep step = SortStep{
                        j,
                        std::vector<int>(data.size())
            };
            std::copy(data.begin(), data.end(), step.currentData.begin());
            result.push_back(step);
        }
        std::iter_swap(data.begin() + i, data.begin() + min);

        SortStep step = SortStep{
                i,
                std::vector<int>(data.size())
        };
        std::copy(data.begin(), data.end(), step.currentData.begin());
        result.push_back(step);
    }
    return result;
}

SortResult insertionSort(std::vector<int>& data) {
    SortResult result = std::vector<SortStep>();
    std::vector<int> original(data.size());
    std::copy(data.begin(), data.end(), original.begin());
    result.push_back(SortStep{
            -1,
            original
        });
    int n = data.size();

    for (int i = 1; i < n; i++) {
        for (int j = i; j >= 1; j--) {
            SortStep step = SortStep{
                        j,
                        std::vector<int>(data.size())
            };
            std::copy(data.begin(), data.end(), step.currentData.begin());
            result.push_back(step);
            if (data[j - 1] < data[j]) break;
            std::iter_swap(data.begin() + j, data.begin() + j - 1);
            step = SortStep{
                        j,
                        std::vector<int>(data.size())
            };
            std::copy(data.begin(), data.end(), step.currentData.begin());
            result.push_back(step);
        }
    }
    return result;
}
