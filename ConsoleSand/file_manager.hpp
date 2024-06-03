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
		int16_t cols = 0;
		int16_t rows = 0;
		std::string description = "";
		Grid* gridPtr = nullptr;
	};

	static void inline skipToEndline(std::fstream& fs)
	{
		char cur = ' ';
		do
		{
			fs.get(cur);
		} while (cur != '\n');
	}

	static void parseGrid(Grid* gridPtr, uint16_t cols, uint16_t rows, std::fstream &fs)
	{
		if (!fs.is_open())
			return;

		fs.seekg(0, std::ios::beg);
		skipToEndline(fs);

		bool eofTriggered = false;
		
		Grid::Cell** cells = gridPtr->cells();

		if (cells == nullptr)
			return;

		for (uint8_t x = 0; x < cols; x++)
		{
			bool minusFlag = false;

			for (uint8_t y = 0; y < rows; y++)
			{
				if (minusFlag)
				{
					y--;
					minusFlag = false;
				}

				if (fs.eof())
					eofTriggered = true;

				char sign = ' ';

				if (!eofTriggered)
				{
					fs.get(sign);

					bool innerChanged = false;

					if (sign == '\n')
					{
						minusFlag = true;
						continue;
					}

					while ((sign == '\n' || fs.eof()) && (x != cols - 1))
					{
						cells[x][y] = Grid::Cell();
						y++;
						innerChanged = true;
					}

					if (innerChanged)
						break;
				}

				Materials::Id matId;
				
				matId = Materials::matIdBySign(sign);

				Grid::Cell cell(matId);

				cells[x][y] = cell;
			}
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

		int16_t cols = 0;
		int16_t rows = 0;

		fs.clear();
		fs.seekg(0, std::ios::beg);

		fs >> cols;
		fs >> rows;

		if ((cols < 1 || cols > 100) || (rows < 1 || rows > 50))
			return { false, 0, 0, "Grid bounds violation: width[1;100] (cols) and height[1;50] (rows)", nullptr };

		Grid* gridPtr = new Grid(cols, rows);

		parseGrid(gridPtr, cols, rows, fs);

		fs.close();

		return { true, cols, rows, "File parsed", gridPtr };
	}
}