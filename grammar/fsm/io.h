#pragma once

#include <iostream>

#include "Machine.h"

namespace fsm
{

namespace constants
{
const std::string FinalStateMark = "F";
const char CsvSeparator = ';';
}

void WriteCsv(std::ostream& output, const Machine& machine);

}
