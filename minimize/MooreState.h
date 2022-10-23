#ifndef MOORE_STATE_H
#define MOORE_STATE_H

#include "common.h"
#include "MooreTransition.h"
#include "AbstractState.h"

class MooreState : public AbstractState
{
public:
	MooreState() = default;

	MooreState(const std::string& name, const std::string& outputSignal);

	const std::string& GetOutputSignal() const;

	void AddTransition(const std::string& inputSignal, const MooreTransition& transition);

	MooreTransition& GetTransition(const std::string& inputSignal);

	const MooreTransition& GetTransition(const std::string& inputSignal) const;

private:
	std::string m_outputSignal{};

	/*
	Key is an input signal name
	*/
	std::unordered_map<std::string, MooreTransition> m_transitions{};
};

#endif // !MOORE_STATE_H
