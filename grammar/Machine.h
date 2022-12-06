#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <stdexcept>

#include "State.h"
#include "Transition.h"

class Machine
{
public:
	std::unique_ptr<State>& AddState(std::unique_ptr<State>&& state);

	std::unique_ptr<State>& GetState(const std::string& stateName);

	bool HasState(const std::string& stateName) const;

	void SetInitialStateName(const std::string& name);

private:
	std::string m_initialStateName;
	std::unordered_map<std::string, std::unique_ptr<State>> m_states;
};
