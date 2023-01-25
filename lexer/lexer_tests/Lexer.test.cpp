#include "catch.hpp"
#include <sstream>

#include "Lexer.h"
#include "TokenLogger.h"

TEST_CASE("test keywords")
{
	Lexer lexer;
	std::istringstream input(R"(if
else
do
while
for
int
double
bool
)");

	auto result = lexer.Parse(input);

	std::ostringstream oss;
	TokenLogger::SetOutputStream(oss);
	TokenLogger::Log(result);

	REQUIRE(oss.str() == R"(IF 'if' 1:1
ELSE 'else' 2:1
DO 'do' 3:1
WHILE 'while' 4:1
FOR 'for' 5:1
INT 'int' 6:1
DOUBLE 'double' 7:1
BOOL 'bool' 8:1
)");
}

TEST_CASE("valid identifiers")
{
	Lexer lexer;
	std::istringstream input(R"(firstId
id2WithD1g1ts
23invalidId
)");

	auto result = lexer.Parse(input);

	std::ostringstream oss;
	TokenLogger::SetOutputStream(oss);
	TokenLogger::Log(result);

	REQUIRE(oss.str() == R"(IDENTIFIER 'firstId' 1:1
IDENTIFIER 'id2WithD1g1ts' 2:1
ERROR '23invalidId' 3:1
)");
}

TEST_CASE("invalid identifiers")
{

	Lexer lexer;
	std::istringstream input(R"(23invalidId
inval@^%id
)");

	auto result = lexer.Parse(input);

	std::ostringstream oss;
	TokenLogger::SetOutputStream(oss);
	TokenLogger::Log(result);

	REQUIRE(oss.str() == R"(ERROR '23invalidId' 1:1
IDENTIFIER 'inval' 2:1
ERROR '@' 2:6
ERROR '^' 2:7
ERROR '%' 2:8
IDENTIFIER 'id' 2:9
)");
}

TEST_CASE("valid numeric literals")
{
	Lexer lexer;
	std::istringstream input(R"(9345
98.23
0b00111011
001234567
0x0123456789ABCDEF
)");

	auto result = lexer.Parse(input);

	std::ostringstream oss;
	TokenLogger::SetOutputStream(oss);
	TokenLogger::Log(result);
	REQUIRE(oss.str() == R"(INTEGER_LITERAL '9345' 1:1
FLOAT_POINT_NUMBER_LITERAL '98.23' 2:1
BINARY_NUMBER_LITERAL '0b00111011' 3:1
OCTAL_NUMBER_LITERAL '001234567' 4:1
HEXADECIMAL_NUMBER_LITERAL '0x0123456789ABCDEF' 5:1
)");
}

TEST_CASE("invalid numeric literals")
{
	Lexer lexer;
	std::istringstream input(R"(98.
0b001211011
001234987567
0x01234GHJK56789ABCDEF
)");

	auto result = lexer.Parse(input);

	std::ostringstream oss;
	TokenLogger::SetOutputStream(oss);
	TokenLogger::Log(result);
	REQUIRE(oss.str() == R"(ERROR '98.' 1:1
ERROR '0b001211011' 2:1
ERROR '001234987567' 3:1
ERROR '0x01234GHJK56789ABCDEF' 4:1
)");
}

TEST_CASE("full program with all tokens")
{
	Lexer lexer;
	std::istringstream input(R"(int main(int argc, double* argv[])
{
    bool flag = argc;
    do
    {
        if (x->prop >= 0b00111)
        {
            /* z = 5.23 - 00342 + 0xFFE98 * 23 / 45; */
            flag = z <= 2;
        }
    } while (x == x);

    v.y = std::string() != x < (flag > argc);
}
)");

	auto result = lexer.Parse(input);

	std::ostringstream oss;
	TokenLogger::SetOutputStream(oss);
	TokenLogger::Log(result);
	REQUIRE(oss.str() == R"(INT 'int' 1:1
IDENTIFIER 'main' 1:5
LEFT_PARENTHESIS '(' 1:9
INT 'int' 1:10
IDENTIFIER 'argc' 1:14
COMMA ',' 1:18
DOUBLE 'double' 1:20
ASTERISK '*' 1:26
IDENTIFIER 'argv' 1:28
OPENING_SQUARE_BRACE '[' 1:32
CLOSING_SQUARE_BRACE ']' 1:33
RIGHT_PARENTHESIS ')' 1:34
OPENING_CURLY_BRACE '{' 2:1
BOOL 'bool' 3:5
IDENTIFIER 'flag' 3:10
ASSIGNMENT '=' 3:15
IDENTIFIER 'argc' 3:17
SEMICOLON ';' 3:21
DO 'do' 4:5
OPENING_CURLY_BRACE '{' 5:5
IF 'if' 6:9
LEFT_PARENTHESIS '(' 6:12
IDENTIFIER 'x' 6:13
RIGHT_ARROW '->' 6:14
IDENTIFIER 'prop' 6:16
GREATER_EQUAL '>=' 6:21
BINARY_NUMBER_LITERAL '0b00111' 6:24
RIGHT_PARENTHESIS ')' 6:31
OPENING_CURLY_BRACE '{' 7:9
COMMENT_OPENING '/*' 8:13
IDENTIFIER 'z' 8:16
ASSIGNMENT '=' 8:18
FLOAT_POINT_NUMBER_LITERAL '5.23' 8:20
MINUS '-' 8:25
OCTAL_NUMBER_LITERAL '00342' 8:27
PLUS '+' 8:33
HEXADECIMAL_NUMBER_LITERAL '0xFFE98' 8:35
ASTERISK '*' 8:43
INTEGER_LITERAL '23' 8:45
SLASH '/' 8:48
INTEGER_LITERAL '45' 8:50
SEMICOLON ';' 8:52
COMMENT_ENDING '*/' 8:54
IDENTIFIER 'flag' 9:13
ASSIGNMENT '=' 9:18
IDENTIFIER 'z' 9:20
LESS_EQUAL '<=' 9:22
INTEGER_LITERAL '2' 9:25
SEMICOLON ';' 9:26
CLOSING_CURLY_BRACE '}' 10:9
CLOSING_CURLY_BRACE '}' 11:5
WHILE 'while' 11:7
LEFT_PARENTHESIS '(' 11:13
IDENTIFIER 'x' 11:14
EQUAL '==' 11:16
IDENTIFIER 'x' 11:19
RIGHT_PARENTHESIS ')' 11:20
SEMICOLON ';' 11:21
IDENTIFIER 'v' 13:5
DOT '.' 13:6
IDENTIFIER 'y' 13:7
ASSIGNMENT '=' 13:9
IDENTIFIER 'std' 13:11
DOUBLE_COLON '::' 13:14
IDENTIFIER 'string' 13:16
LEFT_PARENTHESIS '(' 13:22
RIGHT_PARENTHESIS ')' 13:23
NOT_EQUAL '!=' 13:25
IDENTIFIER 'x' 13:28
LESS '<' 13:30
LEFT_PARENTHESIS '(' 13:32
IDENTIFIER 'flag' 13:33
GREATER '>' 13:38
IDENTIFIER 'argc' 13:40
RIGHT_PARENTHESIS ')' 13:44
SEMICOLON ';' 13:45
CLOSING_CURLY_BRACE '}' 14:1
)");
}
