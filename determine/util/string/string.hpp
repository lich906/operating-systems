#pragma once

#include <vector>
#include <string>
#include <algorithm>

namespace util::string
{

static inline void RemoveWhitespaces(std::string& str)
{
	str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char c) {
		return std::isspace(c);
	}), str.end());
}

static inline std::vector<std::string> Split(const std::string str, char sep)
{
	std::vector<std::string> res;
	std::string cur;

	std::for_each(str.begin(), str.end(), [&](char ch) {
		if (ch == sep)
		{
			res.push_back(cur);
			cur.clear();
		}
		else
		{
			cur.push_back(ch);
		}
	});

	res.push_back(cur);

	return res;
}

}