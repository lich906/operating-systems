#include "catch.hpp"
#include <sstream>

#include "fsm/io.h"
#include "MachineDeterminer.h"

void ProccessLeft(std::istream& input, std::ostream& output)
{
	auto machine = fsm::ReadCsv(input);
	fsm::WriteCsv(output, MachineDeterminer::Determine(machine));
}

TEST_CASE("with 'e' signal and multi transitions")
{
	Logger::Quiet(true);

	std::istringstream in(R"(;;;;;F;;;;
;S1;S2;S3;S4;S5;S6;S7;S8;S9
a;;S3;;;;S7;;S9;
b;;;S4;;;;S5;;
c;;;;S5;;;;;S5
e;S2,S6,S8;;;;S1;;;;
)");

	std::ostringstream out;
	ProccessLeft(in, out);

	REQUIRE(out.str() == R"(;;;F;F
;S0;S1;S2;S3
a;S1;-;S1;S1
b;-;S2;-;-
c;-;S3;S3;-
)");
}
