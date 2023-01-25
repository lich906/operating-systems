#include "io.h"
#include "../util/string/string.hpp"

void fsm::WriteCsv(std::ostream& output, const Machine& machine)
{
	for (auto& [name, state] : machine.m_states)
	{
		output << constants::CsvSeparator << (state->IsFinal() ? constants::FinalStateMark : "");
	}
	output << std::endl;
	for (auto& [name, state] : machine.m_states)
	{
		output << constants::CsvSeparator << name;
	}
	output << std::endl;
	for (auto& signal : machine.m_signals)
	{
		output << signal;
		for (auto& [name, state] : machine.m_states)
		{
			output << constants::CsvSeparator << state->Transition(signal);
		}
		output << std::endl;
	}
}

fsm::Machine fsm::ReadCsv(std::istream& input)
{
	Machine machine;

	std::string outputSignalsLine;
	std::getline(input, outputSignalsLine);
	const auto outputSignals = util::string::Split(outputSignalsLine, constants::CsvSeparator);
	std::vector<bool> isFinal;
	for (size_t index = 1; index < outputSignals.size(); ++index)
		isFinal.push_back(outputSignals[index] == constants::FinalStateMark);

	std::string stateNamesLine;
	std::getline(input, stateNamesLine);
	const auto stateNames = util::string::Split(stateNamesLine, constants::CsvSeparator);
	machine.SetInitialStateName(stateNames[1]);
	std::vector<std::unique_ptr<State>> states;
	for (size_t index = 1; index < stateNames.size(); ++index)
		states.push_back(std::make_unique<State>(stateNames[index], isFinal[index - 1]));

	for (std::string transitionsLine; std::getline(input, transitionsLine);)
	{
		const auto transitions = util::string::Split(transitionsLine, constants::CsvSeparator);
		const auto signal = transitions[0];

		for (size_t index = 1; index < transitions.size(); ++index)
		{
			if (transitions[index] == constants::NoTransitionsPlaceholder || transitions[index].empty())
			{
				continue;
			}

			auto& srcState = states[index - 1];
			const auto dstStateNames = util::string::Split(transitions[index], constants::StatesSeparator);
			for (auto& dstStateName : dstStateNames)
			{
				auto dstState = std::find_if(states.begin(), states.end(), [&](std::unique_ptr<State>& s) {
					return s->GetName() == dstStateName;
				});
				srcState->AddTransition(signal, dstState->get());
			}

		}

		machine.AddSignal(signal);
	}

	for (auto& state : states)
		machine.AddState(std::move(state));

	return machine;
}
