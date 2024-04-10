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

std::pair<uint8_t, uint8_t> Grid::size() const
{
	return {m_height, m_width};
}

Grid::Cell** Grid::cells()
{
	return m_grid;
}

void Grid::process()
{
	for (int8_t row = 0; row < m_height; row++)
		for (int8_t col = 0; col < m_width; col++)
		{
			Cell& cell = m_grid[row][col];

			if (cell.mId == MaterialId::Air)
				continue;

			if (cell.hasMoved)
				continue;

			if (cell.material.type == MaterialType::Powdery)
			{
				if (trespassing(row, GridBorder::Bottom))
					continue;

				if (m_grid[row + 1][col].material.type == MaterialType::Void)
					replaceCellBy(m_grid[row + 1][col], row, col, cell);
				
				else if (m_grid[row + 1][col - 1].material.type == MaterialType::Void && !trespassing(col, GridBorder::Left))
					replaceCellBy(m_grid[row + 1][col - 1], row, col, cell);
				
				else if (m_grid[row + 1][col + 1].material.type == MaterialType::Void && !trespassing(col, GridBorder::Right))
					replaceCellBy(m_grid[row + 1][col + 1], row, col, cell);
			}
			else
			if (cell.material.type == MaterialType::Liquid)
			{
				if (trespassing(row, GridBorder::Bottom))
					continue;

				if (m_grid[row + 1][col].material.type == MaterialType::Void)
					replaceCellBy(m_grid[row + 1][col], row, col, cell);

				else if (m_grid[row][col - 1].material.type == MaterialType::Void && !trespassing(col, GridBorder::Left))
					replaceCellBy(m_grid[row][col - 1], row, col, cell);

				else if (m_grid[row][col + 1].material.type == MaterialType::Void && !trespassing(col, GridBorder::Right))
					replaceCellBy(m_grid[row][col + 1], row, col, cell);

				else if (m_grid[row + 1][col - 1].material.type == MaterialType::Void && !trespassing(col, GridBorder::Left))
					replaceCellBy(m_grid[row + 1][col - 1], row, col, cell);

				else if (m_grid[row + 1][col + 1].material.type == MaterialType::Void && !trespassing(col, GridBorder::Right))
					replaceCellBy(m_grid[row + 1][col + 1], row, col, cell);
			}
			else
			if (cell.material.type == MaterialType::Gas)
			{
				if (trespassing(row, GridBorder::Upper))
					continue;

				if (m_grid[row - 1][col].material.type == MaterialType::Void)
					replaceCellBy(m_grid[row - 1][col], row, col, cell);

				else if (m_grid[row][col - 1].material.type == MaterialType::Void && !trespassing(col, GridBorder::Left))
					replaceCellBy(m_grid[row][col - 1], row, col, cell);

				else if (m_grid[row][col + 1].material.type == MaterialType::Void && !trespassing(col, GridBorder::Right))
					replaceCellBy(m_grid[row][col + 1], row, col, cell);

				else if (m_grid[row - 1][col - 1].material.type == MaterialType::Void && !trespassing(col, GridBorder::Left))
					replaceCellBy(m_grid[row - 1][col - 1], row, col, cell);

				else if (m_grid[row - 1][col + 1].material.type == MaterialType::Void && !trespassing(col, GridBorder::Right))
					replaceCellBy(m_grid[row - 1][col + 1], row, col, cell);
			}
		}

	clearMoveState();
}

void Grid::spawnMaterial(uint8_t row, uint8_t col, MaterialId mId)
{
	Cell cell(mId);
	m_grid[row][col] = cell;
}

void Grid::clearAll()
{
	for (int8_t row = 0; row < m_height; row++)
		for (int8_t col = 0; col < m_width; col++)
			m_grid[row][col] = Cell();
}

void inline Grid::replaceCellBy(Cell& cell, int8_t row, int8_t col, Cell newCell)
{
	Cell temp = cell;
	newCell.hasMoved = true;
	cell = newCell;
	m_grid[row][col] = temp;
}

void inline Grid::clearMoveState()
{
	for (int8_t row = 0; row < m_height; row++)
		for (int8_t col = 0; col < m_width; col++)
			m_grid[row][col].hasMoved = false;
}

bool inline Grid::trespassing(int8_t val, gridBorderSpecify whatBorder) const
{
	if (whatBorder == GridBorder::Left || whatBorder == GridBorder::Upper)
		return ((val - 1) < 0);

	if (whatBorder == GridBorder::Right)
		return ((val + 1) >= m_width);

	if (whatBorder == GridBorder::Bottom)
		return ((val + 1) >= m_height);

	return false;
}