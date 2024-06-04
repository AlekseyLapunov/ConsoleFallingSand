#include <iostream>

#include "../common/config.hpp"
#include "grid_viewer.hpp"

GridViewer::GridViewer(Grid* const gridPtr, uint8_t viewPortWidth, uint8_t viewPortHeight)
	: m_cells(gridPtr->cells()), m_gridWidth(gridPtr->size().first), m_gridHeight(gridPtr->size().second)
{
	m_cursor = { static_cast<uint16_t>(viewPortWidth/2), static_cast<uint16_t>(m_gridHeight - viewPortHeight/2), Config::Signs::cursor, false};
	m_viewPort = {viewPortWidth, viewPortHeight};

	m_viewPort.corners[ViewPort::UpperLeft][ViewPort::X] = 0;
	m_viewPort.corners[ViewPort::UpperLeft][ViewPort::Y] = m_gridHeight - static_cast<uint16_t>(viewPortHeight);

	m_viewPort.corners[ViewPort::UpperRight][ViewPort::X] = m_viewPort.width - 1;
	m_viewPort.corners[ViewPort::UpperRight][ViewPort::Y] = m_gridHeight - static_cast<uint16_t>(viewPortHeight);

	m_viewPort.corners[ViewPort::BottomLeft][ViewPort::X] = 0;
	m_viewPort.corners[ViewPort::BottomLeft][ViewPort::Y] = m_gridHeight - 1;

	m_viewPort.corners[ViewPort::BottomRight][ViewPort::X] = m_viewPort.width - 1;
	m_viewPort.corners[ViewPort::BottomRight][ViewPort::Y] = m_gridHeight - 1;
}

GridViewer::~GridViewer()
{
}

void GridViewer::hideCarriage() const
{
	std::cout << Config::Escape::Carriage::hide;
}

void GridViewer::showCarriage() const
{
	std::cout << Config::Escape::Carriage::show;
}

void GridViewer::display() const
{
	if (m_cells == nullptr)
		return;

	std::cout << Config::Escape::Carriage::moveStart;

	for (uint16_t y = m_viewPort.corners[ViewPort::UpperLeft][ViewPort::Y]; y <= m_viewPort.corners[ViewPort::BottomRight][ViewPort::Y]; y++)
	{
		for (uint16_t x = m_viewPort.corners[ViewPort::UpperLeft][ViewPort::X]; x <= m_viewPort.corners[ViewPort::BottomRight][ViewPort::X]; x++)
		{
			if ((!m_cursor.isHidden) && ((m_cursor.x == x) && (m_cursor.y == y)))
			{
				std::cout << m_cursor.symbol;
				continue;
			}

			std::cout << m_cells[x][y].material.color.c_str();
			std::cout << m_cells[x][y].material.symbol;
			std::cout << Config::Escape::Formatting::standart;
		}

		std::cout << '\n';
	}
}

void GridViewer::displayControlsHint() const
{
	display();
	std::cout << "\n" << Config::Escape::Formatting::underline
		<< "Move cursor"
		<< Config::Escape::Formatting::standart << ": W A S D";

	std::cout << "\n"
		<< Config::Escape::Formatting::underline << "Toggle cursor visibility"
		<< Config::Escape::Formatting::standart << ": H";

	std::cout << "\n"
		<< Config::Escape::Formatting::underline << "Material choice"
		<< Config::Escape::Formatting::standart << ": Q E";

	std::cout << "\n"
		<< Config::Escape::Formatting::underline << "Material placement"
		<< Config::Escape::Formatting::standart << ": Space";

	std::cout << "\n"
		<< Config::Escape::Formatting::underline << "Clear All"
		<< Config::Escape::Formatting::standart << ": C";

	std::cout << "\n"
		<< Config::Escape::Formatting::underline << "End simulation"
		<< Config::Escape::Formatting::standart << ": Escape";
}

void GridViewer::displayMaterialHint(Materials::Id materialId) const
{
	const Materials::Material material = Materials::materials.at(materialId);

	std::cout << Config::Escape::Formatting::underline
		<< "Current Material"
		<< Config::Escape::Formatting::standart
		<< ": "
		<< (materialId == Materials::Id::Air ? ""			 : material.color)
		<< (materialId == Materials::Id::Air ? "Air (clear)" : material.displayName)
		<< "                "
		<< Config::Escape::Formatting::standart;
		
}

GridViewer::Cursor& GridViewer::cursor()
{
	return m_cursor;
}

