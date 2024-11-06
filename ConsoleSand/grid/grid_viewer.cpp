#include <iostream>
#include <sstream>

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
	showCarriage();
}

void GridViewer::hideCarriage() const
{
	std::cout << Config::Escape::Carriage::hide;
}

void GridViewer::showCarriage() const
{
	std::cout << Config::Escape::Carriage::show;
}

void GridViewer::start() const
{
	hideCarriage();
	displayControlsHint();
}

void GridViewer::move(ViewPort::Move direction)
{
	switch (direction)
	{
		case ViewPort::Move::Up:
		{
			if (m_viewPort.corners[ViewPort::UpperLeft][ViewPort::Y] != 0 ||
				m_viewPort.corners[ViewPort::UpperRight][ViewPort::Y] != 0)
			{
				if (m_cursor.centeredAtY(m_viewPort))
					m_viewPort.shift(0, -1);
			}

			if (m_cursor.y != 0)
				m_cursor.y--;

			break;
		}
		case ViewPort::Move::Right:
		{
			if (m_viewPort.corners[ViewPort::BottomRight][ViewPort::X] != (m_gridWidth - 1) ||
				m_viewPort.corners[ViewPort::UpperRight][ViewPort::X] != (m_gridWidth - 1))
			{
				if (m_cursor.centeredAtX(m_viewPort))
					m_viewPort.shift(1, 0);
			}

			if (m_cursor.x != (m_gridWidth - 1))
				m_cursor.x++;

			break;
		}
		case ViewPort::Move::Down:
		{
			if (m_viewPort.corners[ViewPort::BottomLeft][ViewPort::Y] != (m_gridHeight - 1) ||
				m_viewPort.corners[ViewPort::BottomRight][ViewPort::Y] != (m_gridHeight - 1))
			{
				if (m_cursor.centeredAtY(m_viewPort))
					m_viewPort.shift(0, 1);
			}

			if (m_cursor.y != (m_gridHeight - 1))
				m_cursor.y++;

			break;
		}
		case ViewPort::Move::Left:
		{
			if (m_viewPort.corners[ViewPort::UpperLeft][ViewPort::X] != 0 ||
				m_viewPort.corners[ViewPort::BottomLeft][ViewPort::X] != 0)
			{
				if (m_cursor.centeredAtX(m_viewPort))
					m_viewPort.shift(-1, 0);
			}

			if (m_cursor.x != 0)
				m_cursor.x--;

			break;
		}
		case ViewPort::Move::None:
		default:
			break;
	};
}

void GridViewer::ViewPort::shift(int8_t offsetX, int8_t offsetY)
{
	corners[ViewPort::UpperLeft][ViewPort::X] += offsetX;
	corners[ViewPort::UpperLeft][ViewPort::Y] += offsetY;

	corners[ViewPort::UpperRight][ViewPort::X] += offsetX;
	corners[ViewPort::UpperRight][ViewPort::Y] += offsetY;

	corners[ViewPort::BottomLeft][ViewPort::X] += offsetX;
	corners[ViewPort::BottomLeft][ViewPort::Y] += offsetY;

	corners[ViewPort::BottomRight][ViewPort::X] += offsetX;
	corners[ViewPort::BottomRight][ViewPort::Y] += offsetY;
}

void GridViewer::display() const
{
	if (m_cells == nullptr)
		return;

	std::stringstream buffer;
	for (uint16_t y = m_viewPort.corners[ViewPort::UpperLeft][ViewPort::Y]; y <= m_viewPort.corners[ViewPort::BottomRight][ViewPort::Y]; y++)
	{
		for (uint16_t x = m_viewPort.corners[ViewPort::UpperLeft][ViewPort::X]; x <= m_viewPort.corners[ViewPort::BottomRight][ViewPort::X]; x++)
		{
			if ((!m_cursor.isHidden) && ((m_cursor.x == x) && (m_cursor.y == y)))
			{
				buffer << m_cursor.symbol;
				continue;
			}

			buffer << m_cells[x][y].material.color.c_str();
			buffer << m_cells[x][y].material.symbol;
			buffer << Config::Escape::Formatting::standart;
		}

		buffer << '\n';
	}

	std::cout << Config::Escape::Carriage::moveStart;
	std::cout << buffer.str();
}

void GridViewer::displayControlsHint() const
{
	for (uint8_t i = 0; i <= m_viewPort.height + 1; i++)
		std::cout << "\n";

	controlHint("Move cursor", "W A S D");
	controlHint("Toggle cursor visibility", "H");
	controlHint("Material choice", "Q E");
	controlHint("Material placement", "Space");
	controlHint("Clear All", "C");
	controlHint("End simulation", "Escape", false);
}

void GridViewer::controlHint(const std::string& description, const std::string& hotkeys, bool printEndline) const
{
	std::string extended = ": " + hotkeys;

	std::cout << Config::Escape::Formatting::underline
		<< description
		<< Config::Escape::Formatting::standart
		<< extended
		<< (printEndline ? "\n" : "");
}

void GridViewer::displayMaterialHint(Materials::Id materialId) const
{
	const Materials::Material material = Materials::materials.at(materialId);

	std::cout << Config::Escape::Formatting::underline
		<< "Current Material"
		<< Config::Escape::Formatting::standart
		<< ": "
		<< (materialId == Materials::Id::Air ? "" : material.color)
		<< (materialId == Materials::Id::Air ? "Air (clear)" : material.displayName)
		<< "                "
		<< Config::Escape::Formatting::standart
		<< "\n";
		
}

void GridViewer::displayCursorCoords(uint16_t x, uint16_t y)
{
	std::cout << Config::Escape::Formatting::underline
		<< "Cursor Position"
		<< Config::Escape::Formatting::standart
		<< ": "
		<< x << ", " << y << "                 ";
}

GridViewer::Cursor& GridViewer::cursor()
{
	return m_cursor;
}

inline bool GridViewer::Cursor::centeredAtX(const GridViewer::ViewPort& viewPort) const
{
	return (x == (viewPort.corners[ViewPort::BottomLeft][ViewPort::X] + viewPort.width / 2));
}

inline bool GridViewer::Cursor::centeredAtY(const GridViewer::ViewPort& viewPort) const
{

	return (y == (viewPort.corners[ViewPort::UpperLeft][ViewPort::Y] + viewPort.height / 2));
}
