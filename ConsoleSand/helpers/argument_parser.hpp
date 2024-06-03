#pragma once

#include <iostream>
#include <unordered_map>
#include <string>

namespace Args
{
	enum class Codes { Good, Limit };
	static const std::unordered_map<Codes, std::string> codeInfoMap =
	{
		{Codes::Good, "Arguments parsed"},
		{Codes::Limit, "Too much arguments"}
	};

	static const Codes check(const int& argc, const char* const argv[])
	{
		if (argc == 1)
			return Codes::Good;

		if (argc > 2)
			return Codes::Limit;

		return Codes::Good;
	}

	static const std::string codeInfo(const Codes& code)
	{
		return codeInfoMap.at(code);
	}

	static const std::string help()
	{
		return "There is 1 allowed argument - input text file name.\n\
Example usage: app.exe file.txt";
	}

	static const std::string fileName(const char* const argv[])
	{
		if (argv[1] == nullptr)
			return "";

		return argv[1];
	}
}