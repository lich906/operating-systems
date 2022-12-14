#include "State.h"

using namespace fsm;

State::State(const std::string name, bool isFinal)
	: m_name(name)
	, m_final(isFinal)
{
}

void State::AddTransition(const std::string& signal, State* transition)
{
	m_transitions[signal].insert(transition);
}

std::set<State*> State::Transition(const std::string& signal)
{
	std::set<State*> result;

	for (auto& statePart : GetClosure())
	{
		for (auto& transition : statePart->m_transitions[signal])
		{
			auto closedTransition = transition->GetClosure();
			result.insert(closedTransition.begin(), closedTransition.end());
		}
	}

	return result;
}

std::string State::GetName() const
{
	return m_name;
}

bool State::IsFinal() const
{
	return m_final;
}

std::set<State*> State::GetClosure()
{
	std::set<State*> result;
	result.insert(this);
	GetClosureImpl(result);
	return result;
}

void State::GetClosureImpl(std::set<State*>& result)
{
	for (auto& closedState : m_transitions[constants::EmptySignal])
	{
		if (!result.contains(closedState))
		{
			result.insert(closedState);
			closedState->GetClosureImpl(result);
		}
	}
}

std::ostream& fsm::operator<<(std::ostream& out, const std::set<State*>& states)
{
	if (!states.empty())
	{
		out << (*states.begin())->GetName();
		for (auto it = std::next(states.begin()); it != states.end(); ++it)
		{
			out << constants::StatesSeparator << (*it)->GetName();
		}
	}
	else
	{
		out << constants::NoTransitionsPlaceholder;
	}
	return out;
}
