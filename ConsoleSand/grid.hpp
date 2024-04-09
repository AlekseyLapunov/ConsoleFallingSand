#pragma once

#include <utility>
#include <stdint.h>
#include <string>

#include "common_utils.hpp"
#include "materials.hpp"

class Grid
{
public:
	Grid(const uint8_t height, const uint8_t width);
	~Grid();

	Grid(Grid& otherGrid) = delete;
	Grid& operator= (Grid& otherGrid) = delete;

	std::pair<uint8_t, uint8_t> size();

	struct Cell
	{
		uint8_t materialId = Air;
		Material material = materials.at(Air);
	};

	Cell** cells();

	void process();

	void spawnMaterial(uint8_t row, uint8_t col, uint8_t materialId);

private:
	const uint8_t m_height;
	const uint8_t m_width;
	Cell** m_grid;
};
