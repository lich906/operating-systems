#include "catch.hpp"
#include <sstream>

#include "MachineDeterminer.h"
#include "GrammarReader.h"
#include "fsm/io.h"

void ProccessLeft(std::istream& input, std::ostream& output)
{
	GrammarReader reader(input);
	auto machine = reader.ReadLeftGrammar();
	fsm::WriteCsv(output, MachineDeterminer::Determine(machine));
}

void ProccessRight(std::istream& input, std::ostream& output)
{
	GrammarReader reader(input);
	auto machine = reader.ReadRightGrammar();
	fsm::WriteCsv(output, MachineDeterminer::Determine(machine));
}

TEST_CASE("left side grammar")
{
	Logger::Quiet(true);

	std::istringstream in(R"(S -> S0 | B0
B -> B1 | C1
C -> C1 | 2
)");

	std::ostringstream out;
	ProccessLeft(in, out);

	REQUIRE(out.str() == R"(;;;;F
;S0;S1;S2;S3
0;-;-;S3;S3
1;-;S2;S2;-
2;S1;-;-;-
)");
}

TEST_CASE("right side grammar")
{
	Logger::Quiet(true);

	std::istringstream in(R"(H -> 1C | 0S | 0 | 1
S -> 0S | 0
C -> 1C | 0Z | 1 | 0
Z -> 0S | 1A | 0
A -> 0B | 1C | 1
B -> 1A
)");

	std::ostringstream out;
	ProccessRight(in, out);

	REQUIRE(out.str() == R"(;;F;F;F;;
;S0;S1;S2;S3;S4;S5
0;S2;S3;S2;S2;S5;-
1;S1;S1;-;S4;S1;S4
)");
}
