#pragma once

#include <fstream>
#include <string>

namespace FileManager
{
	struct Output
	{
		bool ok = false;
		uint8_t rows = 0;
		uint8_t cols = 0;
		std::string description = "";
	};

	Output readFile(std::string fileName)
	{
		std::fstream fs(fileName, std::ios::in);

		fs.open(fileName);

		if (!fs.is_open())
			return { false, 0, 0, "Cannot open file " + fileName};

		uint8_t rows = 0;
		uint8_t cols = 0;

		fs.clear();
		fs.seekg(0, std::ios::beg);

		fs >> rows;
		fs >> cols;
		
		if ((rows < 1 || rows > 50) || (cols < 1 || cols > 100))
			return {false, 0, 0, "Grid bounds violation: rows[1;50] & cols[1;100]"};

		fs.close();

		return {true, rows, cols, "File parsed"};
	}
}