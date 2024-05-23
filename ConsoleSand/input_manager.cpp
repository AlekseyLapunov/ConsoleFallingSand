#include "input_manager.hpp"

#include <windows.h>

#define KEY_DOWN(key) GetKeyState(key) & 0x8000

InputManager::InputManager(GridViewer::Cursor& const cursorPtr, uint8_t xBound, uint8_t yBound)
	: m_cursor(cursorPtr)
{
	m_boundaries.x = xBound;
	m_boundaries.y = yBound;
}

InputManager::~InputManager()
{}

void InputManager::moveCursor()
{
	if (m_cursor.x >= m_boundaries.x)
		m_cursor.x = m_boundaries.x - 1;

	if (m_cursor.y >= m_boundaries.y)
		m_cursor.y = m_boundaries.y - 1;

	if (KEY_DOWN('A'))
	{
		if (m_cursor.x == 0)
			m_cursor.x = m_boundaries.x - 1;
		else
			m_cursor.x -= 1;
	}
	if (KEY_DOWN('D'))
	{
		if (m_cursor.x == m_boundaries.x - 1)
			m_cursor.x = 0;
		else
			m_cursor.x += 1;
	}
	if (KEY_DOWN('W'))
	{
		if (m_cursor.y == 0)
			m_cursor.y = m_boundaries.y - 1;
		else
			m_cursor.y -= 1;
	}
	if (KEY_DOWN('S'))
	{
		if (m_cursor.y == m_boundaries.y - 1)
			m_cursor.y = 0;
		else
			m_cursor.y += 1;
	}
}

void InputManager::cursorVisibility()
{
	if (KEY_DOWN('H'))
	{
		m_cursor.isHidden = !m_cursor.isHidden;
	}
}

void InputManager::materialChoice(Materials::Id& choice, Materials::Id minId, Materials::Id maxId)
{
	if (KEY_DOWN('Q'))
	{
		if (choice == minId)
			choice = maxId;
		else
			choice = static_cast<Materials::Id>((int)choice - 1);

		while (KEY_DOWN('Q'));
	}
	if (KEY_DOWN('E'))
	{
		if (choice == maxId)
			choice = minId;
		else
			choice = static_cast<Materials::Id>((int)choice + 1);

		while (KEY_DOWN('E'));
	}
}

bool InputManager::spawnMaterial()
{
	return KEY_DOWN(VK_SPACE);
}

bool InputManager::clearGrid()
{
	if (KEY_DOWN('C'))
	{
		while (KEY_DOWN('C'));
		return true;
	}
	return false;
}

bool InputManager::endSimulation()
{
	if (KEY_DOWN(VK_ESCAPE))
	{
		while (KEY_DOWN(VK_ESCAPE));
		return true;
	}
	return false;
}