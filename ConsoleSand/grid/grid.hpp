#pragma once

#include <utility>
#include <stdint.h>
#include <string>

#include "../common/materials.hpp"

class Grid
{
public:
	Grid(const uint8_t width, const uint8_t height);
	Grid(Grid& otherGrid);
	Grid& operator= (Grid& otherGrid);

	~Grid();

	std::pair<uint8_t, uint8_t> size() const;

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

	bool spawnMaterial(const uint8_t& x, const uint8_t& y, const Materials::Id& mId);

	inline void clearAll();

private:

	inline Cell** allocate(uint8_t width, uint8_t height);
	inline void deallocate(Cell** cells, uint8_t width);
	inline void copyCells(Cell** const cells);

	void inline clearMoveState();

	typedef enum class GridBorder { Left = 0, Upper, Right, Bottom } gridBorderSpecify;
	bool inline trespassing(const int8_t& val, const gridBorderSpecify& whatBorder) const;

	void inline replaceCellBy(Cell& cell, const int8_t& x, const int8_t& y, Cell newCell);
	bool inline clearCell(Cell& cell);

	bool processAcidic(Cell& cell, const int8_t& x, const int8_t& y);
	bool processFlamable(Cell& cell, const int8_t& x, const int8_t& y);
	bool processDiffusing(Cell& cell, const int8_t& x, const int8_t& y);

	bool processPowdery(Cell& cell, const int8_t& x, const int8_t& y);
	bool processLiquid(Cell& cell, const int8_t& x, const int8_t& y);
	bool processGas(Cell& cell, const int8_t& x, const int8_t& y);

	uint8_t m_width;
	uint8_t m_height;
	Cell** m_grid;
};
