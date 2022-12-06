#include <iostream>

#include "GrammarReader.h"

int main()
try
{
	GrammarReader reader(std::cin);

	auto machine = reader.ReadRightGrammar();

	return 0;
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;

	return 1;
}
