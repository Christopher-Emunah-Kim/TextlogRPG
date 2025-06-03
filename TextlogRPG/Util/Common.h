#pragma once

#include <cstdint>

#include <iostream>
#include <string>
#include <sstream>
#include <functional>

#include <array>
#include <vector>
#include <map>
#include <unordered_map>

#include <algorithm>

#include <Windows.h>


using namespace std;

class Common {
public:
	static string ToLower(const string& str) {
		string lowerStr = str;
		transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
		return lowerStr;
	}
	static string ToUpper(const string& str) {
		string upperStr = str;
		transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
		return upperStr;
	}
	static void PrintErrorMsg(const string& errorMessage) {
		cerr << "[Error] " << errorMessage << endl;
	}
	static void PrintInfoMsg(const string& infoMessage) {
		cout << "[Info] " << infoMessage <<endl;
	}
	static void PrintWarningMsg(const string& warningMessage) {
		cerr << "[Warning] " << warningMessage << endl;
	}
	static void PrintSystemMsg(const string& systemMessage) {
		cout << "\n===========================================\n\n";
		cout << "[System] " << systemMessage;
		cout << "\n\n===========================================\n" << endl;
	}

	static void PrintLine() {
		cout << "\n===========================================\n" <<endl;
	}
	
	static void PauseAndClearScreen(int32_t milliseconds=1500) {
		Sleep(milliseconds);
		system("cls");
	}
};