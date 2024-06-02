#pragma once

#include <utility>
#include <stdint.h>
#include <string>

#include "materials.hpp"

class Grid
{
public:
	struct Cell
	{
		Materials::Id	mId;
		Materials::Material	material;
		bool		hasMoved = false;

		Cell() : mId(Materials::Id::Air), material(Materials::materials.at(mId)), hasMoved(false) {}
		Cell(Materials::Id mId) : mId(mId), material(Materials::materials.at(mId)), hasMoved(false) {}
	};

	Grid(const uint8_t height, const uint8_t width);
	Grid(Grid& otherGrid);
	Grid& operator= (Grid& otherGrid);

	~Grid();

	std::pair<uint8_t, uint8_t> size() const;

	Cell** const cells() const;

	void process();

	bool spawnMaterial(const uint8_t& row, const uint8_t& col, const Materials::Id& mId);

	void clearAll();

private:

	inline Cell** allocate(uint8_t height, uint8_t width);
	inline void deallocate(Cell** cells, uint8_t height, uint8_t width);

	void inline clearMoveState();

	typedef enum class GridBorder { Left = 0, Upper, Right, Bottom } gridBorderSpecify;
	bool inline trespassing(const int8_t& val, const gridBorderSpecify& whatBorder) const;

	void inline replaceCellBy(Cell& cell, const int8_t& row, const int8_t& col, Cell newCell);
	bool inline clearCell(Cell& cell);

	bool processAcidic(Cell& cell, const int8_t& row, const int8_t& col);
	bool processFlamable(Cell& cell, const int8_t& row, const int8_t& col);
	bool processDiffusing(Cell& cell, const int8_t& row, const int8_t& col);

	bool processPowdery(Cell& cell, const int8_t& row, const int8_t& col);
	bool processLiquid(Cell& cell, const int8_t& row, const int8_t& col);
	bool processGas(Cell& cell, const int8_t& row, const int8_t& col);

	uint8_t m_height;
	uint8_t m_width;
	Cell** m_grid;
};
