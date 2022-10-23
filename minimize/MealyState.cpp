#include "MealyState.h"

MealyState::MealyState(const std::string& name)
	: AbstractState(name)
{
}

void MealyState::AddTransition(const std::string& inputSignal, const MealyTransition& transition)
{
	m_transitions.insert({ inputSignal, transition });
}

MealyTransition& MealyState::GetTransition(const std::string& inputSignal)
{
	if (m_transitions.find(inputSignal) == m_transitions.end())
		throw std::out_of_range("No transition by signal '" + inputSignal + "' for state '" + m_name + "'");

	return m_transitions[inputSignal];
}

const MealyTransition& MealyState::GetTransition(const std::string& inputSignal) const
{
	if (m_transitions.find(inputSignal) == m_transitions.end())
		throw std::out_of_range("No transition by signal '" + inputSignal + "' for state '" + m_name + "'");

	return m_transitions.at(inputSignal);
}
