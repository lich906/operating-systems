#pragma once

#include <queue>

#include "Machine.h"
#include "Logger.hpp"

const std::string NewStateLetter = "S";

class MachineDeterminer
{
public:
	static Machine Determine(Machine& machine);

private:
	static std::unique_ptr<State>& CreateStateIfNotExists(const std::set<State*>& closedState, Machine& resultMachine);

	static std::unique_ptr<State> CreateNewState(const std::set<State*>& states);

	inline static size_t m_newStateIndex = 0;

	inline static std::unordered_map<std::set<State*>, std::string> m_mapClosuresToNewStates;
};
