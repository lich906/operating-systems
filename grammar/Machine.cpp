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

std::unique_ptr<State>& Machine::GetInitialState()
{
	return m_states[m_initialStateName];
}

bool Machine::HasState(const std::string& stateName) const
{
	return m_states.contains(stateName) && m_states.at(stateName) != nullptr;
}

void Machine::SetInitialStateName(const std::string& name)
{
	m_initialStateName = name;
}

void Machine::AddSignal(const std::string& signal)
{
	if (signal != EmptySignal)
	{
		m_signals.insert(signal);
	}
}

std::set<std::string> Machine::GetAvailableSignals() const
{
	return m_signals;
}

void Machine::PrintAsCsv(std::ostream& output) const
{
	for (auto& [name, state] : m_states)
	{
		output << ";" << (state->IsFinal() ? 'F' : ' ');
	}
	output << std::endl;
	for (auto& [name, state] : m_states)
	{
		output << ";" << name;
	}
	output << std::endl;
	for (auto& signal : m_signals)
	{
		output << signal;
		for (auto& [name, state] : m_states)
		{
			output << ";" << state->Transition(signal);
		}
		output << std::endl;
	}
}
