#ifndef ABSTRACT_STATE_H
#define ABSTRACT_STATE_H

#include "common.h"
#include "Label.h"

class AbstractState
{
public:
	const std::string& GetName() const;

	void SetNextLabel(LabelType label);

	LabelType GetNextLabel() const;

	void SetLabel(LabelType label);

	LabelType GetLabel() const;

	bool LabelChanged() const;

	void SwapLabels();

protected:
	AbstractState() = default;

	AbstractState(const std::string& name);

	std::string m_name{};

	LabelType m_label = StateLabel::Unreachable;
	LabelType m_nextLabel = StateLabel::Unreachable;
};

#endif // !ABSTRACT_STATE_H
