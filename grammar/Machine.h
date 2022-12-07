#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <stdexcept>

#include "State.h"

class Machine
{
public:
	std::unique_ptr<State>& AddState(std::unique_ptr<State>&& state);

	std::unique_ptr<State>& GetState(const std::string& stateName);

	std::unique_ptr<State>& GetInitialState();

	bool HasState(const std::string& stateName) const;

	void SetInitialStateName(const std::string& name);

	void AddSignal(const std::string& signal);

	std::set<std::string> GetAvailableSignals() const;

	void PrintAsCsv(std::ostream& output) const;

private:
	std::string m_initialStateName;
	std::unordered_map<std::string, std::unique_ptr<State>> m_states;
	std::set<std::string> m_signals;
};
