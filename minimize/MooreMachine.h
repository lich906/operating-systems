#ifndef MOORE_MACHINE_H
#define MOORE_MACHINE_H

#include "common.h"
#include "MooreState.h"
#include "MachineMinimizer.hpp"
#include "CommonMachineAlgorithm.hpp"

class MooreMachine
{
public:
	void ReadFromCsvFile(const std::string& fileName, const char sep = Constants::CSV_FILE_SEPARATOR);

	void PrintToCsvFile(const std::string& fileName, const char sep = Constants::CSV_FILE_SEPARATOR) const;

	void Minimize();

private:
	void LabelStatesByZeroEquivalenceClass();

	void RebuildMinimizedMachine();

	std::string m_initialStateName;

	std::unordered_map<std::string, MooreState> m_states;

	std::vector<std::string> m_inputSignals;
};

#endif // !MOORE_MACHINE_H
