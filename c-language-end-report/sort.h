#pragma once
#ifndef C_LANGUAGE_END_REPORT_SORT_H
#define C_LANGUAGE_END_REPORT_SORT_H

#include <vector>
#include <map>
#include <string>

typedef struct SortStep {
    int targetIndex;
    std::vector<int> currentData;
} SortStep;
typedef std::vector<SortStep> SortResult;
typedef SortResult (*SortAlgorithm)(std::vector<int>&);

SortResult bubbleSort(std::vector<int>& data);
SortResult selectSort(std::vector<int>& data);
SortResult insertionSort(std::vector<int>& data);
SortResult shellSort(std::vector<int>& data);

#endif //C_LANGUAGE_END_REPORT_SORT_H
