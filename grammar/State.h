#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <set>

const std::string EmptySignal = "e";
const std::string NoTransitionsPlaceholder = "-";

class State
{
public:
	explicit State(const std::string name, bool isFinal = false);

	void AddTransition(const std::string& signal, State* transition);

	std::set<State*> Transition(const std::string& signal);

	std::string GetName() const;

	bool IsFinal() const;

	std::set<State*> GetClosedState();

private:
	void GetClosedStateImpl(std::set<State*>& result);

	std::string m_name;
	bool m_final;

	std::unordered_map<std::string, std::set<State*>> m_transitions;
};

template <>
struct std::hash<std::set<State*>>
{
	std::size_t operator()(const std::set<State*>& set) const noexcept
	{
		std::size_t res = std::hash<nullptr_t>{}(nullptr);
		for (auto& elem : set)
		{
			res ^= (std::hash<State*>{}(elem) << 1);
		}
		return res;
	}
};

std::ostream& operator<<(std::ostream& out, const std::set<State*>& states);
