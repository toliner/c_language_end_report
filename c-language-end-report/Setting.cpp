#include "Setting.h"
#include <string>
#include <stdio.h>
#include <Windows.h>
#define CHARBUFF 256

int readChar(const char* section, const char* keyword, const char* defaultValue, char* returnValue, const char* filePath) {
    char currentDirectory[CHARBUFF];
    getCurrentDirectory(currentDirectory);
    char settingFile[CHARBUFF];
    sprintf(settingFile, "%s\\%s", currentDirectory, filePath);

    return GetPrivateProfileStringA(section, keyword, defaultValue, returnValue, CHARBUFF, settingFile);
}

void getCurrentDirectory(char* currentDirectory) {
    GetCurrentDirectoryA(CHARBUFF, currentDirectory);
}
