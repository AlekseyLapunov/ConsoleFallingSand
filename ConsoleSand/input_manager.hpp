#pragma once

#include "grid_viewer.hpp"

class InputManager
{
public:
	InputManager(GridViewer::Cursor& cursorPtr, uint8_t xBound, uint8_t yBound);
	~InputManager();

	void moveCursor();
	void cursorVisibility();
	void materialChoice(Materials::Id& choice, Materials::Id minId, Materials::Id maxId);
	bool spawnMaterial();
	bool clearGrid();
	bool endSimulation();

private:
	GridViewer::Cursor& m_cursor;
	
	struct Boundaries
	{
		uint8_t x;
		uint8_t y;
	};

	Boundaries m_boundaries;
};
