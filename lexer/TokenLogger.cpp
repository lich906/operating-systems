#include <unordered_map>

#include "TokenLogger.h"

static const std::unordered_map<Token, std::string> tokenNames = {
	{ Token::Identifier, "IDENTIFIER" },
	{ Token::If, "IF" },
	{ Token::Else, "ELSE" },
	{ Token::Do, "DO" },
	{ Token::While, "WHILE" },
	{ Token::For, "FOR" },
	{ Token::Int, "INT" },
	{ Token::Double, "DOUBLE" },
	{ Token::Bool, "BOOL" },
	{ Token::IntegerNumericLiteral, "INTEGER_LITERAL" },
	{ Token::FloatingPointNumberLiteral, "FLOAT_POINT_NUMBER_LITERAL" },
	{ Token::BinaryNumberLiteral, "BINARY_NUMBER_LITERAL" },
	{ Token::OctalNumberLiteral, "OCTAL_NUMBER_LITERAL" },
	{ Token::HexadecimalNumberLiteral, "HEXADECIMAL_NUMBER_LITERAL" },
	{ Token::Plus, "PLUS" },
	{ Token::Minus, "MINUS" },
	{ Token::Asterisk, "ASTERISK" },
	{ Token::Slash, "SLASH" },
	{ Token::Assignment, "ASSIGNMENT" },
	{ Token::Less, "LESS" },
	{ Token::Greater, "GREATER" },
	{ Token::Equal, "EQUAL" },
	{ Token::NotEqual, "NOT_EQUAL" },
	{ Token::LessEqual, "LESS_EQUAL" },
	{ Token::GreaterEqual, "GREATER_EQUAL" },
	{ Token::Comma, "COMMA" },
	{ Token::Dot, "DOT" },
	{ Token::Colon, "COLON" },
	{ Token::Semicolon, "SEMICOLON" },
	{ Token::LeftParenthesis, "LEFT_PARENTHESIS" },
	{ Token::RightParenthesis, "RIGHT_PARENTHESIS" },
	{ Token::OpeningCurlyBrace, "OPENING_CURLY_BRACE" },
	{ Token::ClosingCurlyBrace, "CLOSING_CURLY_BRACE" },
	{ Token::OpeningSquareBrace, "OPENING_SQUARE_BRACE" },
	{ Token::ClosingSquareBrace, "CLOSING_SQUARE_BRACE" },
	{ Token::DoubleColon, "DOUBLE_COLON" },
	{ Token::RightArrow, "RIGHT_ARROW" },
	{ Token::CommentOpening, "COMMENT_OPENING" },
	{ Token::CommentEnding, "COMMENT_ENDING" },
	{ Token::Error, "ERROR" }
};

void TokenLogger::SetOutputStream(std::ostream& out)
{
	m_out = out;
}

void TokenLogger::Log(const TokenWithContext& tokenWithCtx)
{
	m_out.get() << (tokenWithCtx.token == Token::Error ? "\n" : "")
		<< tokenNames.at(*tokenWithCtx.token) << " '" << tokenWithCtx.lexeme << "' " << tokenWithCtx.lineNumber << ':'
				<< tokenWithCtx.columnNumber << (tokenWithCtx.token == Token::Error ? "\n" : "") << std::endl;
}
