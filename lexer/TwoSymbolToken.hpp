#pragma once

#include "Token.h"

// clang-format off

template <Token T>
struct TwoSymbolToken
{
	static inline bool Match(char ch1, char ch2) { return false; }
};

template <>
struct TwoSymbolToken<Token::Equal>
{
	static inline bool Match(char ch1, char ch2) { return ch1 == '=' && ch2 == '='; }
};

template <>
struct TwoSymbolToken<Token::NotEqual>
{
	static inline bool Match(char ch1, char ch2) { return ch1 == '!' && ch2 == '='; }
};

template <>
struct TwoSymbolToken<Token::LessEqual>
{
	static inline bool Match(char ch1, char ch2) { return ch1 == '<' && ch2 == '='; }
};

template <>
struct TwoSymbolToken<Token::GreaterEqual>
{
	static inline bool Match(char ch1, char ch2) { return ch1 == '>' && ch2 == '='; }
};

template <>
struct TwoSymbolToken<Token::DoubleColon>
{
	static inline bool Match(char ch1, char ch2) { return ch1 == ':' && ch2 == ':'; }
};

template <>
struct TwoSymbolToken<Token::RightArrow>
{
	static inline bool Match(char ch1, char ch2) { return ch1 == '-' && ch2 == '>'; }
};

template <>
struct TwoSymbolToken<Token::CommentOpening>
{
	static inline bool Match(char ch1, char ch2) { return ch1 == '/' && ch2 == '*'; }
};

template <>
struct TwoSymbolToken<Token::CommentEnding>
{
	static inline bool Match(char ch1, char ch2) { return ch1 == '*' && ch2 == '/'; }
};

// clang-format on
