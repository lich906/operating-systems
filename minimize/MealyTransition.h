#ifndef MEALY_TRANSITION_H
#define MEALY_TRANSITION_H

#include "common.h"
#include "AbstractTransition.hpp"

class MealyTransition : public AbstractTransition<class MealyState>
{
public:
	MealyTransition() = default;

	MealyTransition(const std::string& nextStateName, const std::string& outputSignal);

	const std::string& GetOutputSignal() const;

private:
	std::string m_outputSignal{};
};

#endif // !MEALY_TRANSITION_H
