#pragma once

#include <iostream>
#include <functional>

#include "TokenWithContext.h"

class TokenLogger
{
public:
	static void SetOutputStream(std::ostream& out);

	static void Log(const TokenWithContext&);

private:
	inline static std::reference_wrapper<std::ostream> m_out = std::cout;
};
