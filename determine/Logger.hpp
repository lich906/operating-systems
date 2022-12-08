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
		if (!m_isQuiet)
		{
			SetConsoleTextAttribute(m_stdOutHandle, color);
			std::cout << data;
		}
	}

	static void Quiet(bool enable)
	{
		m_isQuiet = enable;
	}

private:
	inline static bool m_isQuiet = false;
	inline static HANDLE m_stdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
};
