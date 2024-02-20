#ifdef WIN32
	#include <Windows.h>
#endif
#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include "../core.h"

using namespace std;

namespace ConsoleForeground {
}

class CLogger {
public:
	static void module(const char* msg);
	static void warning(const char* msg);
	static void error(const char* msg);
	static void script(const char* msg);
	static void information(const char* msg);
	static void debug(const char* msg);

	static const string currentDateTime();

	enum ConsoleForeground {
		BLACK = 0,
		DARKBLUE = FOREGROUND_BLUE,
		DARKGREEN = FOREGROUND_GREEN,
		DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DARKRED = FOREGROUND_RED,
		DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
		DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
		DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		GRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
		MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		DARKORANGE = DARKRED | DARKYELLOW,
		ORANGE = RED | YELLOW
	};
};