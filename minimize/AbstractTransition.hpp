#ifndef ABSTRACT_TRANSITION_H
#define ABSTRACT_TRANSITION_H

#include "common.h"

template <typename StateT>
class AbstractTransition
{
public:
	const std::string& GetNextStateName() const
	{
		return m_nextStateName;
	}

	void SetNextStatePtr(StateT* ptr)
	{
		m_nextStatePtr = ptr;
	}

	void SetNextStatePtr(StateT& ptr)
	{
		m_nextStatePtr = std::addressof(ptr);
	}

	StateT* operator->()
	{
		return m_nextStatePtr;
	}

	const StateT* operator->() const
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
	StateT* m_nextStatePtr = nullptr;
};

#endif // !ABSTRACT_TRANSITION_H
