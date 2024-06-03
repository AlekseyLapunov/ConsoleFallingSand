#include "grid.hpp"

Grid::Grid(const uint8_t width, const uint8_t height)
	: m_width(width), m_height(height)
{	
	m_grid = allocate(m_width, m_height);
	clearAll();
}

Grid::Grid(Grid& otherGrid)
	: m_width(otherGrid.m_height), m_height(otherGrid.m_width)
{
	m_grid = allocate(m_width, m_height);
	copyCells(otherGrid.m_grid);
}

Grid& Grid::operator= (Grid& otherGrid)
{
	m_width = otherGrid.m_width;
	m_height = otherGrid.m_height;

	m_grid = allocate(m_width, m_height);
	copyCells(otherGrid.m_grid);

	return *this;
}

Grid::~Grid()
{
	if (m_grid == nullptr)
		return;

	deallocate(m_grid, m_width);
}

Grid::Cell::Cell() : mId(Materials::Id::Air), material(Materials::materials.at(mId)), hasMoved(false) {}

Grid::Cell::Cell(Materials::Id mId) : mId(mId), material(Materials::materials.at(mId)), hasMoved(false) {}

Grid::Cell::Cell(const Cell& other) : mId(other.mId), material(other.material), hasMoved(other.hasMoved) {}

Grid::Cell& Grid::Cell::operator= (const Grid::Cell& other)
{
	mId = other.mId;
	material = other.material;
	hasMoved = other.hasMoved;
	return *this;
}

inline Grid::Cell** Grid::allocate(uint8_t width, uint8_t height)
{
	Cell** cells = new Cell*[width];
	for (uint8_t i = 0; i < width; i++)
		cells[i] = new Cell[height];

	return cells;
}

inline void Grid::deallocate(Cell** cells, uint8_t width)
{
	for (uint8_t i = 0; i < width; i++)
		delete[] cells[i];

	delete[] cells;

	cells = nullptr;
}

inline void Grid::copyCells(Cell** const cells)
{
	for (uint8_t x = 0; x < m_width; x++)
		for (uint8_t y = 0; y < m_height; y++)
			m_grid[x][y] = cells[x][y];
}

std::pair<uint8_t, uint8_t> Grid::size() const
{
	return {m_width, m_height};
}

Grid::Cell** const Grid::cells() const
{
	return m_grid;
}

void Grid::process()
{
	for (int8_t x = m_width - 1; x >= 0; x--)
		for (int8_t y = m_height - 1; y >= 0; y--)
		{
			Cell& cell = m_grid[x][y];

			if (cell.mId == Materials::Id::Air)
				continue;

			if (cell.hasMoved)
				continue;

			if (processAcidic(cell, x, y)) {}
			else if (processFlamable(cell, x, y)) {}
			else if (processDiffusing(cell, x, y)) {}

			if (processPowdery(cell, x, y)) {}
			else if (processLiquid(cell, x, y)) {}
			else if (processGas(cell, x, y)) {}
		}

	clearMoveState();
}

bool Grid::spawnMaterial(const uint8_t& x, const uint8_t& y, const Materials::Id& mId)
{
	if (&m_grid[x][y] == nullptr)
		return false;

	Cell cell(mId);
	m_grid[x][y] = cell;
	return true;
}

inline void Grid::clearAll()
{
	for (int8_t x = 0; x < m_width; x++)
		for (int8_t y = 0; y < m_height; y++)
			m_grid[x][y] = Cell();
}

