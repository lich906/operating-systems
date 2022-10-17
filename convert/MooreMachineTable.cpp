#include "MooreMachineTable.h"
#include "MealyMachineTable.h"

void MooreMachineTable::ReadFromCsvFile(const std::string& fileName, const char sep)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		throw std::runtime_error("File " + fileName + " not found.");
	}

	std::vector<std::istringstream> fileStrings;

	for (std::string line; std::getline(file, line);)
	{
		fileStrings.push_back(std::istringstream(line));
	}

	while (!fileStrings[0].eof())
	{
		std::vector<std::string> column;
		std::string stateOutputSignal, stateName;

		for (size_t i = 0; i < fileStrings.size(); i++)
		{
			std::string item;
			std::getline(fileStrings[i], item, sep);

			if (i == 0)
				stateOutputSignal = item;
			else if (i == 1)
				stateName = item;
			else
				column.push_back(item);
		}

		if (stateOutputSignal.empty() && stateName.empty())
		{
			m_inputSignalIds = column;
		}
		else
		{
			std::map<std::string, std::string> transitions;

			size_t i = 0;
			for (const auto& transitionStr : column)
			{
				transitions[m_inputSignalIds[i]] = transitionStr;
				i++;
			}

			m_mooreTable[stateName] = transitions;

			m_states[stateName] = stateOutputSignal;
		}
	}
}

void MooreMachineTable::PrintToCsvFile(const std::string& fileName, const char sep) const
{
	std::ofstream file(fileName);

	if (!file.is_open())
	{
		throw std::runtime_error("File " + fileName + " not found.");
	}

	std::vector<std::string> strings;

	strings.push_back(std::string());
	strings.push_back(std::string());

	for (auto& inputSignalId : m_inputSignalIds)
	{
		strings.push_back(inputSignalId);
	}

	for (auto& state : m_states)
	{
		strings[0].append(sep + state.second);
		strings[1].append(sep + state.first);

		size_t i = 2;
		for (auto& transitions : m_mooreTable.at(state.first))
		{
			strings[i].append(sep + transitions.second);
			i++;
		}
	}

	for (const auto& string : strings)
		file << string << std::endl;
}

// MealyMachineTable MooreMachineTable::ConvertToMealy(const char stateSymbol) const
// {
// 	MealyMachineTable mealyTable;

// 	std::map<std::string, std::string> mooreStateToMealyState;
// 	size_t count = 0;
// 	for (auto& state : m_states)
// 	{
// 		mooreStateToMealyState[state.first] = stateSymbol + std::to_string(count);
// 		count++;
// 	}

// 	for (auto& state : m_mooreTable)
// 	{
// 		std::string stateId = mooreStateToMealyState.at(state.first);

// 		std::map<std::string, MealyMachineTable::MealyTransition> mealyTransitions;
// 		for (auto& mooreTransition : state.second)
// 		{
// 			mealyTransitions[mooreTransition.first] = std::make_pair(mooreStateToMealyState[mooreTransition.second], m_states.at(mooreTransition.second));
// 		}

// 		mealyTable.m_mealyTable[stateId] = mealyTransitions;
// 	}

// 	mealyTable.m_inputSignalIds = m_inputSignalIds;

// 	return mealyTable;
// }

