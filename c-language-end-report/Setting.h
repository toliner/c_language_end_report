//
// Created by reg on 2022/05/12.
//

#ifndef C_LANGUAGE_2_SETTING_H

#define C_LANGUAGE_2_SETTING_H

extern "C" {
	int readInt(const char* section, const char* keyword, int defaultValue, const char* filePath);
	int readChar(const char* section, const char* keyword, const char* defaultValue, char* returnValue, const char* filePath);
	double readDouble(const char* section, const char* keyword, double defaultValue, const char* filePath);
	void getCurrentDirectory(char* currentDirectory);
	int writeChar(const char* section, const char* keyword, const char* writeValue, const char* filePath);
	int writeInt(const char* section, const char* keyword, int writeValue, const char* filePath);
	int writeDouble(const char* section, const char* keyword, double writeValue, const char* filePath);
}

#endif //C_LANGUAGE_2_SETTING_H
