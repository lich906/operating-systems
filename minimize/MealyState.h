#ifndef MEALY_STATE_H
#define MEALY_STATE_H

#include "common.h"
#include "MealyTransition.h"
#include "AbstractState.hpp"

class MealyState : public AbstractState<MealyTransition>
{
public:
	MealyState() = default;

	MealyState(const std::string& name);

	void AddTransition(const std::string& inputSignal, const MealyTransition& transition);

	MealyTransition& GetTransition(const std::string& inputSignal);

	const MealyTransition& GetTransition(const std::string& inputSignal) const;
};

#endif // !MEALY_STATE_H
