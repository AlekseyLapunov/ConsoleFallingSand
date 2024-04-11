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

Grid::Cell** const Grid::cells() const
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

			if		(processAcidic(cell, row, col));
			else if (processFlamable(cell, row, col));
			else if (processDiffusing(cell, row, col));

			if		(processPowdery(cell, row, col));
			else if (processLiquid(cell, row, col));
			else if (processGas(cell, row, col));
		}

	clearMoveState();
}

bool Grid::spawnMaterial(const uint8_t& row, const uint8_t& col, const MaterialId& mId)
{
	if (&m_grid[row][col] == nullptr)
		return false;

	Cell cell(mId);
	m_grid[row][col] = cell;
	return true;
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

bool inline Grid::clearCell(Cell& cell)
{
	if (&cell == nullptr)
		return false;

	cell = Cell();

	return true;
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

bool Grid::processAcidic(Cell& cell, const int8_t& row, const int8_t& col)
{
	const MaterialFeature&	thisFeature = cell.material.feature;

	if (thisFeature != MaterialFeature::Acidic)
		return false;

	const MaterialType& thisType = cell.material.type;

	bool acted = false;

	if (thisType == MaterialType::Powdery || thisType == MaterialType::Liquid)
	{
		if (!trespassing(row, GridBorder::Bottom))
		{
			if (m_grid[row + 1][col].mId != cell.mId)
				acted = clearCell(m_grid[row + 1][col]);
		} else
		if (!trespassing(col, GridBorder::Left) && !trespassing(row, GridBorder::Bottom))
		{
			if (m_grid[row + 1][col - 1].mId != cell.mId)
				acted = clearCell(m_grid[row + 1][col - 1]);
		} else
		if (!trespassing(col, GridBorder::Right) && !trespassing(row, GridBorder::Bottom))
		{
			if (m_grid[row + 1][col + 1].mId != cell.mId)
				acted = clearCell(m_grid[row + 1][col + 1]);
		}
	}

	if (thisType == MaterialType::Gas)
	{
		if (!trespassing(row, GridBorder::Upper))
			if (m_grid[row - 1][col].mId != cell.mId)
				acted = clearCell(m_grid[row - 1][col]);

		if (!trespassing(col, GridBorder::Left) && !trespassing(row, GridBorder::Upper))
			if (m_grid[row - 1][col - 1].mId != cell.mId)
				acted = clearCell(m_grid[row - 1][col - 1]);

		if (!trespassing(col, GridBorder::Right) && !trespassing(row, GridBorder::Upper))
			if (m_grid[row - 1][col + 1].mId != cell.mId)
				acted = clearCell(m_grid[row - 1][col + 1]);
	}

	if (!trespassing(row, GridBorder::Upper) && !acted)
		if (m_grid[row - 1][col].mId != cell.mId)
			acted = clearCell(m_grid[row - 1][col]);

	if (!trespassing(row, GridBorder::Bottom) && !acted)
		if (m_grid[row + 1][col].mId != cell.mId)
			acted = clearCell(m_grid[row + 1][col]);

	if (!trespassing(col, GridBorder::Left) && !acted)
		if (m_grid[row][col - 1].mId != cell.mId)
			acted = clearCell(m_grid[row][col - 1]);

	if (!trespassing(col, GridBorder::Right) && !acted)
		if (m_grid[row][col + 1].mId != cell.mId)
			acted = clearCell(m_grid[row][col + 1]);
		
	return true;
}

bool Grid::processFlamable(Cell& cell, const int8_t& row, const int8_t& col)
{
	const MaterialFeature&	thisFeature	= cell.material.feature;

	if (thisFeature != MaterialFeature::Flamable)
		return false;

	const MaterialType& thisType = cell.material.type;

	return true;
}

bool Grid::processDiffusing(Cell& cell, const int8_t& row, const int8_t& col)
{
	const MaterialFeature&	thisFeature = cell.material.feature;

	if (thisFeature != MaterialFeature::Diffusing)
		return false;

	const MaterialType& thisType = cell.material.type;

	bool acted = false;

	if (!trespassing(row, GridBorder::Upper) && !acted)
		if (m_grid[row - 1][col].material.type == MaterialType::Liquid && m_grid[row - 1][col].mId != cell.mId)
			acted = spawnMaterial(row - 1, col, cell.mId);

	if (!trespassing(row, GridBorder::Bottom) && !acted)
		if (m_grid[row + 1][col].material.type == MaterialType::Liquid && m_grid[row + 1][col].mId != cell.mId)
			acted = spawnMaterial(row + 1, col, cell.mId);

	if (!trespassing(col, GridBorder::Left) && !acted)
		if (m_grid[row][col - 1].material.type == MaterialType::Liquid && m_grid[row][col - 1].mId != cell.mId)
			acted = spawnMaterial(row, col - 1, cell.mId);

	if (!trespassing(col, GridBorder::Right) && !acted)
		if (m_grid[row][col + 1].material.type == MaterialType::Liquid && m_grid[row][col + 1].mId != cell.mId)
			acted = spawnMaterial(row, col + 1, cell.mId);

	return true;
}