#include "Machine.h"

std::unique_ptr<State>& Machine::AddState(std::unique_ptr<State>&& state)
{
	auto stateName = state->GetName();
	if (!HasState(stateName))
	{
		return m_states[stateName] = std::move(state);
	}
	else
	{
		return m_states[stateName];
	}
}

std::unique_ptr<State>& Machine::GetState(const std::string& stateName)
{
	return m_states[stateName];
}

bool Machine::HasState(const std::string& stateName) const
{
	return m_states.find(stateName) != m_states.end() && m_states.at(stateName) != nullptr;
}

void Machine::SetInitialStateName(const std::string& name)
{
	m_initialStateName = name;
}
