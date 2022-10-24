#include "MooreMachine.h"

void MooreMachine::ReadFromCsvFile(const std::string& fileName, const char sep)
{
	std::ifstream file(fileName);

	if (!file.is_open())
		throw std::runtime_error("File " + fileName + " not found.");

	Logger::Log(std::cout, "Reading moore machine from file '" + fileName + "'...");

	std::vector<std::istringstream> fileStrings;

	for (std::string line; std::getline(file, line);)
		fileStrings.emplace_back(std::move(std::istringstream(line)));

	bool firstIteration = true;
	while (!fileStrings[0].eof())
	{
		std::vector<std::string> column;
		std::string outputSignal, stateName;

		for (size_t i = 0; i < fileStrings.size(); i++)
		{
			std::string item;
			std::getline(fileStrings[i], item, sep);

			if (i == 0)
				outputSignal = item;
			else if (i == 1)
				stateName = item;
			else
				column.push_back(item);
		}

		if (outputSignal.empty() && stateName.empty())
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

			MooreState state(stateName, outputSignal);

			size_t i = 0;
			for (const auto& nextStateName : column)
			{
				MooreTransition transition(nextStateName);

				auto nextStateIt = m_states.find(transition.GetNextStateName());
				if (nextStateIt != m_states.end())
				{
					Logger::Log(std::cout, "Threading states... '" + stateName + "' ---" + m_inputSignals[i] + "--> '" + nextStateIt->second.GetName() + "'");
					transition.SetNextStatePtr(nextStateIt->second);
				}

				Logger::Log(std::cout, "Creating transition... '" + state.GetName() + "' ---" + m_inputSignals[i] + "--> '" + transition.GetNextStateName() + "'");
				state.AddTransition(m_inputSignals[i], transition);
				i++;
			}

			Logger::Log(std::cout, "State '" + state.GetName() + "' created");
			m_states[stateName] = std::move(state);
		}
	}

	CommonMachineAlgorithm::ThreadStates(m_states, m_inputSignals);
}

void MooreMachine::PrintToCsvFile(const std::string& fileName, const char sep) const
{
	std::ofstream file(fileName);

	if (!file.is_open())
		throw std::runtime_error("File " + fileName + " not found.");

	std::vector<std::string> strings({ {}, {} });

	for (auto& inputSignalId : m_inputSignals)
		strings.push_back(inputSignalId);

	for (auto& [stateName, state] : m_states)
	{
		strings[0].append(sep + state.GetOutputSignal());
		strings[1].append(sep + state.GetName());

		size_t i = 2;
		for (auto& inputSignal : m_inputSignals)
		{
			auto& tr = state.GetTransition(inputSignal);
			strings[i].append(sep + tr.GetNextStateName());
			i++;
		}
	}

	for (const auto& string : strings)
		file << string << std::endl;
}

void MooreMachine::Minimize()
{
	MachineMinimizer::RemoveUnreachableStates(m_states, m_inputSignals, m_initialStateName);
	LabelStatesByZeroEquivalenceClass();
	MachineMinimizer::LabelEquivalentStates(m_states, m_inputSignals);
	RebuildMinimizedMachine();
}

void MooreMachine::LabelStatesByZeroEquivalenceClass()
{
	Logger::Log(std::cout, "Labeling states by zero equivalence class...");
	for (auto& [stateName, state] : m_states)
	{
		state.SetLabel(std::hash<std::string>()(state.GetOutputSignal()));
		Logger::Log(std::cout, "Labeling state with hash... '" + stateName + "' --> " + state.GetLabel().str());
	}
}

void MooreMachine::RebuildMinimizedMachine()
{
	Logger::Log(std::cout, "Rebuilding minimized machine...");

	auto stateNamesToMinStateNames = CommonMachineAlgorithm::MapStateNamesToMinStateNames(m_states);

	std::unordered_map<std::string, MooreState> minimizedStates;
	for (auto& [stateName, state] : m_states)
	{
		auto respectiveMinStateName = stateNamesToMinStateNames[state.GetName()];
		if (minimizedStates.find(respectiveMinStateName) == minimizedStates.end())
		{
			MooreState newState(respectiveMinStateName, state.GetOutputSignal());
			for (const auto& inputSignal : m_inputSignals)
			{
				auto oldTransition = state.GetTransition(inputSignal);
				newState.AddTransition(inputSignal, stateNamesToMinStateNames[oldTransition.GetNextStateName()]);
			}
			minimizedStates[respectiveMinStateName] = newState;
		}
	}

	CommonMachineAlgorithm::ThreadStates(minimizedStates, m_inputSignals);

	std::swap(m_states, minimizedStates);
	Logger::Log(std::cout, "Minimized machine have been successfully built.");
}
