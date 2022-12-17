#pragma once

#include <iostream>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	#include <windows.h>
#endif

class Logger
{
public:
	template <typename T>
	inline static void Log(const T& data, int color)
	{
		if (!m_isQuiet)
		{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
			SetConsoleTextAttribute(m_stdOutHandle, color);
#endif
			std::cout << data;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
			SetConsoleTextAttribute(m_stdOutHandle, 7);
#endif
		}
	}

	template <typename T>
	inline static void Log(const T& data)
	{
		if (!m_isQuiet)
		{
			std::cout << data;
		}
	}

	static void Quiet(bool enable)
	{
		m_isQuiet = enable;
	}

private:
	inline static bool m_isQuiet = false;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
	inline static HANDLE m_stdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
};
