#include <argparse.hpp>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "Logger.hpp"
#include "MachineDeterminer.h"
#include "fsm/io.h"

int main(int argc, char** argv)
try
{
	argparse::ArgumentParser program("grammar");
	program.add_argument("-q", "--quiet")
		.default_value(false)
		.implicit_value(true)
		.help("disable console output")
		.action([](auto) { Logger::Quiet(true); });
	program.add_argument("input_file")
		.required()
		.help("input file with automata data in csv format");
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

	std::ifstream inputFile(program.get<std::string>("input_file"));
	if (!inputFile.is_open())
		throw std::runtime_error("Failed to open input file.");

	auto machine = fsm::ReadCsv(inputFile);
	const auto determinedMachine = MachineDeterminer::Determine(machine);

	if (auto outputFilename = program.present<std::string>("output_file"))
	{
		std::ofstream outputFile(*outputFilename);
		if (!outputFile.is_open())
			throw std::runtime_error("Failed to open output file.");
		fsm::WriteCsv(outputFile, determinedMachine);
	}
	else
	{
		fsm::WriteCsv(std::cout, determinedMachine);
	}

	return 0;
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;

	return 1;
}
