#include "MealyMachineTable.h"

void MealyMachineTable::ReadFromCsvFile(const std::string& fileName, const char sep)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		throw std::runtime_error("File " + fileName + " not found.");
	}

	std::vector<std::istringstream> fileStrings;

	for (std::string line; std::getline(file, line); )
	{
		fileStrings.push_back(std::istringstream(line));
	}

	while (!fileStrings[0].eof())
	{
		std::vector<std::string> column;
		std::string colName;

		for (size_t i = 0; i < fileStrings.size(); i++)
		{
			std::string item;
			std::getline(fileStrings[i], item, sep);

			if (i == 0)
				colName = item;
			else
				column.push_back(item);
		}

		if (colName.empty() || colName == " ")
		{
			m_inputSignalIds = column;
		}
		else
		{
			std::map<std::string, MealyTransition> transitions;

			size_t i = 0;
			for (const auto& transitionStr : column)
			{
				MealyTransition transition = ParseMealyTransition(transitionStr);
				transitions[m_inputSignalIds[i]] = transition;
				i++;
			}

			m_mealyTable[colName] = transitions;
		}
	}
}

// MooreMachineTable MealyMachineTable::ConvertToMoore(const char stateSymbol) const
// {
// 	MooreMachineTable mooreTable;

// 	std::map<MealyTransition, std::string> mealyTransToMooreStates;

// 	std::map<std::string, std::string> mooreStatesToMealyStates;

// 	int count = 0;
// 	for (const auto& stateTransitions : m_mealyTable)
// 	{
// 		for(auto& transition : stateTransitions.second)
// 		{
// 			if (mealyTransToMooreStates.find(transition.second) == mealyTransToMooreStates.end())
// 			{
// 				std::string stateId = stateSymbol + std::to_string(count);

// 				mealyTransToMooreStates[transition.second] = stateId;
// 				mooreStatesToMealyStates[stateId] = transition.second.first;
// 				mooreTable.m_states[stateId] = transition.second.second;

// 				count++;
// 			}
// 		}
// 	}

// 	for (auto& mooreState : mooreTable.m_states)
// 	{
// 		auto mealyState = mooreStatesToMealyStates[mooreState.first];

// 		std::map<std::string, std::string> mooreTransitions;

// 		for (auto& mealyTransitions : m_mealyTable.at(mealyState))
// 		{
// 			mooreTransitions[mealyTransitions.first] = mealyTransToMooreStates[mealyTransitions.second];
// 		}

// 		mooreTable.m_mooreTable[mooreState.first] = mooreTransitions;
// 	}

// 	mooreTable.m_inputSignalIds = m_inputSignalIds;

// 	return mooreTable;
// }

void MealyMachineTable::PrintToCsvFile(const std::string& fileName, const char sep) const
{
	std::ofstream file(fileName);

	if (!file.is_open())
	{
		throw std::runtime_error("File " + fileName + " not found.");
	}

	std::vector<std::string> strings;

	strings.push_back(std::string());

	for (auto& inputSignalId : m_inputSignalIds)
	{
		strings.push_back(inputSignalId);
	}

	for (auto& [stateName, transitions] : m_mealyTable)
	{
		strings[0].append(sep + stateName);

		size_t i = 1;
		for (auto& transition : transitions)
		{
			strings[i].append(sep + transition.second.first + '/' + transition.second.second);
			i++;
		}
	}

	for (const auto& string : strings)
		file << string << std::endl;
}

MealyMachineTable::MealyTransition MealyMachineTable::ParseMealyTransition(std::string str)
{
	size_t delimPos = str.find('/');

	return std::make_pair(str.substr(0, delimPos), str.substr(delimPos + 1));
}
