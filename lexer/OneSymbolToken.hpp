#pragma once

#include "Token.h"

// clang-format off

template <Token T>
struct OneSymbolToken
{
	static inline bool Match(char ch) { return false; }
};

template <>
struct OneSymbolToken<Token::Plus>
{
	static inline bool Match(char ch) { return ch == '+'; }
};

template <>
struct OneSymbolToken<Token::Minus>
{
	static inline bool Match(char ch) { return ch == '-'; }
};

template <>
struct OneSymbolToken<Token::Asterisk>
{
	static inline bool Match(char ch) { return ch == '*'; }
};

template <>
struct OneSymbolToken<Token::Slash>
{
	static inline bool Match(char ch) { return ch == '/'; }
};

template <>
struct OneSymbolToken<Token::Assignment>
{
	static inline bool Match(char ch) { return ch == '='; }
};

template <>
struct OneSymbolToken<Token::Less>
{
	static inline bool Match(char ch) { return ch == '<'; }
};

template <>
struct OneSymbolToken<Token::Greater>
{
	static inline bool Match(char ch) { return ch == '>'; }
};

template <>
struct OneSymbolToken<Token::Comma>
{
	static inline bool Match(char ch) { return ch == ','; }
};

template <>
struct OneSymbolToken<Token::Dot>
{
	static inline bool Match(char ch) { return ch == '.'; }
};

template <>
struct OneSymbolToken<Token::Colon>
{
	static inline bool Match(char ch) { return ch == ':'; }
};

template <>
struct OneSymbolToken<Token::Semicolon>
{
	static inline bool Match(char ch) { return ch == ';'; }
};

template <>
struct OneSymbolToken<Token::LeftParenthesis>
{
	static inline bool Match(char ch) { return ch == '('; }
};

template <>
struct OneSymbolToken<Token::RightParenthesis>
{
	static inline bool Match(char ch) { return ch == ')'; }
};

template <>
struct OneSymbolToken<Token::OpeningCurlyBrace>
{
	static inline bool Match(char ch) { return ch == '{'; }
};

template <>
struct OneSymbolToken<Token::ClosingCurlyBrace>
{
	static inline bool Match(char ch) { return ch == '}'; }
};

template <>
struct OneSymbolToken<Token::OpeningSquareBrace>
{
	static inline bool Match(char ch) { return ch == '['; }
};

template <>
struct OneSymbolToken<Token::ClosingSquareBrace>
{
	static inline bool Match(char ch) { return ch == ']'; }
};

// clang-format on
