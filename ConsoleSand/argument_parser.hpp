#pragma once

#include <unordered_map>
#include <string>

namespace Args
{
	enum class Codes { Good, Limit, Unknown, GeneralError };

	static const std::unordered_map<Codes, std::string> codeInfoMap;

	static const Codes check(const int& argc, const char* const argv[])
	{
		if (argc > 1)
			return Codes::Limit;
	}

	static const std::string codeInfo(const Codes& code)
	{
		return codeInfoMap.at(code);
	}
}