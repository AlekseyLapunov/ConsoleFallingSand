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
		materialId	mId			= Air;
		Material	material	= materials.at(Air);
		bool		hasMoved	= false;
	};

	Cell** cells();

	void process();

	void spawnMaterial(uint8_t row, uint8_t col, materialId mId);

private:
	void clearMoveState();

	const uint8_t m_height;
	const uint8_t m_width;
	Cell** m_grid;
};
