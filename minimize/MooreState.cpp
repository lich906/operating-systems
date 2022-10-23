#include "MooreState.h"

MooreState::MooreState(const std::string& name, const std::string& outputSignal)
	: AbstractState(name)
	, m_outputSignal(outputSignal)
{
}

const std::string& MooreState::GetOutputSignal() const
{
	return m_outputSignal;
}

void MooreState::AddTransition(const std::string& inputSignal, const MooreTransition& transition)
{
	m_transitions.insert({ inputSignal, transition });
}

MooreTransition& MooreState::GetTransition(const std::string& inputSignal)
{
	if (m_transitions.find(inputSignal) == m_transitions.end())
		throw std::out_of_range("No transition by signal '" + inputSignal + "' for state '" + m_name + "'");

	return m_transitions[inputSignal];
}

const MooreTransition& MooreState::GetTransition(const std::string& inputSignal) const
{
	if (m_transitions.find(inputSignal) == m_transitions.end())
		throw std::out_of_range("No transition by signal '" + inputSignal + "' for state '" + m_name + "'");

	return m_transitions.at(inputSignal);
}
