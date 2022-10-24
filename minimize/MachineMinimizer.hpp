#ifndef MACHINE_MINIMIZER_H
#define MACHINE_MINIMIZER_H

#include "common.h"

class MachineMinimizer
{
public:
	template <typename T>
	static void RemoveUnreachableStates(std::unordered_map<std::string, T>& states, const std::vector<std::string>& inputSignals, const std::string& initialStateName)
	{
		Logger::Log(std::cout, "Labeling reachable states...");
		std::queue<T*> queue;

		Logger::Log(std::cout, "Pushing intial state '" + initialStateName + "' into queue...");
		queue.push(&(states.find(initialStateName)->second));

		do
		{
			for (const auto& inputSignal : inputSignals)
			{
				auto tr = queue.front()->GetTransition(inputSignal);

				if (tr->GetLabel() == StateLabel::Unreachable)
				{
					queue.push(&(states.find(tr->GetName())->second));
					Logger::Log(std::cout, "State '" + tr->GetName() + "' pushed into queue.");
				}
			}

			Logger::Log(std::cout, "State '" + queue.front()->GetName() + "' labeled as reachable.");
			queue.front()->SetLabel(StateLabel::Reachable);
			queue.pop();
		} while (!queue.empty());

		Logger::Log(std::cout, "Removing unreachable states...");
		size_t count = 0;
		for (auto it = states.begin(); it != states.end();)
		{
			if (it->second.GetLabel() == StateLabel::Unreachable)
			{
				Logger::Log(std::cout, "State '" + it->second.GetName() + "' is unreachable. Removing...");
				it = states.erase(it);
				++count;
			}
			else
			{
				++it;
			}
		}
		Logger::Log(std::cout, "Number of removed unreachable states: " + std::to_string(count));
	}

	/*
	Before this step of minimization states must be labeled
	- for Mealy -- by first equivalence class
	- for Moore -- by zero equivalence class
	*/
	template <typename T>
	static void LabelEquivalentStates(std::unordered_map<std::string, T>& states, const std::vector<std::string>& inputSignals)
	{
		bool distributionChanged = false;
		do
		{
			for (auto& [stateName, state] : states)
			{
				std::vector<Label> nextStatesHashes;
				for (const auto& inputSignal : inputSignals)
					nextStatesHashes.push_back(state.GetTransition(inputSignal)->GetLabel());

				state.SetNextLabel(GetHash(state.GetLabel(), nextStatesHashes));
			}

			distributionChanged = SwapLabels(states);
		} while (distributionChanged);
	}

private:
	/*
	'thisStateLabel' is included into hash to avoid inclusion states in the same equivalence class
	if they were in different classes in previous distribution
	*/
	static Label GetHash(Label thisStateLabel, const std::vector<Label>& nextStatesHashes)
	{
		std::size_t seed = nextStatesHashes.size();
		for (auto& i : nextStatesHashes)
			seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
		seed ^= thisStateLabel + 0x9e3779b9 + (seed << 6) + (seed >> 2);

		return seed;
	}
	
	template <typename T>
	static bool SwapLabels(std::unordered_map<std::string, T>& states)
	{
		std::unordered_map<Label, Label> hashMap;
		bool distributionChanged = false;

		for (auto& [stateName, state] : states)
		{
			auto hash = hashMap.find(state.GetLabel());
			if (hash == hashMap.end())
			{
				hashMap[state.GetLabel()] = state.GetNextLabel();
			}
			else if (hash->second != state.GetNextLabel())
			{
				Logger::Log(std::cout, "Distribution changed. Hash " + hash->first.str() + " implies to " + hash->second.str() + " and " + state.GetNextLabel().str());
				distributionChanged = true;
				break;
			}
		}

		if (!distributionChanged)
			Logger::Log(std::cout, "Distribution not changed. Equivalence classes has been determined.");

		for (auto& [stateName, state] : states)
			state.SwapLabels();

		return distributionChanged;
	}
};

#endif // !MACHINE_MINIMIZER_H
