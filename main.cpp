#include <iostream>
#include <vector>
#include "data.h"

int main() {
    std::vector<int> data = createDataArray();
    for (const auto &item: data) {
        printf_s("%d, ", item);
    }
    return 0;
}
