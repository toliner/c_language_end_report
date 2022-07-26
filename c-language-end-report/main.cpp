#include <vector>
#include "data.h"
#include "sort.h"
#include "curses.h"

std::map<std::string, SortAlgorithm> sortAlgorithms = {
        std::make_pair("Bubble Sort", &bubbleSort)
};
int initCurses();
SortAlgorithm selectAlgorithmMenu();

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
    if (initCurses() == 1) {
        return 1;
    }
    while (true) {
        SortAlgorithm algorithm = selectAlgorithmMenu();
        if (algorithm == nullptr) break;

    }
    endwin();
    return 0;
}

int initCurses() {
    if (initscr() == NULL) {
        return 1;
    }
    noecho();
    cbreak();
    timeout(0);
    start_color();
    keypad(stdscr, TRUE);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    return 0;
}

SortAlgorithm selectAlgorithmMenu() {
    while (true) {
        int key = getch();
        if (key == 'q') {
            return nullptr;
        }
        erase();
        attrset(0);
        mvprintw(0, 0, "Algorithm Visualizer");
        mvprintw(2, 1, "Choose Algorithm:");
        int y = 3;
        for (const auto &item: sortAlgorithms) {
            mvprintw(y, 2, "- %s", item.first.c_str());
            y++;
        }
        napms(200);
    }
}
