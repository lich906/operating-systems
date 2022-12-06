#pragma once

#include <string>
#include <unordered_map>
#include <set>

class State
{
public:
	explicit State(const std::string name, bool isFinal = false);

	void AddTransition(const std::string& signalName, State* transition);

	std::string GetName() const;

	bool IsFinal() const;

private:
	std::string m_name;
	bool m_final;

	std::unordered_map<std::string, std::set<State*>> m_transitions;
};
