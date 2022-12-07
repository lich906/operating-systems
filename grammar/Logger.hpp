#pragma once

#include <iostream>
#include <windows.h>

class Logger
{
public:
	/*
	Explicitly declare method as inline, so 'data' will be evaluated only if m_isDebug flag is set
	*/
	template <typename T>
	inline static void Log(const T& data, int color = 7)
	{
		if (m_isDebug)
		{
			SetConsoleTextAttribute(m_stdOutHandle, color);
			std::cout << data;
		}
	}

private:
	inline static bool m_isDebug = true;
	inline static HANDLE m_stdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
};
