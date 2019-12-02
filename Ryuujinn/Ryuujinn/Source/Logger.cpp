#include "Logger.h"
#include <stdarg.h>
#include <string>
#include <iostream>
#include <Windows.h>

void Logger::LogError(const char* fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	char msg[1024] = { 0 };
	vsprintf_s(msg, 1024, fmt, arg);
	va_end(arg);

	SwtichColorToRed();
	std::cout << msg << std::endl;
	SwitchColorToWhite();
}

void Logger::LogWarning(const char* fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	char msg[1024] = { 0 };
	vsprintf_s(msg, 1024, fmt, arg);
	va_end(arg);

	SwitchColorToYellow();
	std::cout << msg << std::endl;
	SwitchColorToWhite();
}

void Logger::Log(const char* fmt, ...)
{
	va_list arg;
	va_start(arg, fmt);
	char msg[1024] = { 0 };
	vsprintf_s(msg, 1024, fmt, arg);
	va_end(arg);

	std::cout << msg << std::endl;
}

void Logger::SwtichColorToRed()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
}

void Logger::SwitchColorToYellow()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
}

void Logger::SwitchColorToWhite()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}