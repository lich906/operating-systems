#ifndef COMMON_MACHINE_ALGORITHM_H
#define COMMON_MACHINE_ALGORITHM_H

#include "common.h"
#include "Label.h"

class CommonMachineAlgorithm
{
public:
	template <typename T>
	static void ThreadStates(std::unordered_map<std::string, T>& states, const std::vector<std::string>& inputSignals)
	{
		Logger::Log(std::cout, "Threading states...");
		for (auto& [stateName, state] : states)
		{
			for (const auto& inputSignal : inputSignals)
			{
				auto& tr = state.GetTransition(inputSignal);
				if (!tr.HaveNextStatePointer() && !tr.IsEmpty())
				{
					Logger::Log(std::cout, "Threading states... '" + state.GetName() + "' ---" + inputSignal + "--> '" + tr.GetNextStateName() + "'");
					tr.SetNextStatePtr(states.find(tr.GetNextStateName())->second);
				}
			}
		}
	}

	/*
	E.g.
	a0 -> q0
	a1 -> q0
	a2 -> q1
	a0 and a1 are equivalent states
	*/
	template <typename T>
	static std::unordered_map<std::string, std::string> MapStateNamesToMinStateNames(const std::unordered_map<std::string, T>& states)
	{
		auto hashToMinStateNames = MapLabelsToMinimizedNames(states);

		std::unordered_map<std::string, std::string> stateNamesToMinStateNames;
		for (auto& [stateName, state] : states)
		{
			auto it = stateNamesToMinStateNames.find(state.GetName());
			if (it == stateNamesToMinStateNames.end())
			{
				stateNamesToMinStateNames[state.GetName()] = hashToMinStateNames[state.GetLabel()];
				Logger::Log(std::cout, "Mapping state to minimized state... '" + state.GetName() + "' --> '" + stateNamesToMinStateNames.at(state.GetName()) + "'");
			}
		}

		return stateNamesToMinStateNames;
	}

private:
	template <typename T>
	static std::unordered_map<Label, std::string> MapLabelsToMinimizedNames(const std::unordered_map<std::string, T>& states)
	{
		std::unordered_map<Label, std::string> labelsToMinStateNames;
		size_t count = 0;
		for (auto& [stateName, state] : states)
		{
			auto label = state.GetLabel();
			auto it = labelsToMinStateNames.find(label);
			if (it == labelsToMinStateNames.end())
			{
				labelsToMinStateNames[label] = Constants::MINIMIZED_STATE_LETTER + std::to_string(count);
				++count;
				Logger::Log(std::cout, "Map hash to minimized state " + label.str() + " >>>-- '" + labelsToMinStateNames.at(label) + "'");
			}
		}

		return labelsToMinStateNames;
	}
};

#endif // !COMMON_MACHINE_ALGORITHM_H
