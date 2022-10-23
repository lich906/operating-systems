#ifndef PROGRAM_ARGUMENTS_H
#define PROGRAM_ARGUMENTS_H

#include "common.h"

class ProgramOption
{
public:
	ProgramOption(const std::string& shortcut, const std::string& command,
		const std::string& description, const std::function<void()>& action);

	std::string_view GetHelpInfo() const;

	bool Match(const std::string& str) const;

	void Execute() const;

private:
	const std::string m_shortcut;
	const std::string m_command;
	const std::string m_description;
	const std::string m_helpInfo;
	std::function<void()> m_action;
};

class ProgramArguments
{
public:
	ProgramArguments& AddOption(const ProgramOption& option);

	void Parse(int argc, char** argv);

	/*
		returns
		- true if option was applied
		- false otherwise
	*/
	bool ApplyOption(const std::string& optionStr);

	void SetVerbose(bool verbose);

	void ShowHelpMessage() const;

	bool VerboseEnabled() const;

	bool IsMealyMode() const;

	bool IsMooreMode() const;

	const std::string& GetInputFileName() const;

	const std::string& GetOutputFileName() const;

private:
	std::vector<ProgramOption> m_options;

	bool m_verboseFlag = false;
	std::string m_mode;
	std::string m_inputFileName;
	std::string m_outputFileName;
};

#endif // !PROGRAM_ARGUMENTS_H
