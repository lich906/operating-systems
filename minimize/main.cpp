#include "common.h"
#include "ProgramArguments.h"
#include "MealyMachine.h"
#include "MooreMachine.h"

int main(int argc, char** argv)
{
	ProgramArguments arguments;
	arguments
		.AddOption({ "h", "help", "Show help message.", [&]() { arguments.ShowHelpMessage(); exit(0); } })
		.AddOption({ "v", "verbose", "Increase program output and show what is being done.", [&]() { arguments.SetVerbose(true); } });

	try
	{
		arguments.Parse(argc, argv);
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "Use --help command to see program syntax." << std::endl;
		return 1;
	}

	if (arguments.VerboseEnabled())
	{
		std::cout << "Is Mealy Mode: " << arguments.IsMealyMode() << std::endl;
		std::cout << "Is Moore Mode: " << arguments.IsMooreMode() << std::endl;
		std::cout << "Input file name: " << arguments.GetInputFileName() << std::endl;
		std::cout << "Output file name: " << arguments.GetOutputFileName() << std::endl;
		std::cout << "====================================================" << std::endl;
	}

	try
	{
		if (arguments.IsMealyMode())
		{
			MealyMachine mealy;
			mealy.ReadFromCsvFile(arguments.GetInputFileName());
			mealy.Minimize();
			mealy.PrintToCsvFile(arguments.GetOutputFileName());
		}
		else if (arguments.IsMooreMode())
		{
			MooreMachine moore;
			moore.ReadFromCsvFile(arguments.GetInputFileName());
			moore.Minimize();
			moore.PrintToCsvFile(arguments.GetOutputFileName());
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
