#pragma once

#include "grid.hpp"

class GridViewer
{
public:
	GridViewer(Grid* const gridPtr, char cursorSymbol,
			   uint8_t cursorPosX, uint8_t cursorPosY);
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

	Cursor* cursor() const;

private:
	//Grid* const m_gridPtr;
	Grid::Cell** const m_cells;
	uint8_t m_height;
	uint8_t m_width;
	Cursor* m_cursor;
};
