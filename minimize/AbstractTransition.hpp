#ifndef ABSTRACT_TRANSITION_H
#define ABSTRACT_TRANSITION_H

#include "common.h"

template <typename StatePtr>
class AbstractTransition
{
public:
	const std::string& GetNextStateName() const
	{
		return m_nextStateName;
	}

	void SetNextStatePtr(StatePtr* ptr)
	{
		m_nextStatePtr = ptr;
	}

	void SetNextStatePtr(StatePtr& ptr)
	{
		m_nextStatePtr = std::addressof(ptr);
	}

	StatePtr* operator->()
	{
		return m_nextStatePtr;
	}

	const StatePtr* operator->() const
	{
		return m_nextStatePtr;
	}

	bool HaveNextStatePointer() const
	{
		return m_nextStatePtr != nullptr;
	}

protected:
	AbstractTransition() = default;

	AbstractTransition(const std::string& nextStateName)
		: m_nextStateName(nextStateName){}

	std::string m_nextStateName{};
	StatePtr* m_nextStatePtr = nullptr;
};

#endif // !ABSTRACT_TRANSITION_H
