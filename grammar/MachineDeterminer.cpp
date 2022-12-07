#include "MachineDeterminer.h"

Machine MachineDeterminer::Determine(Machine& machine)
{
	Machine resultMachine;
	std::queue<std::set<State*>> newStates;
	newStates.push(machine.GetInitialState()->GetClosedState());

	do
	{
		auto currentClosedState = newStates.front();

		auto& srcState = CreateStateIfNotExists(currentClosedState, resultMachine);

		for (auto& signal : machine.GetAvailableSignals())
		{
			std::set<State*> transitions;
			for (auto& statePart : currentClosedState)
			{
				auto trs = statePart->Transition(signal);
				transitions.insert(trs.begin(), trs.end());
			}
			if (!transitions.empty())
			{
				Logger::Log("Creating transition... " + srcState->GetName() + " --" + signal + "--> ");
				Logger::Log(transitions);
				Logger::Log('\n');

				Logger::Log("State '");
				Logger::Log(transitions);
				if (m_mapClosuresToNewStates.contains(transitions)
					&& resultMachine.HasState(m_mapClosuresToNewStates[transitions]))
				{
					Logger::Log("' already exists.\n");
					auto& existingState = resultMachine.GetState(m_mapClosuresToNewStates[transitions]);
					srcState->AddTransition(signal, existingState.get());
					Logger::Log("Transition created: " + srcState->GetName() + " --" + signal + "--> " + existingState->GetName() + '\n');
				}
				else
				{
					Logger::Log("' not found.\n");
					newStates.push(transitions);
					auto& newState = resultMachine.AddState(CreateNewState(transitions));
					m_mapClosuresToNewStates[transitions] = newState->GetName();
					srcState->AddTransition(signal, newState.get());
					Logger::Log("Transition created: " + srcState->GetName() + " --" + signal + "--> " + newState->GetName() + '\n');
				}
			}
		}

		newStates.pop();
	} while (!newStates.empty());

	for (auto& signal : machine.GetAvailableSignals())
		resultMachine.AddSignal(signal);

	return resultMachine;
}

std::unique_ptr<State> MachineDeterminer::CreateNewState(const std::set<State*>& states)
{
	bool isFinal = false;
	for (auto& state : states)
		if (state->IsFinal())
		{
			isFinal = true;
			break;
		}

	auto newState = std::make_unique<State>(NewStateLetter + std::to_string(m_newStateIndex++), isFinal);
	Logger::Log("New state created: '", 10);
	Logger::Log(states, 10);
	Logger::Log("' --> " + newState->GetName() + (isFinal ? " (Final)" : "") + '\n', 10);

	m_mapClosuresToNewStates[states] = newState->GetName();

	return newState;
}

std::unique_ptr<State>& MachineDeterminer::CreateStateIfNotExists(const std::set<State*>& closedState, Machine& resultMachine)
{
	if (m_mapClosuresToNewStates.contains(closedState)
		&& resultMachine.HasState(m_mapClosuresToNewStates[closedState]))
	{
		return resultMachine.GetState(m_mapClosuresToNewStates[closedState]);
	}
	else
	{
		return resultMachine.AddState(CreateNewState(closedState));
	}
}
