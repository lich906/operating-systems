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

	MealyMachineTable ConvertToMealy(const char stateSymbol = 's') const;

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
