#pragma once

#include "grid.hpp"

class GridViewer
{
public:
	GridViewer(Grid* const gridPtr, uint8_t cursorPosX, uint8_t cursorPosY);
	~GridViewer();

	void display() const;
	void displayControlsHint() const;
	void displayMaterialHint(Materials::Id materialId) const;
	void hideCarriage() const;
	void showCarriage() const;

	struct Cursor
	{
		uint8_t x;
		uint8_t y;
		char	symbol;
		bool	isHidden = false;
	};

	Cursor& cursor();

private:
	Grid::Cell** const m_cells;
	const uint8_t m_width;
	const uint8_t m_height;
	Cursor m_cursor;
};