#pragma once

#include "grid.hpp"

class GridViewer
{
public:
	GridViewer(Grid* const gridPtr, uint8_t viewPortWidth, uint8_t viewPortHeight);
	~GridViewer();

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
		enum class Move { None, Up, Right, Down, Left };

		void shift(int8_t offsetX, int8_t offsetY);
	};

	struct Cursor
	{
		uint16_t x;
		uint16_t y;
		char symbol;
		bool isHidden = false;

		inline bool centeredAtX(const GridViewer::ViewPort& viewPort) const;
		inline bool centeredAtY(const GridViewer::ViewPort& viewPort) const;
	};

	void display() const;
	void displayControlsHint() const;
	void displayMaterialHint(Materials::Id materialId) const;
	void displayCursorCoords(uint16_t x, uint16_t y);
	void start() const;
	void move(ViewPort::Move direction);

	Cursor& cursor();

private:
	void hideCarriage() const;
	void showCarriage() const;

	Grid::Cell** const m_cells;
	const uint16_t m_gridWidth;
	const uint16_t m_gridHeight;

	ViewPort m_viewPort;
	Cursor m_cursor;
};
