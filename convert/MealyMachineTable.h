#ifndef MEALY_MACHINE_TABLE_H
#define MEALY_MACHINE_TABLE_H

#include "pch.h"
#include "MooreMachineTable.h"

class MealyMachineTable
{
public:
	/*
	* first -- next state id
	* second -- output signal id
	*/
	using MealyTransition = std::pair<std::string, std::string>;

	friend class MooreMachineTable;

	void ReadFromCsvFile(const std::string& fileName, const char sep = ';');

	template<typename Moore>
	Moore ConvertToMoore(const char stateSymbol = 's') const
	{
		Moore mooreTable;

		std::map<MealyTransition, std::string> mealyTransToMooreStates;

		std::map<std::string, std::string> mooreStatesToMealyStates;

		int count = 0;
		for (const auto& stateTransitions : m_mealyTable)
		{
			for(auto& transition : stateTransitions.second)
			{
				if (mealyTransToMooreStates.find(transition.second) == mealyTransToMooreStates.end())
				{
					std::string stateId = stateSymbol + std::to_string(count);

					mealyTransToMooreStates[transition.second] = stateId;
					mooreStatesToMealyStates[stateId] = transition.second.first;
					mooreTable.m_states[stateId] = transition.second.second;

					count++;
				}
			}
		}

		for (auto& mooreState : mooreTable.m_states)
		{
			auto mealyState = mooreStatesToMealyStates[mooreState.first];

			std::map<std::string, std::string> mooreTransitions;

			for (auto& mealyTransitions : m_mealyTable.at(mealyState))
			{
				mooreTransitions[mealyTransitions.first] = mealyTransToMooreStates[mealyTransitions.second];
			}

			mooreTable.m_mooreTable[mooreState.first] = mooreTransitions;
		}

		mooreTable.m_inputSignalIds = m_inputSignalIds;

		return mooreTable;
	}

	void PrintToCsvFile(const std::string& fileName, const char sep = ';') const;

private:
	/*
	* key -- state id
	* value -- map {
	*     key -- input signal id
	*     value -- pair {
	*         first -- next state
	*         second -- output signal
	*     }
	* }
	*/
	std::map<std::string, std::map<std::string, MealyTransition>> m_mealyTable;

	std::vector<std::string> m_inputSignalIds;

	static MealyTransition ParseMealyTransition(std::string str);
};

#endif
