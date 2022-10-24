#include "MealyMachine.h"

void MealyMachine::ReadFromCsvFile(const std::string& fileName, const char sep)
{
	std::ifstream file(fileName);

	if (!file.is_open())
		throw std::runtime_error("File " + fileName + " not found.");

	Logger::Log(std::cout, "Reading mealy machine from file '" + fileName + "'...");

	std::vector<std::istringstream> fileStrings;

	for (std::string line; std::getline(file, line);)
		fileStrings.emplace_back(std::move(std::istringstream(line)));

	bool firstIteration = true;
	while (!fileStrings[0].eof())
	{
		std::vector<std::string> column;
		std::string stateName;

		for (size_t i = 0; i < fileStrings.size(); i++)
		{
			std::string item;
			std::getline(fileStrings[i], item, sep);

			if (i == 0)
				stateName = item;
			else
				column.push_back(item);
		}

		if (stateName.empty() || stateName == " ")
		{
			m_inputSignals = column;
		}
		else
		{
			if (firstIteration)
			{
				m_initialStateName = stateName;
				firstIteration = false;
			}

			MealyState state(stateName);

			size_t i = 0;
			for (const auto& transitionStr : column)
			{
				MealyTransition transition = ParseMealyTransition(transitionStr);

				auto nextStateIt = m_states.find(transition.GetNextStateName());
				if (nextStateIt != m_states.end())
				{
					Logger::Log(std::cout, "Threading states... '" + state.GetName() + "' ---" + m_inputSignals[i] + '/' + transition.GetOutputSignal() + "--> '" + nextStateIt->second.GetName() + "'");
					transition.SetNextStatePtr(nextStateIt->second);
				}

				Logger::Log(std::cout, "Creating transition... '" + state.GetName() + "' ---" + m_inputSignals[i] + '/' + transition.GetOutputSignal() + "--> '" + transition.GetNextStateName() + "'");
				state.AddTransition(m_inputSignals[i], transition);
				i++;
			}

			Logger::Log(std::cout, "State '" + state.GetName() + "' created.");
			m_states[stateName] = std::move(state);
		}
	}

	CommonMachineAlgorithm::ThreadStates(m_states, m_inputSignals);
}

void MealyMachine::PrintToCsvFile(const std::string& fileName, const char sep) const
{
	std::ofstream file(fileName);

	if (!file.is_open())
		throw std::runtime_error("File " + fileName + " not found.");

	std::vector<std::string> strings({ {} });

	for (auto& inputSignalId : m_inputSignals)
		strings.push_back(inputSignalId);

	for (auto& [stateName, state] : m_states)
	{
		strings[0].append(sep + state.GetName());

		size_t i = 1;
		for (auto& inputSignal : m_inputSignals)
		{
			auto& tr = state.GetTransition(inputSignal);
			strings[i].append(sep + tr.GetNextStateName() + '/' + tr.GetOutputSignal());
			++i;
		}
	}

	for (const auto& string : strings)
		file << string << std::endl;
}

void MealyMachine::Minimize()
{
	MachineMinimizer::RemoveUnreachableStates(m_states, m_inputSignals, m_initialStateName);
	LabelStatesByFirstEquivalenñåClass();
	MachineMinimizer::LabelEquivalentStates(m_states, m_inputSignals);
	RebuildMinimizedMachine();
}

void MealyMachine::LabelStatesByFirstEquivalenñåClass()
{
	Logger::Log(std::cout, "Labeling states by first equivalence class...");
	for (auto& [stateName, state] : m_states)
	{
		std::string allOutputSignals;
		for (const auto& inputSignal : m_inputSignals)
			allOutputSignals += state.GetTransition(inputSignal).GetOutputSignal();
		
		state.SetLabel(std::hash<std::string>()(allOutputSignals));
		Logger::Log(std::cout, "Labeling state with hash... '" + stateName + "' -->>> " + state.GetLabel().str());
	}
}

void MealyMachine::RebuildMinimizedMachine()
{
	Logger::Log(std::cout, "Rebuilding minimized machine...");

	auto stateNamesToMinStateNames = CommonMachineAlgorithm::MapStateNamesToMinStateNames(m_states);

	std::unordered_map<std::string, MealyState> minimizedStates;
	for (auto& [stateName, state] : m_states)
	{
		auto respectiveMinStateName = stateNamesToMinStateNames[state.GetName()];
		if (minimizedStates.find(respectiveMinStateName) == minimizedStates.end())
		{
			MealyState newState(respectiveMinStateName);
			for (const auto& inputSignal : m_inputSignals)
			{
				auto oldTransition = state.GetTransition(inputSignal);
				newState.AddTransition(inputSignal, { stateNamesToMinStateNames[oldTransition.GetNextStateName()], oldTransition.GetOutputSignal() });
			}
			minimizedStates[respectiveMinStateName] = newState;
		}
	}

	CommonMachineAlgorithm::ThreadStates(minimizedStates, m_inputSignals);

	std::swap(m_states, minimizedStates);
	Logger::Log(std::cout, "Minimized machine have been successfully built.");
}

MealyTransition MealyMachine::ParseMealyTransition(const std::string& str)
{
	size_t delimPos = str.find('/');

	return { str.substr(0, delimPos), str.substr(delimPos + 1) };
}
