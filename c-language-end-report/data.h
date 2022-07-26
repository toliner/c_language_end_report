#ifndef C_LANGUAGE_END_REPORT_DATA_H
#define C_LANGUAGE_END_REPORT_DATA_H

#include <string>
#include "vector"

std::vector<int> createDataArray();
int readDataFromFile(std::string filePath, bool shuffle, std::vector<int> *vector);

#endif //C_LANGUAGE_END_REPORT_DATA_H
