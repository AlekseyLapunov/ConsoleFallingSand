#include <iostream>

#include "grid_viewer.hpp"

GridViewer::GridViewer(Grid* const gridPtr, char cursorSymbol,
						uint8_t cursorPosX, uint8_t cursorPosY)
	: m_gridPtr(gridPtr)
{
	m_cursor = new Cursor;

	m_cursor->symbol = cursorSymbol;
	m_cursor->x = cursorPosX;
	m_cursor->y = cursorPosY;
}

GridViewer::~GridViewer()
{
	delete m_cursor;

	m_cursor = nullptr;
}

void GridViewer::hideCarriage()
{
	std::cout << HIDE_CARRIAGE;
}

void GridViewer::showCarriage()
{
	std::cout << SHOW_CARRIAGE;
}

void GridViewer::display()
{
	if (m_gridPtr == nullptr)
		return;

	Grid::Cell** cells = m_gridPtr->cells();

	uint8_t height = 0;
	uint8_t width = 0;

	{
		std::pair<uint8_t, uint8_t> pack = m_gridPtr->size();
		height = pack.first;
		width  = pack.second;
	}

	if (height == 0 || width == 0)
		return;

	std::cout << MOVE_CARRIAGE_START;

	for (uint8_t row = 0; row < height; row++)
	{
		for (uint8_t col = 0; col < width; col++)
		{
			if ((!m_cursor->isHidden) && ((m_cursor->x == col) && (m_cursor->y == row)))
			{
				std::cout << m_cursor->symbol;
				continue;
			}

			std::cout << cells[row][col].material.color.c_str();
			std::cout << cells[row][col].material.symbol;
			std::cout << STANDARD_STYLE;
		}

		std::cout << '\n';
	}
}

void GridViewer::displayHint()
{
	display();
	std::cout << "\n" << UNDERLINE
		<< "Move cursor"
		<< STANDARD_STYLE << ": W A S D";

	std::cout << "\n"
		<< UNDERLINE << "Toggle cursor visibility"
		<< STANDARD_STYLE << ": H";

	std::cout << "\n"
		<< UNDERLINE << "Material choice:"
		<< STANDARD_STYLE << ": Q E";
}

void GridViewer::displayMaterialHint(uint8_t materialId)
{
	const Material material = materials.at(materialId);

	std::cout << UNDERLINE
		<< "Current Material"
		<< STANDARD_STYLE
		<< ": "
		<< (materialId == 0 ? ""			: material.color)
		<< (materialId == 0 ? "Air (clear)" : material.displayName)
		<< "                                               "
		<< STANDARD_STYLE;
		
}

GridViewer::Cursor* GridViewer::cursor()
{
	return m_cursor;
}

