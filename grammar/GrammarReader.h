#pragma once

#include <fstream>
#include <string_view>
#include <algorithm>

#include "fsm\Machine.h"

const std::string InitialStateName = "H";
const std::string FinalStateName = "F";
const auto VariantsSeparator = '|';

class GrammarReader
{
public:
	explicit GrammarReader(std::istream& input);

	fsm::Machine ReadLeftGrammar();

	fsm::Machine ReadRightGrammar();

private:
	std::istream& m_input;
};
