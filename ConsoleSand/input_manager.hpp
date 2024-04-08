#pragma once

#include "grid_viewer.hpp"
#include "common_utils.hpp"

class InputManager
{
public:
	InputManager(GridViewer::Cursor* const cursorPtr, uint8_t xBound, uint8_t yBound);
	~InputManager();

	void moveCursor();
	void cursorVisibility();
	void materialChoice(uint8_t& choice, uint8_t minId, uint8_t maxId);
	bool spawnMaterial();

private:
	GridViewer::Cursor* m_cursor;
	
	struct Boundaries
	{
		uint8_t x;
		uint8_t y;
	};

	Boundaries m_boundaries;
};
