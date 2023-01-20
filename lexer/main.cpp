#include <iostream>
#include <sstream>

#include "Lexer.h"
#include "TokenLogger.h"

int main()
{
	//std::string str;
	//std::getline(std::cin, str);
	//std::istringstream iss(str);

	TokenLogger::SetOutputStream(std::cout);

	Lexer lexer;

	for (auto&& token : lexer.Parse(std::cin))
	{
		TokenLogger::Log(token);
	}
}
