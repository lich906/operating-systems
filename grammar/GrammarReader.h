#pragma once

#include <fstream>
#include <string_view>
#include <algorithm>

#include "Machine.h"

const std::string InitialStateName = "H";
const std::string FinalStateName = "F";
const auto VariantsSeparator = '|';

class GrammarReader
{
public:
	explicit GrammarReader(std::istream& input);

	Machine ReadLeftGrammar();

	Machine ReadRightGrammar();

private:
	std::istream& m_input;
};
