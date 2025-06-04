#pragma once

typedef signed char			 int8;     //-128~127
typedef short				     int16;   //-32768~32767
typedef int						 int32;   //-2147483648~2147483647
typedef long long			     int64;   //-9223372036854775808~9223372036854775807
typedef unsigned char	     uint8;   //0~255
typedef unsigned short       uint16;  //0~65535
typedef unsigned int          uint32;  //0~4294967295
typedef unsigned long long uint64;  //0~18446744073709551615


#include <iostream>
#include <string>
//#include <sstream>
//#include <functional>

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
	static void PauseAndClearScreen(int32 milliseconds=1500) {
		Sleep(milliseconds);
		system("cls");
	}
	static void ShowOption(const string& text)
	{
		cout << "\n===========================================\n\n";
		cout << text << "\n";
		cout << "\n===========================================" << endl;
	}

	static char GetCharInput()
	{
		char input;
		cin >> input;
		cin.ignore(1024, '\n'); 
		return input;
	}
};