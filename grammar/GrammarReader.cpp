#include "GrammarReader.h"
#include "util/string/string.hpp"

using namespace fsm;

GrammarReader::GrammarReader(std::istream& input)
	: m_input(input)
{
}

Machine GrammarReader::ReadLeftGrammar()
{
	Machine machine;

	size_t lineNum = 1;
	for (std::string line; std::getline(m_input, line); ++lineNum)
	{
		util::string::RemoveWhitespaces(line);
		std::string leftSideNonterminal(1, line[0]);
		auto rightSideVariants = std::string(line.begin() + 3, line.end());
		auto ruleVariants = util::string::Split(rightSideVariants, VariantsSeparator);

		auto& destState = machine.AddState(std::make_unique<State>(leftSideNonterminal, lineNum == 1));

		for (const auto& variant : ruleVariants)
		{
			switch (variant.size())
			{
			case 1:
			{
				if (auto& existingInitState = machine.GetState(InitialStateName))
				{
					existingInitState->AddTransition(variant, destState.get());
				}
				else
				{
					auto initialState = std::make_unique<State>(InitialStateName, false);
					initialState->AddTransition(variant, destState.get());
					machine.AddState(std::move(initialState));
					machine.SetInitialStateName(InitialStateName);
				}

				machine.AddSignal(variant);
			}
			break;
			case 2:
			{
				std::string stateName(1, variant[0]);
				std::string signalName(1, variant[1]);

				if (stateName == destState->GetName())
				{
					destState->AddTransition(signalName, destState.get());
				}
				else if (auto& existingState = machine.GetState(stateName))
				{
					existingState->AddTransition(signalName, destState.get());
				}
				else
				{
					auto newState = std::make_unique<State>(stateName, false);
					newState->AddTransition(signalName, destState.get());
					machine.AddState(std::move(newState));
				}

				machine.AddSignal(signalName);
			}
			break;
			default:
				throw std::runtime_error("Invalid grammar syntax: variant '" + variant + "' at line " + std::to_string(lineNum));
			}
		}
	}

	return machine;
}

Machine GrammarReader::ReadRightGrammar()
{
	Machine machine;

	bool finalStateCreated = false;
	size_t lineNum = 1;
	for (std::string line; std::getline(m_input, line); ++lineNum)
	{
		util::string::RemoveWhitespaces(line);
		std::string leftSideNonterminal(1, line[0]);
		auto rightSideVariants = std::string(line.begin() + 3, line.end());
		auto ruleVariants = util::string::Split(rightSideVariants, VariantsSeparator);

		auto& srcState = machine.AddState(std::make_unique<State>(leftSideNonterminal, false));

		if (lineNum == 1)
			machine.SetInitialStateName(srcState->GetName());

		for (const auto& variant : ruleVariants)
		{
			switch (variant.size())
			{
			case 1:
			{
				if (auto& existingFinalState = machine.GetState(FinalStateName))
				{
					srcState->AddTransition(variant, existingFinalState.get());
				}
				else
				{
					auto finalState = std::make_unique<State>(FinalStateName, true);
					srcState->AddTransition(variant, finalState.get());
					machine.AddState(std::move(finalState));
					finalStateCreated = true;
				}

				machine.AddSignal(variant);
			}
			break;
			case 2:
			{
				std::string signal(1, variant[0]);
				std::string stateName(1, variant[1]);

				if (stateName == srcState->GetName())
				{
					srcState->AddTransition(signal, srcState.get());
				}
				else if (auto& existingState = machine.GetState(stateName))
				{
					srcState->AddTransition(signal, existingState.get());
				}
				else
				{
					auto newState = std::make_unique<State>(stateName, false);
					srcState->AddTransition(signal, newState.get());
					machine.AddState(std::move(newState));
				}

				machine.AddSignal(signal);
			}
			break;
			default:
				throw std::runtime_error("Invalid grammar syntax: variant '" + variant + "' at line " + std::to_string(lineNum));
			}
		}
	}

	if (!finalStateCreated)
	{
		throw std::runtime_error("Invalid grammar rules: final state not recognized.");
	}

	return machine;
}
