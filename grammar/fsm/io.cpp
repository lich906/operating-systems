#include "io.h"

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
