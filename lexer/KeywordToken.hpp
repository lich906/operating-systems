#pragma once

#include "Token.h"

// clang-format off

template <Token T>
struct KeywordToken
{
	static inline std::string Get() { return {}; }
};

template <>
struct KeywordToken<Token::If>
{
	static inline std::string Get() { return "if"; }
};

template <>
struct KeywordToken<Token::Else>
{
	static inline std::string Get() { return "else"; }
};

template <>
struct KeywordToken<Token::Do>
{
	static inline std::string Get() { return "do"; }
};

template <>
struct KeywordToken<Token::While>
{
	static inline std::string Get() { return "while"; }
};

template <>
struct KeywordToken<Token::For>
{
	static inline std::string Get() { return "for"; }
};

template <>
struct KeywordToken<Token::Int>
{
	static inline std::string Get() { return "int"; }
};

template <>
struct KeywordToken<Token::Double>
{
	static inline std::string Get() { return "double"; }
};

template <>
struct KeywordToken<Token::Bool>
{
	static inline std::string Get() { return "bool"; }
};

// clang-format on
