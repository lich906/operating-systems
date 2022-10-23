#include "AbstractState.h"

const std::string& AbstractState::GetName() const
{
	return m_name;
}

AbstractState::AbstractState(const std::string& name)
	: m_name(name)
{
}

void AbstractState::SetNextLabel(LabelType label)
{
	m_nextLabel = label;
}

LabelType AbstractState::GetNextLabel() const
{
	return m_nextLabel;
}

void AbstractState::SetLabel(LabelType label)
{
	m_label = label;
}

LabelType AbstractState::GetLabel() const
{
	return m_label;
}

bool AbstractState::LabelChanged() const
{
	return m_nextLabel != m_label;
}

void AbstractState::SwapLabels()
{
	Logger::Log(std::cout, m_name + " swapping hash {" + LabelToString(m_label) + "} ===> {" + LabelToString(m_nextLabel) + "}");
	std::swap(m_label, m_nextLabel);
}