#include "NumberParser.h"
#include <sstream>

bool NumberParser::IsNumberStart(char value)
{
	return std::isdigit(value);
}

std::tuple<Token, std::string> NumberParser::Parse(std::istream& input)
{
	auto const number = ReadNumber(input);
	return { ParseNumber(number), number };
}

std::string NumberParser::ReadNumber(std::istream& input)
{
	bool pointFound = false;
	std::string result;

	while (input && (std::isalnum(input.peek()) || input.peek() == '.'))
	{
		if (input.peek() == '.')
			if (!pointFound)
				pointFound = true;
			else
				return result;

		result += input.get();
	}

	return result;
}

Token NumberParser::ParseNumber(const std::string& number)
{
	if (number.length() == 1)
	{
		return Token::IntegerNumericLiteral;
	}

	std::size_t i = 0;
	auto first = number.at(i++);

	if (first == '0')
	{
		auto second = number.at(i++);
		auto const leftover = number.substr(i);

		switch (second)
		{
		case 'x':
			return ParseHexadecimal(leftover);
		case 'b':
			return ParseBinary(leftover);
		case '.':
			return ParseFloatingPoint(leftover);
		default:
			return ParseOctal(leftover);
		}
	}
	else
	{
		return ParseInteger(number.substr(i));
	}
}

Token NumberParser::ParseInteger(const std::string& number)
{
	for (std::size_t i = 0; i < number.length(); ++i)
	{
		auto& ch = number.at(i);
		if (!std::isdigit(ch))
		{
			if (ch == '.')
			{
				return ParseFloatingPoint(number.substr(i + 1));
			}

			return Token::Error;
		}
	}

	return Token::IntegerNumericLiteral;
}

Token NumberParser::ParseFloatingPoint(const std::string& number)
{
	for (auto ch : number)
	{
		if (!std::isdigit(ch))
		{
			return Token::Error;
		}
	}

	return number.size() ? Token::FloatingPointNumberLiteral : Token::Error;
}

Token NumberParser::ParseHexadecimal(const std::string& number)
{
	if (number.length() == 0)
	{
		return Token::Error;
	}

	for (auto&& ch : number)
	{
		if (!IsHexDigit(ch))
		{
			return Token::Error;
		}
	}

	return Token::HexadecimalNumberLiteral;
}

Token NumberParser::ParseBinary(const std::string& number)
{
	if (number.length() == 0)
	{
		return Token::Error;
	}

	for (auto&& ch : number)
	{
		if (!IsBinaryDigit(ch))
		{
			return Token::Error;
		}
	}

	return Token::BinaryNumberLiteral;
}

Token NumberParser::ParseOctal(const std::string& number)
{
	for (std::size_t i = 0; i < number.length(); ++i)
	{
		auto& ch = number.at(i);

		if (!IsOctalDigit(ch))
		{
			if (ch == '.')
			{
				return ParseFloatingPoint(number.substr(i + 1));
			}

			return Token::Error;
		}
	}

	return Token::OctalNumberLiteral;
}

bool NumberParser::IsHexDigit(char ch)
{
	return std::isdigit(ch) || ('A' <= std::toupper(ch) && std::toupper(ch) <= 'F');
}

bool NumberParser::IsBinaryDigit(char ch)
{
	return ch == '0' || ch == '1';
}

bool NumberParser::IsOctalDigit(char ch)
{
	return '0' <= ch && ch <= '7';
}
