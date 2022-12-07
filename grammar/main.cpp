#include <iostream>

#include "GrammarReader.h"
#include "MachineDeterminer.h"

int main()
try
{
	GrammarReader reader(std::cin);
	auto machine = reader.ReadRightGrammar();
	const auto determinedMachine = MachineDeterminer::Determine(machine);
	determinedMachine.PrintAsCsv(std::cout);

	return 0;
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;

	return 1;
}
