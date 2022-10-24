#ifndef MEALY_MACHINE_H
#define MEALY_MACHINE_H

#include "common.h"
#include "MealyState.h"
#include "MachineMinimizer.hpp"
#include "CommonMachineAlgorithm.hpp"

class MealyMachine
{
public:
	void ReadFromCsvFile(const std::string& fileName, const char sep = Constants::CSV_FILE_SEPARATOR);

	void PrintToCsvFile(const std::string& fileName, const char sep = Constants::CSV_FILE_SEPARATOR) const;

	void Minimize();

private:
	void LabelStatesByFirstEquivalenñåClass();

	void RebuildMinimizedMachine();

	std::string m_initialStateName;

	std::unordered_map<std::string, MealyState> m_states;

	std::vector<std::string> m_inputSignals;

	static MealyTransition ParseMealyTransition(const std::string& str);
};

#endif // !MEALY_MACHINE_H
