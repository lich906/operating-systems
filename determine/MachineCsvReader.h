#pragma once

#include <iostream>

#include "fsm/Machine.h"

class MachineCsvReader
{
public:
	explicit MachineCsvReader(std::istream& input);

	fsm::Machine Read();

private:
	std::istream& m_input;
};
