#include <Windows.h>
#ifndef C_LANGUAGE_2_SETTING_H

#define C_LANGUAGE_2_SETTING_H

int readChar(const char* section, const char* keyword, const char* defaultValue, char* returnValue, const char* filePath);
void getCurrentDirectory(char* currentDirectory);

#endif //C_LANGUAGE_2_SETTING_H
