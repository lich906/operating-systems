#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

class Logger
{
public:
	friend class ProgramArguments;

	/*
	Explicitly declare method as inline, so 'data' will be evaluated only if m_verboseEnabled flag is set
	*/
	template <typename T>
	inline static void Log(std::ostream& stream, const T& data)
	{
		if (m_verboseEnabled)
		{
			stream << data << std::endl;
		}
	}

private:
	inline static bool m_verboseEnabled = false;
};

#endif // !LOGGER_H
