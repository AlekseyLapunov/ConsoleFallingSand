#pragma once

#include "grid.hpp"

class GridViewer
{
public:
	GridViewer(Grid* const gridPtr, uint8_t viewPortWidth, uint8_t viewPortHeight);
	~GridViewer();

	void display() const;
	void displayControlsHint() const;
	void displayMaterialHint(Materials::Id materialId) const;
	void hideCarriage() const;
	void showCarriage() const;

	struct Cursor
	{
		uint16_t x;
		uint16_t y;
		char symbol;
		bool isHidden = false;
	};

	struct ViewPort
	{
		uint8_t width;
		uint8_t height;

		static const uint8_t numCorners = 4;
		static const uint8_t numCoords = 2;

		uint16_t corners[numCorners][numCoords] = { {0, 0}, {0, 0},
													{0, 0}, {0, 0} };

		enum Corners { UpperLeft, UpperRight, BottomLeft, BottomRight };
		enum Coords  { X, Y };
	};

	Cursor& cursor();

private:
	Grid::Cell** const m_cells;
	const uint16_t m_gridWidth;
	const uint16_t m_gridHeight;

	ViewPort m_viewPort;
	Cursor m_cursor;
};