void inline Grid::replaceCellBy(Cell& cell, const int8_t& x, const int8_t& y, Cell newCell)
{
	if (&m_grid[x][y] == nullptr)
		return;

	const Cell temp = cell;
	newCell.hasMoved = true;
	cell = newCell;
	m_grid[x][y] = temp;
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
	for (int8_t x = 0; x < m_width; x++)
		for (int8_t y = 0; y < m_height; y++)
			m_grid[x][y].hasMoved = false;
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

bool Grid::processPowdery(Cell& cell, const int8_t& x, const int8_t& y)
{
	const Materials::Type& thisType = cell.material.type;

	if (thisType != Materials::Type::Powdery)
		return false;

	if (!trespassing(y, GridBorder::Bottom) && m_grid[x][y + 1].material.type < thisType)
		replaceCellBy(m_grid[x][y + 1], x, y, cell);

	else if (!trespassing(x, GridBorder::Left) && !trespassing(y, GridBorder::Bottom) && m_grid[x - 1][y + 1].material.type < thisType)
		replaceCellBy(m_grid[x - 1][y + 1], x, y, cell);

	else if (!trespassing(x, GridBorder::Right) && !trespassing(y, GridBorder::Bottom) && m_grid[x + 1][y + 1].material.type < thisType)
		replaceCellBy(m_grid[x + 1][y + 1], x, y, cell);

	return true;
}

bool Grid::processLiquid(Cell& cell, const int8_t& x, const int8_t& y)
{
	const Materials::Type& thisType = cell.material.type;

	if (thisType != Materials::Type::Liquid)
		return false;

	if (!trespassing(y, GridBorder::Bottom) && m_grid[x][y + 1].material.type < thisType)
		replaceCellBy(m_grid[x][y + 1], x, y, cell);

	else if (!trespassing(x, GridBorder::Left) && m_grid[x - 1][y].material.type < thisType)
		replaceCellBy(m_grid[x - 1][y], x, y, cell);

	else if (!trespassing(x, GridBorder::Right) && m_grid[x + 1][y].material.type < thisType)
		replaceCellBy(m_grid[x + 1][y], x, y, cell);

	else if (!trespassing(x, GridBorder::Left) && !trespassing(y, GridBorder::Bottom) && m_grid[x - 1][y + 1].material.type < thisType)
		replaceCellBy(m_grid[x - 1][y + 1], x, y, cell);

	else if (!trespassing(x, GridBorder::Right) && !trespassing(y, GridBorder::Bottom) && m_grid[x + 1][y + 1].material.type < thisType)
		replaceCellBy(m_grid[x + 1][y + 1], x, y, cell);

	return true;
}

bool Grid::processGas(Cell& cell, const int8_t& x, const int8_t& y)
{
	const Materials::Type& thisType = cell.material.type;

	if (thisType != Materials::Type::Gas)
		return false;

	if (!trespassing(y, GridBorder::Upper) && m_grid[x][y - 1].material.type < thisType)
		replaceCellBy(m_grid[x][y - 1], x, y, cell);

	else if (!trespassing(x, GridBorder::Left) && m_grid[x - 1][y].material.type < thisType)
		replaceCellBy(m_grid[x - 1][y], x, y, cell);

	else if (!trespassing(x, GridBorder::Right) && m_grid[x + 1][y].material.type < thisType)
		replaceCellBy(m_grid[x + 1][y], x, y, cell);

	else if (!trespassing(y, GridBorder::Upper) && !trespassing(x, GridBorder::Left) && m_grid[x - 1][y - 1].material.type < thisType)
		replaceCellBy(m_grid[x - 1][y - 1], x, y, cell);

	else if (!trespassing(y, GridBorder::Upper) && !trespassing(x, GridBorder::Right) && m_grid[x + 1][y - 1].material.type < thisType)
		replaceCellBy(m_grid[x + 1][y - 1], x, y, cell);

	return true;
}

bool Grid::processAcidic(Cell& cell, const int8_t& x, const int8_t& y)
{
	const Materials::Feature& thisFeature = cell.material.feature;

	if (thisFeature != Materials::Feature::Acidic)
		return false;

	const Materials::Type& thisType = cell.material.type;

	bool acted = false;

	if (thisType == Materials::Type::Powdery || thisType == Materials::Type::Liquid)
	{
		if (!trespassing(y, GridBorder::Bottom))
		{
			if (m_grid[x][y + 1].mId != cell.mId)
				acted = clearCell(m_grid[x][y + 1]);
		} else
		if (!trespassing(x, GridBorder::Left) && !trespassing(y, GridBorder::Bottom))
		{
			if (m_grid[x - 1][y + 1].mId != cell.mId)
				acted = clearCell(m_grid[x - 1][y + 1]);
		} else
		if (!trespassing(x, GridBorder::Right) && !trespassing(y, GridBorder::Bottom))
		{
			if (m_grid[x + 1][y + 1].mId != cell.mId)
				acted = clearCell(m_grid[x + 1][y + 1]);
		}
	}

	if (thisType == Materials::Type::Gas)
	{
		if (!trespassing(y, GridBorder::Upper))
			if (m_grid[x][y - 1].mId != cell.mId)
				acted = clearCell(m_grid[x][y - 1]);

		if (!trespassing(x, GridBorder::Left) && !trespassing(y, GridBorder::Upper))
			if (m_grid[x - 1][y - 1].mId != cell.mId)
				acted = clearCell(m_grid[x - 1][y - 1]);

		if (!trespassing(x, GridBorder::Right) && !trespassing(y, GridBorder::Upper))
			if (m_grid[x + 1][y - 1].mId != cell.mId)
				acted = clearCell(m_grid[x + 1][y - 1]);
	}

	if (!trespassing(y, GridBorder::Upper) && !acted)
		if (m_grid[x][y - 1].mId != cell.mId)
			acted = clearCell(m_grid[x][y - 1]);

	if (!trespassing(y, GridBorder::Bottom) && !acted)
		if (m_grid[x][y + 1].mId != cell.mId)
			acted = clearCell(m_grid[x][y + 1]);

	if (!trespassing(x, GridBorder::Left) && !acted)
		if (m_grid[x - 1][y].mId != cell.mId)
			acted = clearCell(m_grid[x - 1][y]);

	if (!trespassing(x, GridBorder::Right) && !acted)
		if (m_grid[x + 1][y].mId != cell.mId)
			acted = clearCell(m_grid[x + 1][y]);
		
	return true;
}

bool Grid::processFlamable(Cell& cell, const int8_t& x, const int8_t& y)
{
	const Materials::Feature&	thisFeature	= cell.material.feature;

	if (thisFeature != Materials::Feature::Flamable)
		return false;

	const Materials::Type& thisType = cell.material.type;

	return true;
}

bool Grid::processDiffusing(Cell& cell, const int8_t& x, const int8_t& y)
{
	const Materials::Feature& thisFeature = cell.material.feature;

	if (thisFeature != Materials::Feature::Diffusing)
		return false;

	const Materials::Type& thisType = cell.material.type;

	bool acted = false;

	if (!trespassing(y, GridBorder::Upper) && !acted)
		if (m_grid[x][y - 1].material.type == Materials::Type::Liquid && m_grid[x][y - 1].mId != cell.mId)
			acted = spawnMaterial(x, y - 1, cell.mId);

	if (!trespassing(y, GridBorder::Bottom) && !acted)
		if (m_grid[x][y + 1].material.type == Materials::Type::Liquid && m_grid[x][y + 1].mId != cell.mId)
			acted = spawnMaterial(x, y + 1, cell.mId);

	if (!trespassing(x, GridBorder::Left) && !acted)
		if (m_grid[x - 1][y].material.type == Materials::Type::Liquid && m_grid[x - 1][y].mId != cell.mId)
			acted = spawnMaterial(x - 1, y, cell.mId);

	if (!trespassing(x, GridBorder::Right) && !acted)
		if (m_grid[x + 1][y].material.type == Materials::Type::Liquid && m_grid[x + 1][y].mId != cell.mId)
			acted = spawnMaterial(x + 1, y, cell.mId);

	return true;
}
