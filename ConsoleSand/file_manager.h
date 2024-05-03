#pragma once

#include <fstream>
#include <string>

#include "grid.hpp"
#include "materials.hpp"

namespace FileManager
{
	struct Output
	{
		bool ok = false;
		int16_t rows = 0;
		int16_t cols = 0;
		std::string description = "";
		Grid::Cell** cells = nullptr;
	};

	static void inline skipToEndline(std::fstream& fs)
	{
		char cur = ' ';
		do
		{
			fs.get(cur);
		} while (cur != '\n');
	}

	static void parseGrid(Grid::Cell** cells, uint16_t rows, uint16_t cols, std::fstream &fs)
	{
		if (!fs.is_open())
			return;

		fs.seekg(0, std::ios::beg);
		
		for (uint8_t row = 0; row < rows; row++)
		{
			for (uint8_t col = 0; col < cols; col++)
			{
				if (fs.eof())
					return;

				char cur = ' ';

				fs.get(cur);

				if (cur == '\n')
					break;

				Materials::Id matId = Materials::matIdBySign(cur);

				Grid::Cell cell;
				cell.mId = matId;
				//cell.material = materials.at(matId);

				cells[row][col] = cell;
			}

			skipToEndline(fs);
		}
	}

	static Output readFile(std::string fileName)
	{
		if (fileName.empty())
			return {false, 0, 0, "Filename is empty", nullptr};

		std::fstream fs(fileName, std::ios::in);

		fs.open(fileName);

		if (!fs.is_open())
			return { false, 0, 0, "Cannot open file " + fileName, nullptr };

		int16_t rows = 0;
		int16_t cols = 0;

		fs.clear();
		fs.seekg(0, std::ios::beg);

		fs >> rows;
		fs >> cols;

		if ((rows < 1 || rows > 50) || (cols < 1 || cols > 100))
			return { false, 0, 0, "Grid bounds violation: rows[1;50] & cols[1;100]", nullptr };

		Grid::Cell** cells = Grid::allocate(rows, cols);

		parseGrid(cells, rows, cols, fs);

		fs.close();

		return { true, rows, cols, "File parsed", cells };
	}
}