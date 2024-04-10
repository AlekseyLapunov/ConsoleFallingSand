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
	for (int8_t row = m_height - 1; row >= 0; row--)
		for (int8_t col = m_width - 1; col >= 0; col--)
		{
			Cell& cell = m_grid[row][col];

			if (cell.mId == MaterialId::Air)
				continue;

			if (cell.hasMoved)
				continue;

			if		(processPowdery(cell, row, col));
			else if (processLiquid(cell, row, col));
			else if (processGas(cell, row, col));
		}

	clearMoveState();
}

void Grid::spawnMaterial(const uint8_t& row, const uint8_t& col, const MaterialId& mId)
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

void inline Grid::replaceCellBy(Cell& cell, const int8_t& row, const int8_t& col, Cell newCell)
{
	if (&m_grid[row][col] == nullptr)
		return;

	const Cell temp = cell;
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

bool inline Grid::trespassing(const int8_t& val, const gridBorderSpecify& whatBorder) const
{
	if (whatBorder == GridBorder::Left || whatBorder == GridBorder::Upper)
		return ((val - 1) < 0);

	if (whatBorder == GridBorder::Right)
		return ((val + 1) >= m_width);

	if (whatBorder == GridBorder::Bottom)
		return ((val + 1) >= m_height);

	return false;
}

bool Grid::processPowdery(Cell& cell, const int8_t& row, const int8_t& col)
{
	const MaterialType& thisType = cell.material.type;

	if (thisType != MaterialType::Powdery)
		return false;
	
	if (trespassing(row, GridBorder::Bottom))
		return false;

	if (m_grid[row + 1][col].material.type < thisType)
		replaceCellBy(m_grid[row + 1][col], row, col, cell);

	else if (m_grid[row + 1][col - 1].material.type < thisType && !trespassing(col, GridBorder::Left))
		replaceCellBy(m_grid[row + 1][col - 1], row, col, cell);

	else if (m_grid[row + 1][col + 1].material.type < thisType && !trespassing(col, GridBorder::Right))
		replaceCellBy(m_grid[row + 1][col + 1], row, col, cell);

	return true;
}

bool Grid::processLiquid(Cell& cell, const int8_t& row, const int8_t& col)
{
	const MaterialType& thisType = cell.material.type;

	if (thisType != MaterialType::Liquid)
		return false;

	if (trespassing(row, GridBorder::Bottom))
		return false;

	if (m_grid[row + 1][col].material.type < thisType)
		replaceCellBy(m_grid[row + 1][col], row, col, cell);

	else if (m_grid[row][col - 1].material.type < thisType && !trespassing(col, GridBorder::Left))
		replaceCellBy(m_grid[row][col - 1], row, col, cell);

	else if (m_grid[row][col + 1].material.type < thisType && !trespassing(col, GridBorder::Right))
		replaceCellBy(m_grid[row][col + 1], row, col, cell);

	else if (m_grid[row + 1][col - 1].material.type < thisType && !trespassing(col, GridBorder::Left))
		replaceCellBy(m_grid[row + 1][col - 1], row, col, cell);

	else if (m_grid[row + 1][col + 1].material.type < thisType && !trespassing(col, GridBorder::Right))
		replaceCellBy(m_grid[row + 1][col + 1], row, col, cell);

	return true;
}

bool Grid::processGas(Cell& cell, const int8_t& row, const int8_t& col)
{
	const MaterialType& thisType = cell.material.type;

	if (thisType != MaterialType::Gas)
		return false;

	if (trespassing(row, GridBorder::Upper))
		return false;

	if (m_grid[row - 1][col].material.type < thisType)
		replaceCellBy(m_grid[row - 1][col], row, col, cell);

	else if (m_grid[row][col - 1].material.type < thisType && !trespassing(col, GridBorder::Left))
		replaceCellBy(m_grid[row][col - 1], row, col, cell);

	else if (m_grid[row][col + 1].material.type < thisType && !trespassing(col, GridBorder::Right))
		replaceCellBy(m_grid[row][col + 1], row, col, cell);

	else if (m_grid[row - 1][col - 1].material.type < thisType && !trespassing(col, GridBorder::Left))
		replaceCellBy(m_grid[row - 1][col - 1], row, col, cell);

	else if (m_grid[row - 1][col + 1].material.type < thisType && !trespassing(col, GridBorder::Right))
		replaceCellBy(m_grid[row - 1][col + 1], row, col, cell);

	return true;
}