#pragma once

#include "grid.hpp"

class GridViewer
{
public:
	GridViewer(Grid* const gridPtr, char cursorSymbol,
			   uint8_t cursorPosX, uint8_t cursorPosY);
	~GridViewer();

	void display();
	void displayControlsHint();
	void displayMaterialHint(uint8_t materialId);
	void hideCarriage();
	void showCarriage();

	struct Cursor
	{
		uint8_t x;
		uint8_t y;
		char	symbol;
		bool	isHidden = false;
	};

	Cursor* cursor();

private:
	Grid* const m_gridPtr;
	Cursor* m_cursor;
};
