#include <optional>

#include "Lexer.h"
#include "NumberParser.h"

std::vector<TokenWithContext> Lexer::Parse(std::istream& input)
{
	std::vector<TokenWithContext> result;

	while (input)
	{
		SkipWhitespaces(input);

		char firstChar;
		TokenWithContext tokWCtx;
		tokWCtx.token = Token::Error;
		tokWCtx.lineNumber = m_lineNum;
		tokWCtx.columnNumber = m_colNum;

		if (IsIdentifierStart(input.peek()))
		{
			std::tie(tokWCtx.token, tokWCtx.lexeme) = ParseIdentifier(input);
		}
		else if (NumberParser::IsNumberStart(input.peek()))
		{
			std::tie(tokWCtx.token, tokWCtx.lexeme) = NumberParser::Parse(input);
			m_colNum += tokWCtx.lexeme.size();
		}
		else if (auto oneSymbolTok = MatchOneSymbolTokens(firstChar = GetChar(input)))
		{
			std::optional<Token> twoSymbolTok;
			if (input && (twoSymbolTok = MatchTwoSymbolTokens(firstChar, input.peek())))
			{
				tokWCtx.token = *twoSymbolTok;
				(tokWCtx.lexeme += firstChar) += GetChar(input);
			}
			else
			{
				tokWCtx.token = *oneSymbolTok;
				tokWCtx.lexeme += firstChar;
			}
		}
		else if (auto twoSymbolTok = MatchTwoSymbolTokens(firstChar, input.peek()))
		{
			tokWCtx.token = *twoSymbolTok;
			(tokWCtx.lexeme += firstChar) += GetChar(input);
		}
		else
		{
			tokWCtx.lexeme += firstChar;
		}

		if (input) result.emplace_back(std::move(tokWCtx));
	}

	return result;
}

void Lexer::SkipWhitespaces(std::istream& input)
{
	char ch;
	while (std::isspace(ch = input.peek()))
	{
		if (ch == '\n')
			NextLine();

		GetChar(input);
	}
}

bool Lexer::IsIdentifierStart(char ch)
{
	return ch == '_' || std::isalpha(ch);
}

bool Lexer::IsIdentifierSymbol(char ch)
{
	return ch == '_' || std::isalnum(ch);
}

int Lexer::GetChar(std::istream& input)
{
	++m_colNum;
	return input.get();
}

void Lexer::NextLine()
{
	++m_lineNum;
	m_colNum = 0;
}

std::optional<Token> Lexer::MatchTwoSymbolTokens(char ch1, char ch2)
{
// clang-format off
	if (TwoSymbolToken<Token::Equal>::Match(ch1, ch2)) return Token::Equal;
	else if (TwoSymbolToken<Token::NotEqual>::Match(ch1, ch2)) return Token::NotEqual;
	else if (TwoSymbolToken<Token::LessEqual>::Match(ch1, ch2)) return Token::LessEqual;
	else if (TwoSymbolToken<Token::GreaterEqual>::Match(ch1, ch2)) return Token::GreaterEqual;
	else if (TwoSymbolToken<Token::DoubleColon>::Match(ch1, ch2)) return Token::DoubleColon;
	else if (TwoSymbolToken<Token::RightArrow>::Match(ch1, ch2)) return Token::RightArrow;
	else if (TwoSymbolToken<Token::CommentOpening>::Match(ch1, ch2)) return Token::CommentOpening;
	else if (TwoSymbolToken<Token::CommentEnding>::Match(ch1, ch2)) return Token::CommentEnding;
// clang-format on

	return std::nullopt;
}

std::optional<Token> Lexer::MatchOneSymbolTokens(char ch)
{
// clang-format off
	if (OneSymbolToken<Token::Plus>::Match(ch)) return Token::Plus;
	else if (OneSymbolToken<Token::Minus>::Match(ch)) return Token::Minus;
	else if (OneSymbolToken<Token::Asterisk>::Match(ch)) return Token::Asterisk;
	else if (OneSymbolToken<Token::Slash>::Match(ch)) return Token::Slash;
	else if (OneSymbolToken<Token::Assignment>::Match(ch)) return Token::Assignment;
	else if (OneSymbolToken<Token::Less>::Match(ch)) return Token::Less;
	else if (OneSymbolToken<Token::Greater>::Match(ch)) return Token::Greater;
	else if (OneSymbolToken<Token::Comma>::Match(ch)) return Token::Comma;
	else if (OneSymbolToken<Token::Dot>::Match(ch)) return Token::Dot;
	else if (OneSymbolToken<Token::Colon>::Match(ch)) return Token::Colon;
	else if (OneSymbolToken<Token::Semicolon>::Match(ch)) return Token::Semicolon;
	else if (OneSymbolToken<Token::LeftParenthesis>::Match(ch)) return Token::LeftParenthesis;
	else if (OneSymbolToken<Token::RightParenthesis>::Match(ch)) return Token::RightParenthesis;
	else if (OneSymbolToken<Token::OpeningCurlyBrace>::Match(ch)) return Token::OpeningCurlyBrace;
	else if (OneSymbolToken<Token::ClosingCurlyBrace>::Match(ch)) return Token::ClosingCurlyBrace;
	else if (OneSymbolToken<Token::OpeningSquareBrace>::Match(ch)) return Token::OpeningSquareBrace;
	else if (OneSymbolToken<Token::ClosingSquareBrace>::Match(ch)) return Token::ClosingSquareBrace;
	// clang-format on

	return std::nullopt;
}

std::optional<Token> Lexer::MatchKeywordTokens(std::string str)
{
// clang-format off
	std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) {
		return std::tolower(c);
	});

	if (str == KeywordToken<Token::Int>::Get()) return Token::Int;
	else if (str == KeywordToken<Token::Double>::Get()) return Token::Double;
	else if (str == KeywordToken<Token::Bool>::Get()) return Token::Bool;
	else if (str == KeywordToken<Token::If>::Get()) return Token::If;
	else if (str == KeywordToken<Token::Else>::Get()) return Token::Else;
	else if (str == KeywordToken<Token::Do>::Get()) return Token::Do;
	else if (str == KeywordToken<Token::While>::Get()) return Token::While;
	else if (str == KeywordToken<Token::For>::Get()) return Token::For;

// clang-format on

	return std::nullopt;
}

std::pair<Token, std::string> Lexer::ParseIdentifier(std::istream& input)
{
	std::string result;

	while (input && IsIdentifierSymbol(input.peek()))
		result.push_back(GetChar(input));

	if (std::optional<Token> token = MatchKeywordTokens(result))
	{
		return { *token, result };
	}

	return { Token::Identifier, result };
}
