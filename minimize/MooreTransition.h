#ifndef MOORE_TRANSITION_H
#define MOORE_TRANSITION_H

#include "common.h"
#include "AbstractTransition.hpp"

class MooreTransition : public AbstractTransition<class MooreState>
{
public:
	MooreTransition() = default;

	MooreTransition(const std::string& nextStateName);

private:
	std::string m_nextStateName{};
};

#endif // !MOORE_TRANSITION_H
