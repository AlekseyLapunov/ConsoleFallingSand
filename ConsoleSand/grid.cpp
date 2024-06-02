#include "grid.hpp"

Grid::Grid(const uint8_t height, const uint8_t width)
	: m_height(height), m_width(width)
{	
	m_grid = allocate(height, width);
	clearAll();
}

Grid::Grid(Grid& otherGrid)
	: m_height(otherGrid.m_height), m_width(otherGrid.m_width), m_grid(otherGrid.m_grid)
{
	otherGrid.m_grid = nullptr;
}

Grid& Grid::operator= (Grid& otherGrid)
{
	otherGrid.m_grid = nullptr;
	m_height = otherGrid.m_height;
	m_width = otherGrid.m_width;
	m_grid = otherGrid.m_grid;

	return *this;
}

Grid::~Grid()
{
	if (m_grid == nullptr)
		return;

	deallocate(m_grid, m_height, m_width);
}

inline Grid::Cell** Grid::allocate(uint8_t height, uint8_t width)
{
	Cell** cells = new Cell*[height];
	for (uint8_t i = 0; i < height; i++)
		cells[i] = new Cell[width];

	return cells;
}

inline void Grid::deallocate(Cell** cells, uint8_t height, uint8_t width)
{
	for (uint8_t i = 0; i < height; i++)
		delete[] cells[i];

	delete[] cells;

	cells = nullptr;
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

			if (cell.mId == Materials::Id::Air)
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

bool Grid::spawnMaterial(const uint8_t& x, const uint8_t& y, const Materials::Id& mId)
{
	if (&m_grid[y][x] == nullptr)
		return false;

	Cell cell(mId);
	m_grid[y][x] = cell;
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
	const Materials::Type& thisType = cell.material.type;

	if (thisType != Materials::Type::Powdery)
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
	const Materials::Type& thisType = cell.material.type;

	if (thisType != Materials::Type::Liquid)
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
	const Materials::Type& thisType = cell.material.type;

	if (thisType != Materials::Type::Gas)
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
	const Materials::Feature&	thisFeature = cell.material.feature;

	if (thisFeature != Materials::Feature::Acidic)
		return false;

	const Materials::Type& thisType = cell.material.type;

	bool acted = false;

	if (thisType == Materials::Type::Powdery || thisType == Materials::Type::Liquid)
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

	if (thisType == Materials::Type::Gas)
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
	const Materials::Feature&	thisFeature	= cell.material.feature;

	if (thisFeature != Materials::Feature::Flamable)
		return false;

	const Materials::Type& thisType = cell.material.type;

	return true;
}

bool Grid::processDiffusing(Cell& cell, const int8_t& row, const int8_t& col)
{
	const Materials::Feature&	thisFeature = cell.material.feature;

	if (thisFeature != Materials::Feature::Diffusing)
		return false;

	const Materials::Type& thisType = cell.material.type;

	bool acted = false;

	if (!trespassing(row, GridBorder::Upper) && !acted)
		if (m_grid[row - 1][col].material.type == Materials::Type::Liquid && m_grid[row - 1][col].mId != cell.mId)
			acted = spawnMaterial(col, row - 1, cell.mId);

	if (!trespassing(row, GridBorder::Bottom) && !acted)
		if (m_grid[row + 1][col].material.type == Materials::Type::Liquid && m_grid[row + 1][col].mId != cell.mId)
			acted = spawnMaterial(col, row + 1, cell.mId);

	if (!trespassing(col, GridBorder::Left) && !acted)
		if (m_grid[row][col - 1].material.type == Materials::Type::Liquid && m_grid[row][col - 1].mId != cell.mId)
			acted = spawnMaterial(col - 1, row, cell.mId);

	if (!trespassing(col, GridBorder::Right) && !acted)
		if (m_grid[row][col + 1].material.type == Materials::Type::Liquid && m_grid[row][col + 1].mId != cell.mId)
			acted = spawnMaterial(col + 1, row, cell.mId);

	return true;
}