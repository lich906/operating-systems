#ifndef LABELED_STATE_H
#define LABELED_STATE_H

#include "common.h"

using LabelType = std::size_t;

namespace StateLabel
{
const LabelType Unreachable = -1;
const LabelType Reachable = 0;
}; // namespace StateLabel

inline std::string LabelToString(const LabelType& label)
{
	return std::to_string(label).substr(0, 4);
}

#endif // !LABELED_STATE_H
