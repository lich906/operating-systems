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

	MooreMachineTable ConvertToMoore(const char stateSymbol = 's') const;

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
