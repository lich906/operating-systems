#pragma once

#include <queue>

#include "fsm\Machine.h"
#include "Logger.hpp"

const std::string NewStateLetter = "S";

class MachineDeterminer
{
public:
	static fsm::Machine Determine(fsm::Machine& machine);

private:
	static std::unique_ptr<fsm::State>& CreateStateIfNotExists(const std::set<fsm::State*>& closedState, fsm::Machine& resultMachine);

	static std::unique_ptr<fsm::State> CreateNewState(const std::set<fsm::State*>& states);

	inline static size_t m_newStateIndex = 0;

	inline static std::unordered_map<std::set<fsm::State*>, std::string> m_mapClosuresToNewStates;
};
