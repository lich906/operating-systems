#include "MachineCsvReader.h"

MachineCsvReader::MachineCsvReader(std::istream& input)
	: m_input(input)
{
}

fsm::Machine MachineCsvReader::Read()
{
	return fsm::Machine();
}
