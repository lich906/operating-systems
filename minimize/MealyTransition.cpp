#include "MealyTransition.h"

MealyTransition::MealyTransition(const std::string& nextStateName, const std::string& outputSignal)
	: AbstractTransition(nextStateName)
	, m_outputSignal(outputSignal)
{
}

const std::string& MealyTransition::GetOutputSignal() const
{
	return m_outputSignal;
}
