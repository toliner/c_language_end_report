#include <vector>
#include <fstream>
#include <format>
#include <filesystem>
#include "data.h"
#include "sort.h"
#include "curses.h"
#include "Setting.h"

namespace fs = std::filesystem;

std::vector<std::pair<std::string, SortAlgorithm>> sortAlgorithms = {
        std::make_pair("Bubble Sort", &bubbleSort),
        std::make_pair("Select Sort", &selectSort),
        std::make_pair("Insertion Sort", &insertionSort),
        std::make_pair("Shell Sort", &shellSort)
};
int initCurses();
int outputOriginaldata(std::vector<int>& originalData);
void outputSortResult(const std::pair<std::string, SortAlgorithm>& item, SortResult& result);
std::pair<std::string, SortAlgorithm>* selectAlgorithmMenu();
void renderAlgorithmStep(std::string name, SortResult result);
const char border_bar[53] = "----------------------------------------------------";

int main() {
    printf_s("‰æ–ÊƒTƒCƒY‚ð‘å‚«‚­‚µ‚Ä‚­‚¾‚³‚¢\n");

    if (!fs::exists("out")) {
        fs::create_directory("out");
    }
    
    char buffer[128];
    readChar("algorithm_visualizer", "input_file", "", buffer, "settings.ini");
    std::string inputFile(buffer);
    readChar("algorithm_visualizer", "use_file", "false", buffer, "settings.ini");
    std::string useFile(buffer);
    readChar("algorithm_visualizer", "mix_data", "false", buffer, "settings.ini");
    std::string mixData(buffer);
    std::vector<int> originalData = std::vector<int>();
    if (useFile == "true") {
        int i = readDataFromFile(inputFile, mixData == "true", &originalData);
        if (i != 0) {
            return i;
        }
    } else {
        originalData = createDataArray();
    }
    if (outputOriginaldata(originalData)) return -1;

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
    sprintf(fileName, "out/%s.txt", item.first.c_str());
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
    std::ofstream file("out/_Original Data.txt");
    if (file.fail()) {
        fprintf_s(stderr, "Failed to open file: %s", "original_data.txt");
        return -1;
    }
    for (const auto& item : originalData) {
        file << item << std::endl;
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
