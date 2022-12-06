#include "State.h"

State::State(const std::string name, bool isFinal)
	: m_name(name)
	, m_final(isFinal)
{
}

void State::AddTransition(const std::string& signalName, State* transition)
{
	m_transitions[signalName].insert(transition);
}

std::string State::GetName() const
{
	return m_name;
}

bool State::IsFinal() const
{
	return m_final;
}
