#include <iostream>
#include <filesystem>
#include <argparse.hpp>

#include "Logger.hpp"
#include "GrammarReader.h"
#include "MachineDeterminer.h"

int main(int argc, char** argv)
try
{
	argparse::ArgumentParser program("grammar");
	program.add_argument("-q", "--quiet")
		.default_value(false)
		.implicit_value(true)
		.help("disable console output")
		.action([](auto) { Logger::Quiet(true); });
	program.add_argument("grammar_type")
		.required()
		.help("type of regular grammar ('left' or 'right')");
	program.add_argument("grammar_file")
		.required()
		.help("text file with grammar rules");
	program.add_argument("output_file")
		.remaining()
		.help("output file with result in csv format (if ommited print result to stdout)");

	try
	{
		program.parse_args(argc, argv);
	}
	catch (const std::exception&)
	{
		std::cout << program.help().str() << std::endl;
		throw;
	}

	std::ifstream inputFile(program.get<std::string>("grammar_file"));
	if (!inputFile.is_open())
		throw std::runtime_error("Failed to open grammar file.");

	GrammarReader reader(inputFile);

	bool isRight = false;
	auto grammarType = program.get<std::string>("grammar_type");
	if (isRight = (grammarType == "right"))
	{
	}
	else if (grammarType == "left")
	{
	}
	else
	{
		throw std::runtime_error("Invalid grammar type '" + grammarType + "'");
	}
	
	auto machine = isRight ? reader.ReadRightGrammar() : reader.ReadLeftGrammar();
	const auto determinedMachine = MachineDeterminer::Determine(machine);

	if (auto outputFilename = program.present<std::string>("output_file"))
	{
		std::ofstream outputFile(*outputFilename);
		if (!outputFile.is_open())
			throw std::runtime_error("Failed to open output file.");
		determinedMachine.PrintAsCsv(outputFile);
	}
	else
	{
		determinedMachine.PrintAsCsv(std::cout);
	}

	return 0;
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;

	return 1;
}
