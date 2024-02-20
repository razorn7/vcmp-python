#pragma warning(disable:4996) /* _CRT_SECURE_WARNINGS */

#include <iostream>
#include <assert.h>
#include <time.h>
#include <fstream>
#include "console.h"
#include "../core.h"

using namespace std;

bool debug_messages;
bool enable_logger;
bool logger_timestamp;
std::string timestamp_format;
std::string file_name;

/*
	@ credits to habi
	@ https://github.com/habi498/logfile-maker/blob/main/SQFuncs.cpp
*/
void refresh_logger() {
	if (enable_logger) {
		HANDLE hcons = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO info;

		GetConsoleScreenBufferInfo(hcons, &info);
		size_t y = info.dwCursorPosition.Y + 1, x = info.dwSize.X;
		COORD start;
		start.X = 0;
		start.Y = 0;

		CHAR_INFO* buffer = (CHAR_INFO*)
			malloc(sizeof(CHAR_INFO) * (size_t)info.dwSize.X * info.dwSize.Y);
		SMALL_RECT rect;

		rect.Top = 0;
		rect.Left = 0;
		rect.Bottom = y - 1;
		rect.Right = x - 1;

		bool read = ReadConsoleOutput(hcons, buffer, info.dwSize, start, &rect);
		if (read != 0) {
			std::ofstream myfile;
			myfile.open(file_name.c_str());

			for (int i = 0; i < x * y; i++) {
				myfile << buffer[i].Char.AsciiChar;
				if ((i + 1) % x == 0) {
					myfile << std::endl;
				}
			}
			myfile.close();
			free(buffer);
		}
	}

	remove("server_log.txt");
}

const string CLogger::currentDateTime() {
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), timestamp_format.c_str(), &tstruct);

	return buf;
}

void CLogger::module(const char* msg) {
#ifdef WIN32
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbBefore;
	GetConsoleScreenBufferInfo(hstdout, &csbBefore);

	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::DARKGREEN);
	std::cout << "[MODULE] ";

	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::WHITE);
	std::cout << msg << std::endl;

	SetConsoleTextAttribute(hstdout, csbBefore.wAttributes);
#else
	printf("%s %c[0;32m[MODULE]%c[0;37m %s\n", 27, 27, msg);
#endif

	refresh_logger();
}

void CLogger::warning(const char* msg){
#ifdef WIN32
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbBefore;
	GetConsoleScreenBufferInfo(hstdout, &csbBefore);
	if (logger_timestamp == true) {
		SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
		std::cout << currentDateTime() << " ";
	}

	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
	std::cout << "[";
	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::DARKORANGE);
	std::cout << "warning";
	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
	std::cout << "] ";

	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
	std::cout << msg << std::endl;

	SetConsoleTextAttribute(hstdout, csbBefore.wAttributes);
#else
	printf("%c[0;30m[WARN]%c[0;37m %s\n", 27, 27, msg);
#endif

	refresh_logger();
}

void CLogger::debug(const char* msg) {
	if (debug_messages == true) {
#ifdef WIN32
		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_SCREEN_BUFFER_INFO csbBefore;
		GetConsoleScreenBufferInfo(hstdout, &csbBefore);
		if (logger_timestamp == true) {
			SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
			std::cout << currentDateTime() << " ";
		}

		SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
		std::cout << "[";
		SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::DARKCYAN);
		std::cout << "debug";
		SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
		std::cout << "] ";

		SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
		std::cout << msg << std::endl;

		SetConsoleTextAttribute(hstdout, csbBefore.wAttributes);
#else
		printf("%c[0;30m[WARN]%c[0;37m %s\n", 27, 27, msg);
#endif
	}

	refresh_logger();
}

void CLogger::error(char const* msg) {
#ifdef WIN32
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbBefore;
	GetConsoleScreenBufferInfo(hstdout, &csbBefore);
	if (logger_timestamp == true) {
		SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
		std::cout << currentDateTime() << " ";
	}

	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
	std::cout << "[";
	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::RED);
	std::cout << "error";
	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
	std::cout << "] ";

	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
	std::cout << msg << std::endl;

	SetConsoleTextAttribute(hstdout, csbBefore.wAttributes);
#else
	printf("%c[0;30m[ERR]%c[0;37m %s\n", 27, 27, msg);
#endif

	refresh_logger();
}

void CLogger::script(const char* msg) {
#ifdef WIN32
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbBefore;
	GetConsoleScreenBufferInfo(hstdout, &csbBefore);
	if (logger_timestamp) {
		SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
		std::cout << currentDateTime() << " ";
	}

	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
	std::cout << "[";
	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::ORANGE);
	std::cout << "script";
	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
	std::cout << "] ";

	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::WHITE);
	std::cout << msg << std::endl;

	SetConsoleTextAttribute(hstdout, csbBefore.wAttributes);
#else
	printf("%c[0;30m[SCRIPT]%c[0;37m %s\n", 27, 27, msg);
#endif

	refresh_logger();
}

void CLogger::information(const char* msg) {
#ifdef WIN32
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbBefore;
	GetConsoleScreenBufferInfo(hstdout, &csbBefore);
	if (logger_timestamp) {
		SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
		std::cout << currentDateTime() << " ";
	}

	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
	std::cout << "[";
	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::CYAN);
	std::cout << "info";
	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
	std::cout << "] ";

	SetConsoleTextAttribute(hstdout, CLogger::ConsoleForeground::GRAY);
	std::cout << msg << std::endl;

	SetConsoleTextAttribute(hstdout, csbBefore.wAttributes);
#else
	printf("%c[0;30m[INF]%c[0;37m %s\n", 27, 27, msg);
#endif

	refresh_logger();
}

PYBIND11_EMBEDDED_MODULE(vcmp_logger, module)
{
	pybind11::class_<CLogger>(module, "Logger")
		.def_static("info", &CLogger::information)
		.def_static("warning", &CLogger::warning)
		.def_static("debug", &CLogger::debug)
		.def_static("error", &CLogger::error)
		.def_static("script", &CLogger::script);
}