#include "input_manager.hpp"

#include <windows.h>

InputManager::InputManager(GridViewer::Cursor* const cursorPtr, uint8_t xBound, uint8_t yBound)
	: m_cursor(cursorPtr)
{
	m_boundaries.x = xBound;
	m_boundaries.y = yBound;
}

InputManager::~InputManager()
{}

void InputManager::moveCursor()
{
	if (m_cursor == nullptr)
		return;

	if (m_cursor->x >= m_boundaries.x)
		m_cursor->x = m_boundaries.x - 1;

	if (m_cursor->y >= m_boundaries.y)
		m_cursor->y = m_boundaries.y - 1;

	if (GetKeyState('A') & 0x8000)
	{
		if (m_cursor->x == 0)
			m_cursor->x = m_boundaries.x - 1;
		else
			m_cursor->x -= 1;
	}
	if (GetKeyState('D') & 0x8000)
	{
		if (m_cursor->x == m_boundaries.x - 1)
			m_cursor->x = 0;
		else
			m_cursor->x += 1;
	}
	if (GetKeyState('W') & 0x8000)
	{
		if (m_cursor->y == 0)
			m_cursor->y = m_boundaries.y - 1;
		else
			m_cursor->y -= 1;
	}
	if (GetKeyState('S') & 0x8000)
	{
		if (m_cursor->y == m_boundaries.y - 1)
			m_cursor->y = 0;
		else
			m_cursor->y += 1;
	}
}

void InputManager::cursorVisibility()
{
	if (GetKeyState('H') & 0x8000)
	{
		m_cursor->isHidden = !m_cursor->isHidden;
	}
}

void InputManager::materialChoice(uint8_t& choice, uint8_t minId, uint8_t maxId)
{
	if (GetKeyState('Q') & 0x8000)
	{
		if (choice == minId)
			choice = maxId;
		else
			choice--;
	}
	if (GetKeyState('E') & 0x8000)
	{
		if (choice == maxId)
			choice = minId;
		else
			choice++;
	}
}

bool InputManager::spawnMaterial()
{
	return GetKeyState(VK_SPACE) & 0x8000;
}