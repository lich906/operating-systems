#ifndef LABELED_STATE_H
#define LABELED_STATE_H

#include "common.h"

class Label
{
public:
	Label() = default;

	Label(std::size_t value)
		: m_value(std::move(value)) {}

	operator std::size_t&()
	{
		return m_value;
	}

	operator const std::size_t&() const
	{
		return m_value;
	}

	std::string str() const
	{
		std::stringstream ss;
		ss << std::hex << m_value;
		return "{" + ss.str().substr(0, 8) + "}";
	}

private:
	std::size_t m_value{};
};

template <>
struct std::hash<Label>
{
	std::size_t operator()(const Label& l) const noexcept
	{
		return std::hash<std::size_t>()(l);
	}
};

namespace StateLabel
{
const Label Unreachable = -1;
const Label Reachable = 0;
}; // namespace StateLabel

#endif // !LABELED_STATE_H
