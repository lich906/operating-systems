#include "ProgramArguments.h"

ProgramArguments& ProgramArguments::AddOption(const ProgramOption& option)
{
	m_options.push_back(option);
	return *this;
}

void ProgramArguments::Parse(int argc, char** argv)
{
	std::vector<std::string> arguments;
	std::unordered_set<std::string> options;
	for (int i = 1; i < argc; ++i)
		if (argv[i][0] == '-')
			options.insert(argv[i]);
		else
			arguments.push_back(argv[i]);

	for (auto& option : options)
		if (!ApplyOption(option))
			throw std::runtime_error("Unknown option '" + option + "'");

	if (arguments.size() < Constants::ARGS_COUNT)
		throw std::runtime_error("Too few arguments.");
	else if (arguments.size() > Constants::ARGS_COUNT)
		throw std::runtime_error("Too many arguments.");

	if (arguments[0] != Constants::MEALY_MODE_STR && arguments[0] != Constants::MOORE_MODE_STR)
	{
		throw std::runtime_error("Invalid program mode '" + arguments[0] + "'");
	}

	m_mode = arguments[0];
	m_inputFileName = arguments[1];
	m_outputFileName = arguments[2];

}

bool ProgramArguments::ApplyOption(const std::string& optionStr)
{
	for (const auto& option : m_options)
	{
		if (option.Match(optionStr))
		{
			option.Execute();
			return true;
		}
	}

	return false;
}

void ProgramArguments::SetVerbose(bool verbose)
{
	m_verboseFlag = verbose;
	Logger::m_verboseEnabled = verbose;
}

void ProgramArguments::ShowHelpMessage() const
{
	std::cout << Constants::HELP_MESSAGE << std::endl;
	for (const auto& option : m_options)
	{
		std::cout << option.GetHelpInfo() << std::endl;
	}
}

bool ProgramArguments::VerboseEnabled() const
{
	return m_verboseFlag;
}

bool ProgramArguments::IsMealyMode() const
{
	return m_mode == Constants::MEALY_MODE_STR;
}

bool ProgramArguments::IsMooreMode() const
{
	return m_mode == Constants::MOORE_MODE_STR;
}

const std::string& ProgramArguments::GetInputFileName() const
{
	return m_inputFileName;
}

const std::string& ProgramArguments::GetOutputFileName() const
{
	return m_outputFileName;
}

ProgramOption::ProgramOption(const std::string& shortcut, const std::string& command, const std::string& description, const std::function<void()>& action)
	: m_shortcut('-' + shortcut)
	, m_command("--" + command)
	, m_description(description)
	, m_helpInfo("\t-" + shortcut + " | --" + command + "\t\t\t" + description)
	, m_action(action)
{
}

std::string_view ProgramOption::GetHelpInfo() const
{
	return m_helpInfo;
}

bool ProgramOption::Match(const std::string& str) const
{
	return str == m_shortcut || str == m_command;
}

void ProgramOption::Execute() const
{
	m_action();
}
