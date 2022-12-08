#include "io.h"

void fsm::WriteCsv(std::ostream& output, const Machine& machine)
{
	for (auto& [name, state] : machine.m_states)
	{
		output << ";" << (state->IsFinal() ? 'F' : ' ');
	}
	output << std::endl;
	for (auto& [name, state] : machine.m_states)
	{
		output << ";" << name;
	}
	output << std::endl;
	for (auto& signal : machine.m_signals)
	{
		output << signal;
		for (auto& [name, state] : machine.m_states)
		{
			output << ";" << state->Transition(signal);
		}
		output << std::endl;
	}
}
