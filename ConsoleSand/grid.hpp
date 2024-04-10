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

	std::pair<uint8_t, uint8_t> size() const;

	struct Cell
	{
		MaterialId	mId;
		Material	material;
		bool		hasMoved	= false;

		Cell() : mId(MaterialId::Air), material(materials.at(mId)), hasMoved(false) {}
		Cell(MaterialId mId) : mId(mId), material(materials.at(mId)), hasMoved(false) {}
	};

	Cell** cells();

	void process();

	void spawnMaterial(const uint8_t& row, const uint8_t& col, const MaterialId& mId);

	void clearAll();

private:
	void inline clearMoveState();

	typedef enum class GridBorder { Left = 0, Upper, Right, Bottom } gridBorderSpecify;
	bool inline trespassing(const int8_t& val, const gridBorderSpecify& whatBorder) const;

	void inline replaceCellBy(Cell& cell, const int8_t& row, const int8_t& col, Cell newCell);

	bool processPowdery(Cell& cell, const int8_t& row, const int8_t& col);
	bool processLiquid(Cell& cell, const int8_t& row, const int8_t& col);
	bool processGas(Cell& cell, const int8_t& row, const int8_t& col);

	const uint8_t m_height;
	const uint8_t m_width;
	Cell** m_grid;
};
