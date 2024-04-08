#include "grid.hpp"

Grid::Grid(const uint8_t height, const uint8_t width)
	: m_height(height), m_width(width)
{
	m_grid = new Cell*[height];
	for (uint8_t i = 0; i < height; i++)
		m_grid[i] = new Cell[width];
}

Grid::~Grid()
{
	for (uint8_t i = 0; i < m_height; i++)
		delete[] m_grid[i];

	delete[] m_grid;

	m_grid = nullptr;
}

std::pair<uint8_t, uint8_t> Grid::size()
{
	return {m_height, m_width};
}

Grid::Cell** Grid::cells()
{
	return m_grid;
}

void Grid::process()
{
	for (int8_t row = m_height - 1; row >= 0; row--)
		for (int8_t col = m_width - 1; col >= 0; col--)
		{
			Cell& cell = m_grid[row][col];

			if (cell.materialId == Air)
				continue;
			
			if (cell.materialId == Sand)
			{
				if (row + 1 >= m_height)
					continue;

				if (m_grid[row + 1][col].materialId == Air)
				{
					Cell temp = m_grid[row + 1][col];
					m_grid[row + 1][col] = cell;
					m_grid[row][col] = temp;
				} else
				if (m_grid[row + 1][col - 1].materialId == Air && (col - 1) >= 0)
				{
					Cell temp = m_grid[row + 1][col - 1];
					m_grid[row + 1][col - 1] = cell;
					m_grid[row][col] = temp;
				} else
				if (m_grid[row + 1][col + 1].materialId == Air && (col + 1) < m_width)
				{
					Cell temp = m_grid[row + 1][col + 1];
					m_grid[row + 1][col + 1] = cell;
					m_grid[row][col] = temp;
				}
				
			}
		}
}

void Grid::spawnMaterial(uint8_t row, uint8_t col, uint8_t materialId)
{
	Cell cell =  {materialId, materials.at(materialId)};
	m_grid[row][col] = cell;
}