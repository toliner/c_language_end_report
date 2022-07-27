#include <vector>
#include <fstream>
#include <format>
#include "data.h"
#include "sort.h"
#include "curses.h"

std::vector<std::pair<std::string, SortAlgorithm>> sortAlgorithms = {
        std::make_pair("Bubble Sort", &bubbleSort),
        std::make_pair("Select Sort", &selectSort)
};
int initCurses();
int outputOriginaldata(std::vector<int>& originalData);
void outputSortResult(const std::pair<std::string, SortAlgorithm>& item, SortResult& result);
std::pair<std::string, SortAlgorithm>* selectAlgorithmMenu();
void renderAlgorithmStep(std::string name, SortResult result);
const char border_bar[53] = "----------------------------------------------------";

int main() {
    std::vector<int> originalData = createDataArray();
    
    if (outputOriginaldata(originalData)) return -1;

    printf_s("‰æ–ÊƒTƒCƒY‚ð‘å‚«‚­‚µ‚Ä‚­‚¾‚³‚¢");

    std::map<std::string, SortResult> results;
    for (const auto &item : sortAlgorithms) {
        printf_s("Running Sort: %s\n", item.first.c_str());
        std::vector<int> data = std::vector<int>(originalData.size());
        std::copy(originalData.begin(), originalData.end(), data.begin());
        SortResult result = item.second(data);
        results.insert(std::make_pair(item.first, result));
        outputSortResult(item, result);
    }
    if (initCurses() == 1) {
        return 1;
    }
    while (true) {
        auto algorithm = selectAlgorithmMenu();
        if (algorithm == nullptr) break;
        renderAlgorithmStep(algorithm->first, results[algorithm->first]);
    }
    endwin();
    return 0;
}

void outputSortResult(const std::pair<std::string, SortAlgorithm>& item, SortResult& result) {
    char fileName[128];
    sprintf(fileName, "%s.txt", item.first.c_str());
    std::ofstream file(fileName);
    int i = 0;
    for (const auto& step : result) {
        file << "Step " << i << ":" << std::endl;
        for (const auto& item : step.currentData) {
            file << item << ", ";
        }
        file << std::endl;
        i++;
    }
}

int outputOriginaldata(std::vector<int>& originalData) {
    std::ofstream file("original_data.txt");
    if (file.fail()) {
        fprintf_s(stderr, "Failed to open file: %s", "original_data.txt");
        return -1;
    }
    file.close();
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

std::pair<std::string, SortAlgorithm>* selectAlgorithmMenu() {
    int select = 0;
    while (true) {
        int key = getch();
        switch (key) {
            case 'q':
                return nullptr;
            case KEY_UP:
                if (select != 0) {
                    select--;
                }
                break;
            case KEY_DOWN:
                if (select < sortAlgorithms.size() - 1) {
                    select++;
                }
                break;
            case 'z':
                return &sortAlgorithms[select];
            default:
                break;
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
        mvprintw(3 + select, 2, "*");
        napms(100);
    }
}

void renderAlgorithmStep(std::string name, SortResult result) {
    int step = 0;
    while (true) {
        int key = getch();
        switch (key) {
            case 'q': 
                return;
            case KEY_UP:
            case 'w':
                if (step < result.size() - 11) {
                    step += 10;
                }
                break;
            case KEY_DOWN:
            case 's':
                if (step >= 10) {
                    step -= 10;
                }
                break;
            case KEY_RIGHT:
            case 'd':
                if (step < result.size() - 1) {
                    step += 1;
                }
                break;
            case KEY_LEFT:
            case 'a':
                if (step > 0) {
                    step -= 1;
                };
                break;
            default:
                break;
        }
        erase();
        attrset(0);
        mvprintw(0, 0, "Algorithm Visualizer");
        mvprintw(1, 0, "%s", name.c_str());
        mvprintw(3, 2, border_bar);
        mvprintw(54, 2, border_bar);
        for (int i = 0; i < 50; i++) {
            mvprintw(i + 4, 2, "|");
            mvprintw(i + 4, 54, "|");
        }
        std::vector<int> data = result[step].currentData;
        for (int i = 0; i < 50; i++) {
            int item = data[i];
            if (result[step].targetIndex == i) {
                attrset(COLOR_PAIR(1));
            } else {
                attrset(0);
            }
            for (int j = 0; j < item; j++) {
                mvprintw(53 - j, i + 4, "*");
            }
        }
        attrset(0);
        mvprintw(5, 55, "Step: %d / %d", step + 1, result.size());
        mvprintw(7, 55, "KEY_UP    or W: +10 step");
        mvprintw(8, 55, "KEY_DOWN  or S: -10 step");
        mvprintw(9, 55, "KEY_RIGHT or A: -1  step");
        mvprintw(10,55, "KEY_LEFT  or D: +1  step");
    }
}
