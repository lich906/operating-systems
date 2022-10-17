#ifndef MOORE_MACHINE_TABLE_H
#define MOORE_MACHINE_TABLE_H

#include "pch.h"
#include "MealyMachineTable.h"

class MooreMachineTable
{
public:
	using MooreState = std::pair<std::string, std::string>;

	friend class MealyMachineTable;

	void ReadFromCsvFile(const std::string& fileName, const char sep = ';');

	void PrintToCsvFile(const std::string& fileName, const char sep = ';') const;

	template <typename Mealy>
	Mealy ConvertToMealy(const char stateSymbol = 's') const
	{
		Mealy mealyTable;

		std::map<std::string, std::string> mooreStateToMealyState;
		size_t count = 0;
		for (auto& state : m_states)
		{
			mooreStateToMealyState[state.first] = stateSymbol + std::to_string(count);
			count++;
		}

		for (auto& state : m_mooreTable)
		{
			std::string stateId = mooreStateToMealyState.at(state.first);

			std::map<std::string, typename Mealy::MealyTransition> mealyTransitions;
			for (auto& mooreTransition : state.second)
			{
				mealyTransitions[mooreTransition.first] = std::make_pair(mooreStateToMealyState[mooreTransition.second], m_states.at(mooreTransition.second));
			}

			mealyTable.m_mealyTable[stateId] = mealyTransitions;
		}

		mealyTable.m_inputSignalIds = m_inputSignalIds;

		return mealyTable;
	}

private:
	/*
	* key -- state id
	* value -- output signal id
	*/
	std::map<std::string, std::string> m_states;

	/*
	* key -- state id
	* value -- map {
	*     key -- input signal id
	*     value -- next state id
	* }
	*/
	std::map<std::string, std::map<std::string, std::string>> m_mooreTable;

	std::vector<std::string> m_inputSignalIds;
};

#endif // !MOORE_MACHINE_TABLE_H
