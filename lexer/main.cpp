#include <iostream>
#include <sstream>

#include "Lexer.h"
#include "TokenLogger.h"

int main()
{
	Lexer lexer;
	TokenLogger::SetOutputStream(std::cout);
	TokenLogger::Log(lexer.Parse(std::cin));
}
