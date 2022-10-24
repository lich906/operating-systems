#ifndef MOORE_STATE_H
#define MOORE_STATE_H

#include "common.h"
#include "MooreTransition.h"
#include "AbstractState.hpp"

class MooreState : public AbstractState<MooreTransition>
{
public:
	MooreState() = default;

	MooreState(const std::string& name, const std::string& outputSignal);

	const std::string& GetOutputSignal() const;

private:
	std::string m_outputSignal{};
};

#endif // !MOORE_STATE_H
