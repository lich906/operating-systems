#ifndef ABSTRACT_STATE_H
#define ABSTRACT_STATE_H

#include "common.h"
#include "Label.h"

template <typename TransitionT>
class AbstractState
{
public:
	const std::string& GetName() const
	{
		return m_name;
	}

	void AddTransition(const std::string& inputSignal, const TransitionT& transition)
	{
		m_transitions.insert({ inputSignal, transition });
	}

	TransitionT& GetTransition(const std::string& inputSignal)
	{
		if (m_transitions.find(inputSignal) == m_transitions.end())
			throw std::out_of_range("Transition by signal '" + inputSignal + "' for state '" + m_name + "' not found");

		return m_transitions[inputSignal];
	}

	const TransitionT& GetTransition(const std::string& inputSignal) const
	{
		if (m_transitions.find(inputSignal) == m_transitions.end())
			throw std::out_of_range("Transition by signal '" + inputSignal + "' for state '" + m_name + "' not found");

		return m_transitions.at(inputSignal);
	}

	void SetNextLabel(Label label)
	{
		m_nextLabel = std::move(label);
	}

	Label GetNextLabel() const
	{
		return m_nextLabel;
	}

	void SetLabel(Label label)
	{
		m_label = std::move(label);
	}

	Label GetLabel() const
	{
		return m_label;
	}

	void SwapLabels()
	{
		Logger::Log(std::cout, "Rehashing... '" + m_name + "' " + m_label.str() + " >>> " + m_nextLabel.str());
		std::swap(m_label, m_nextLabel);
	}

protected:
	AbstractState() = default;

	AbstractState(const std::string& name)
		: m_name(name) {}

	std::string m_name{};

	Label m_label = StateLabel::Unreachable;
	Label m_nextLabel = StateLabel::Unreachable;

	/*
	Key is an input signal name
	*/
	std::unordered_map<std::string, TransitionT> m_transitions{};
};

#endif // !ABSTRACT_STATE_H
