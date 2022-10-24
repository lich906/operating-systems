#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string_view>

namespace Constants
{
const std::string MINIMIZED_STATE_LETTER = "q";
constexpr char CSV_FILE_SEPARATOR = ';';
constexpr std::size_t ARGS_COUNT = 3;
constexpr std::string_view MEALY_MODE_STR = "mealy";
constexpr std::string_view MOORE_MODE_STR = "moore";
constexpr std::string_view HELP_MESSAGE = 
"Syntax: minimize.exe [options...] (mealy|moore) input_file output_file"
"\n"
"Options:";
}; // namespace Constants

#endif // !CONSTANTS_H
