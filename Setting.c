#include "Setting.h"
#include <stdio.h>
#include <Windows.h>
#define CHARBUFF 124

int readInt(const char *section, const char *keyword, int defaultValue, const char *filePath) {
    char currentDirectory[CHARBUFF];
    getCurrentDirectory(currentDirectory);
    char settingFile[CHARBUFF];
    sprintf(settingFile, filePath, currentDirectory);
    return GetPrivateProfileInt(section, keyword, defaultValue, settingFile);
}

int readChar(const char *section, const char *keyword, const char *defaultValue, char *returnValue, const char *filePath) {
    char currentDirectory[CHARBUFF];
    getCurrentDirectory(currentDirectory);
    char settingFile[CHARBUFF];
    sprintf(settingFile, filePath, currentDirectory);

    return GetPrivateProfileStringA(section, keyword, defaultValue, returnValue, CHARBUFF, settingFile);
}

double readDouble(const char *section, const char *keyword, double defaultValue, const char *filePath) {
    char currentDirectory[CHARBUFF];
    getCurrentDirectory(currentDirectory);
    char settingFile[CHARBUFF];
    sprintf(settingFile, filePath, currentDirectory);
    char str[CHARBUFF];
    char defaultValueStr[CHARBUFF];
    sprintf(defaultValueStr, "%lf", defaultValue);
    readChar(section, keyword, defaultValueStr, str, filePath);
    return strtod(defaultValueStr, NULL);
}

void getCurrentDirectory(char *currentDirectory) {
    GetCurrentDirectory(CHARBUFF, currentDirectory);
}

int writeChar(const char *section, const char *keyword, const char *writeValue, const char *filePath) {
    char currentDirectory[CHARBUFF];
    getCurrentDirectory(currentDirectory);
    char settingFile[CHARBUFF];
    sprintf(settingFile, filePath, currentDirectory);
    return WritePrivateProfileStringA(section, keyword, writeValue, settingFile);
}

int writeInt(const char *section, const char *keyword, int writeValue, const char *filePath) {
    char currentDirectory[CHARBUFF];
    getCurrentDirectory(currentDirectory);
    char settingFile[CHARBUFF];
    sprintf(settingFile, filePath, currentDirectory);
    char str[CHARBUFF];
    sprintf(str, "%d", writeValue);
    return WritePrivateProfileStringA(section, keyword, str, settingFile);
}

int writeDouble(const char *section, const char *keyword, double writeValue, const char *filePath) {
    char currentDirectory[CHARBUFF];
    getCurrentDirectory(currentDirectory);
    char settingFile[CHARBUFF];
    sprintf(settingFile, filePath, currentDirectory);
    char str[CHARBUFF];
    sprintf(str, "%lf", writeValue);
    return WritePrivateProfileStringA(section, keyword, str, settingFile);
}
