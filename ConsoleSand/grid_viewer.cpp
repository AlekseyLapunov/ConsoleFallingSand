#include <iostream>

#include "grid_viewer.hpp"

GridViewer::GridViewer(Grid* const gridPtr, char cursorSymbol,
						uint8_t cursorPosX, uint8_t cursorPosY)
	: m_cells(gridPtr->cells()), m_height(gridPtr->size().first), m_width(gridPtr->size().second)
{
	m_cursor = Cursor();

	m_cursor.symbol = cursorSymbol;
	m_cursor.x = cursorPosX;
	m_cursor.y = cursorPosY;
}

GridViewer::~GridViewer()
{
	//delete m_cursor;
	//m_cursor = nullptr;
}

void GridViewer::hideCarriage() const
{
	std::cout << HIDE_CARRIAGE;
}

void GridViewer::showCarriage() const
{
	std::cout << SHOW_CARRIAGE;
}

void GridViewer::display() const
{
	if (m_cells == nullptr)
		return;

	std::cout << MOVE_CARRIAGE_START;

	for (uint8_t row = 0; row < m_height; row++)
	{
		for (uint8_t col = 0; col < m_width; col++)
		{
			if ((!m_cursor.isHidden) && ((m_cursor.x == col) && (m_cursor.y == row)))
			{
				std::cout << m_cursor.symbol;
				continue;
			}

			std::cout << m_cells[row][col].material.color.c_str();
			std::cout << m_cells[row][col].material.symbol;
			std::cout << STANDARD_STYLE;
		}

		std::cout << '\n';
	}
}

void GridViewer::displayControlsHint() const
{
	display();
	std::cout << "\n" << UNDERLINE
		<< "Move cursor"
		<< STANDARD_STYLE << ": W A S D";

	std::cout << "\n"
		<< UNDERLINE << "Toggle cursor visibility"
		<< STANDARD_STYLE << ": H";

	std::cout << "\n"
		<< UNDERLINE << "Material choice"
		<< STANDARD_STYLE << ": Q E";

	std::cout << "\n"
		<< UNDERLINE << "Material placement"
		<< STANDARD_STYLE << ": Space";

	std::cout << "\n"
		<< UNDERLINE << "Clear All"
		<< STANDARD_STYLE << ": C";

	std::cout << "\n"
		<< UNDERLINE << "End simulation"
		<< STANDARD_STYLE << ": Escape";
}

void GridViewer::displayMaterialHint(Materials::Id materialId) const
{
	const Materials::Material material = Materials::materials.at(materialId);

	std::cout << UNDERLINE
		<< "Current Material"
		<< STANDARD_STYLE
		<< ": "
		<< (materialId == Materials::Id::Air ? ""			  : material.color)
		<< (materialId == Materials::Id::Air ? "Air (clear)" : material.displayName)
		<< "                                               "
		<< STANDARD_STYLE;
		
}

GridViewer::Cursor& GridViewer::cursor()
{
	return m_cursor;
}

