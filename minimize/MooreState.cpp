#include "MooreState.h"

MooreState::MooreState(const std::string& name, const std::string& outputSignal)
	: AbstractState(name)
	, m_outputSignal(outputSignal)
{
}

const std::string& MooreState::GetOutputSignal() const
{
	return m_outputSignal;
}
