#pragma once

enum class Token
{
	Identifier,

	// reserved words

		If,     // if
		Else,   // else
		Do,     // do
		While,  // while
		For,    // for
		Int,    // int
		Double, // double
		Bool,   // bool

	// ~ reserved words

	// numeric literals

		IntegerNumericLiteral,      // -123
		FloatingPointNumberLiteral, // -32.14
		BinaryNumberLiteral,        // 0b001110
		OctalNumberLiteral,         // 036703
		HexadecimalNumberLiteral,   // 0xBC893

	// ~ numeric literals

	// operators

		//// one-symbol
		Plus,         // +
		Minus,        // -
		Asterisk,     // *
		Slash,        // /
		Assignment,   // =
		Less,         // <
		Greater,      // >

		//// two-symbol
		Equal,        // ==
		NotEqual,     // !=
		LessEqual,    // <=
		GreaterEqual, // >=

		// ~ operators

	// delimiters
	
		//// one-symbol
		Comma,              // ,
		Dot,                // .
		Colon,              // :
		Semicolon,          // ;
		LeftParenthesis,    // (
		RightParenthesis,   // )
		OpeningCurlyBrace,  // {
		ClosingCurlyBrace,  // }
		OpeningSquareBrace, // [
		ClosingSquareBrace, // ]

		//// two-symbol
		DoubleColon,        // ::
		RightArrow,         // ->
		CommentOpening,     // /*
		CommentEnding,      // */

	// ~ delimiters

	Error,
};
