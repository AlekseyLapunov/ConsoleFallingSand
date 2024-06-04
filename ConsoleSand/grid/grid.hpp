#pragma once

#include <utility>
#include <stdint.h>
#include <string>

#include "../common/materials.hpp"

class Grid
{
public:
	Grid(const uint16_t width, const uint16_t height);
	Grid(Grid& otherGrid);
	Grid& operator= (Grid& otherGrid);

	~Grid();

	std::pair<uint16_t, uint16_t> size() const;

	struct Cell
	{
		Materials::Id	mId;
		Materials::Material	material;
		bool hasMoved = false;

		Cell();
		Cell(Materials::Id mId);
		Cell(const Cell& other);
		Cell& operator= (const Cell& other);
	};

	Cell** const cells() const;

	void process();

	bool spawnMaterial(const uint16_t& x, const uint16_t& y, const Materials::Id& mId);

	inline void clearAll();

private:

	inline Cell** allocate(uint16_t width, uint16_t height);
	inline void deallocate(Cell** cells, uint16_t width);
	inline void copyCells(Cell** const cells);

	void inline clearMoveState();

	typedef enum class GridBorder { Left = 0, Upper, Right, Bottom } gridBorderSpecify;
	bool inline trespassing(const int16_t& val, const gridBorderSpecify& whatBorder) const;

	void inline swapCells(Cell& cell, Cell& newCell);
	bool inline clearCell(Cell& cell);

	bool processAcidic(Cell& cell, const int16_t& x, const int16_t& y);
	bool processFlamable(Cell& cell, const int16_t& x, const int16_t& y);
	bool processDiffusing(Cell& cell, const int16_t& x, const int16_t& y);

	bool processPowdery(Cell& cell, const int16_t& x, const int16_t& y);
	bool processLiquid(Cell& cell, const int16_t& x, const int16_t& y);
	bool processGas(Cell& cell, const int16_t& x, const int16_t& y);

	uint16_t m_width;
	uint16_t m_height;
	Cell** m_grid;
};
