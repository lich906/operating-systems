#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

#include "TokenWithContext.h"
#include "TwoSymbolToken.hpp"
#include "OneSymbolToken.hpp"
#include "KeywordToken.hpp"

class Lexer
{
public:
	std::vector<TokenWithContext> Parse(std::istream& input);

private:
	std::optional<Token> MatchTwoSymbolTokens(char ch1, char ch2);
	std::optional<Token> MatchOneSymbolTokens(char ch);
	std::optional<Token> MatchKeywordTokens(std::string str);

	std::pair<Token, std::string> ParseIdentifier(std::istream& input);
	void SkipWhitespaces(std::istream& input);

	bool IsIdentifierStart(char ch);
	bool IsIdentifierSymbol(char ch);

	int GetChar(std::istream& input);
	void NextLine();

	size_t m_lineNum = 1, m_colNum = 1;
};
