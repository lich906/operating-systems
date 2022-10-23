#ifndef MEALY_STATE_H
#define MEALY_STATE_H

#include "common.h"
#include "MealyTransition.h"
#include "AbstractState.h"

class MealyState : public AbstractState
{
public:
	MealyState() = default;

	MealyState(const std::string& name);

	void AddTransition(const std::string& inputSignal, const MealyTransition& transition);

	MealyTransition& GetTransition(const std::string& inputSignal);

	const MealyTransition& GetTransition(const std::string& inputSignal) const;
private:
	/*
	Key is an input signal name
	*/
	std::unordered_map<std::string, MealyTransition> m_transitions{};
};

#endif // !MEALY_STATE_H
