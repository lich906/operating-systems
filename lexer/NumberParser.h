#pragma once

#include <tuple>
#include <string>

#include "Token.h"

class NumberParser
{
public:
	static bool IsNumberStart(char value);

	static std::tuple<Token, std::string> Parse(std::istream& input);

private:
	static std::string ReadNumber(std::istream& input);
	static Token ParseNumber(const std::string& number);

	static Token ParseInteger(const std::string& number);
	static Token ParseFloatingPoint(const std::string& number);

	static Token ParseHexadecimal(const std::string& number);
	static Token ParseBinary(const std::string& number);
	static Token ParseOctal(const std::string& number);

	static bool IsHexDigit(char ch);
	static bool IsBinaryDigit(char ch);
	static bool IsOctalDigit(char ch);
};
