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

// Not readable code below, it will get optimized in the future
void Grid::process()
{
	for (int8_t row = 0; row < m_height; row++)
		for (int8_t col = 0; col < m_width; col++)
		{
			Cell& cell = m_grid[row][col];

			if (cell.mId == Air)
				continue;

			if (cell.hasMoved)
				continue;

			if (cell.mId == Sand)
			{
				if (trespassing(row, GridBorder::Bottom))
					continue;

				if (m_grid[row + 1][col].mId == Air)
				{
					Cell temp = m_grid[row + 1][col];
					cell.hasMoved = true;
					m_grid[row + 1][col] = cell;
					m_grid[row][col] = temp;
				}
				else
					if (m_grid[row + 1][col - 1].mId == Air && !trespassing(col, GridBorder::Left))
					{
						Cell temp = m_grid[row + 1][col - 1];
						cell.hasMoved = true;
						m_grid[row + 1][col - 1] = cell;
						m_grid[row][col] = temp;
					}
					else
						if (m_grid[row + 1][col + 1].mId == Air && !trespassing(col, GridBorder::Right))
						{
							Cell temp = m_grid[row + 1][col + 1];
							cell.hasMoved = true;
							m_grid[row + 1][col + 1] = cell;
							m_grid[row][col] = temp;
						}

			}
			else
			if (cell.mId == Water)
			{
				if (trespassing(row, GridBorder::Bottom))
					continue;

				if (m_grid[row + 1][col].mId == Air)
				{
					Cell temp = m_grid[row + 1][col];
					cell.hasMoved = true;
					m_grid[row + 1][col] = cell;
					m_grid[row][col] = temp;
				}
				else if (m_grid[row][col - 1].mId == Air && !trespassing(col, GridBorder::Left))
				{
					Cell temp = m_grid[row][col - 1];
					cell.hasMoved = true;
					m_grid[row][col - 1] = cell;
					m_grid[row][col] = temp;
				}
				else if (m_grid[row][col + 1].mId == Air && !trespassing(col, GridBorder::Right))
				{
					Cell temp = m_grid[row][col + 1];
					cell.hasMoved = true;
					m_grid[row][col + 1] = cell;
					m_grid[row][col] = temp;
				}
				else if (m_grid[row + 1][col - 1].mId == Air && !trespassing(col, GridBorder::Left))
				{
					Cell temp = m_grid[row + 1][col - 1];
					cell.hasMoved = true;
					m_grid[row + 1][col - 1] = cell;
					m_grid[row][col] = temp;
				}
				else if (m_grid[row + 1][col + 1].mId == Air && !trespassing(col, GridBorder::Right))
				{
					Cell temp = m_grid[row + 1][col + 1];
					cell.hasMoved = true;
					m_grid[row + 1][col + 1] = cell;
					m_grid[row][col] = temp;
				}

			}
			else
				if (cell.mId == Gas)
				{
					if (trespassing(row, GridBorder::Upper))
						continue;

					if (m_grid[row - 1][col].mId == Air)
					{
						Cell temp = m_grid[row - 1][col];
						cell.hasMoved = true;
						m_grid[row - 1][col] = cell;
						m_grid[row][col] = temp;
					}
					else if (m_grid[row][col - 1].mId == Air && !trespassing(col, GridBorder::Left))
					{
						Cell temp = m_grid[row][col - 1];
						cell.hasMoved = true;
						m_grid[row][col - 1] = cell;
						m_grid[row][col] = temp;
					}
					else if (m_grid[row][col + 1].mId == Air && !trespassing(col, GridBorder::Right))
					{
						Cell temp = m_grid[row][col + 1];
						cell.hasMoved = true;
						m_grid[row][col + 1] = cell;
						m_grid[row][col] = temp;
					}
					else if (m_grid[row - 1][col - 1].mId == Air && !trespassing(col, GridBorder::Left))
					{
						Cell temp = m_grid[row - 1][col - 1];
						cell.hasMoved = true;
						m_grid[row - 1][col - 1] = cell;
						m_grid[row][col] = temp;
					}
					else if (m_grid[row - 1][col + 1].mId == Air && !trespassing(col, GridBorder::Right))
					{
						Cell temp = m_grid[row - 1][col + 1];
						cell.hasMoved = true;
						m_grid[row - 1][col + 1] = cell;
						m_grid[row][col] = temp;
					}

				}
		}

	clearMoveState();
}

void Grid::spawnMaterial(uint8_t row, uint8_t col, materialId mId)
{
	Cell cell =  {mId, materials.at(mId)};
	m_grid[row][col] = cell;
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