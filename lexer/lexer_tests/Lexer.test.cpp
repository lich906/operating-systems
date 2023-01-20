#include "catch2/catch.hpp"
#include <sstream>

#include "Lexer.h"

TEST_CASE("test keywords")
{
	Lexer lexer;
	std::istringstream input(R"(
if
else
do
while
for
int
double
bool
)");

	auto result = lexer.Parse(input);

	CHECK(result[0].token == Token::If);
	CHECK(result[1].token == Token::Else);
	CHECK(result[2].token == Token::Do);
	CHECK(result[3].token == Token::While);
	CHECK(result[4].token == Token::For);
	CHECK(result[5].token == Token::Int);
	CHECK(result[6].token == Token::Double);
	CHECK(result[7].token == Token::Bool);
}

TEST_CASE("test identifiers")
{
	Lexer lexer;
	std::istringstream input(R"(
firstId
id2WithD1g1ts
23invalidId
)");

	auto result = lexer.Parse(input);

	CHECK(result[0].token == Token::Identifier);
	CHECK(result[0].lexeme == "firstId");
	CHECK(result[1].token == Token::Identifier);
	CHECK(result[1].lexeme == "id2WithD1g1ts");
	CHECK(result[2].token == Token::Error);
	CHECK(result[2].lexeme == "23invalidId");
}
