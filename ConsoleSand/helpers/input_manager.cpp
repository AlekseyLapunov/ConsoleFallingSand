#include "input_manager.hpp"

#ifdef _WIN32
#include <windows.h>
#define KEY_DOWN(key) (GetKeyState(key) & 0x8000)
#define ESCAPE_KEY VK_ESCAPE
#define SPACE_KEY VK_SPACE
#else
#include <ncurses.h>
#define KEY_DOWN(key) (key == getch())
#define ESCAPE_KEY 27
#define SPACE_KEY ' '
#endif

InputManager::InputManager(GridViewer::Cursor& cursorPtr, uint16_t xBound, uint16_t yBound)
	: m_cursor(cursorPtr)
{
	m_boundaries.x = xBound;
	m_boundaries.y = yBound;

#ifndef _WIN32
	initscr();
	cbreak();
	noecho();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
#endif
}

InputManager::~InputManager()
{
#ifndef _WIN32
	closeInput();
#endif
}

void InputManager::moveCursor()
{
	if (m_cursor.x >= m_boundaries.x)
		m_cursor.x = m_boundaries.x - 1;

	if (m_cursor.y >= m_boundaries.y)
		m_cursor.y = m_boundaries.y - 1;

	if (KEY_DOWN('A'))
	{
		if (m_cursor.x == 0)
			return;

		m_cursor.x -= 1;
	}
	if (KEY_DOWN('D'))
	{
		if (m_cursor.x == m_boundaries.x - 1)
			return;
		
		m_cursor.x += 1;
	}
	if (KEY_DOWN('W'))
	{
		if (m_cursor.y == 0)
			return;
		
		m_cursor.y -= 1;
	}
	if (KEY_DOWN('S'))
	{
		if (m_cursor.y == m_boundaries.y - 1)
			return;
		
		m_cursor.y += 1;
	}
}

void InputManager::cursorVisibility()
{
	if (KEY_DOWN('H'))
	{
		m_cursor.isHidden = !m_cursor.isHidden;

		while (KEY_DOWN('H'));
	}
}

void InputManager::materialChoice(Materials::Id& choice, Materials::Id minId, Materials::Id maxId) const
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

bool InputManager::spawnMaterial() const
{
	return KEY_DOWN(SPACE_KEY);
}

bool InputManager::clearGrid() const
{
	if (KEY_DOWN('C'))
	{
		while (KEY_DOWN('C'));
		return true;
	}
	return false;
}

bool InputManager::endSimulation() const
{
	if (KEY_DOWN(ESCAPE_KEY))
	{
		while (KEY_DOWN(ESCAPE_KEY));
		return true;
	}
	return false;
}