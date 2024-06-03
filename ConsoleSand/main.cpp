#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "argument_parser.hpp"
#include "config.hpp"
#include "file_manager.hpp"
#include "input_manager.hpp"
#include "grid.hpp"
#include "grid_viewer.hpp"
#include "materials.hpp"

int main(int argc, char* argv[])
{
	Args::Codes code = Args::check(argc, argv);
	if (code != Args::Codes::Good)
	{
		std::cerr << Args::codeInfo(code) << "\n";
		std::cerr << Args::help() << "\n";
	}
	
	FileManager::Output fm = FileManager::readFile(Args::fileName(argv));
	
	uint8_t gridWidth  = Config::Grid::width;
	uint8_t gridHeight = Config::Grid::height;

	std::unique_ptr<Grid> gridObj;

	if (!fm.ok)
	{
		gridObj = std::make_unique<Grid>(gridWidth, gridHeight);
		std::cerr << fm.description << "\n";
	}
	else
	{
		gridWidth = fm.cols;
		gridHeight = fm.rows;
		gridObj = std::make_unique<Grid>(*fm.gridPtr);
	}

	Grid* const grid = gridObj.get();

	GridViewer viewer(grid, gridWidth/2, gridHeight/2);

	GridViewer::Cursor& cursor = viewer.cursor();

	InputManager inputManager(cursor, gridWidth, gridHeight);

	viewer.hideCarriage();
	viewer.displayControlsHint();

	Materials::Id currentMaterialId = Materials::Id::Air;

	while (true)
	{
		grid->process();

		viewer.display();
		viewer.displayMaterialHint(currentMaterialId);

		inputManager.moveCursor();
		inputManager.cursorVisibility();
		inputManager.materialChoice(currentMaterialId, Materials::Id::Air,
			static_cast<Materials::Id>(Materials::materials.size() - 1));

		if (inputManager.clearGrid())
			grid->clearAll();

		if (inputManager.spawnMaterial())
			grid->spawnMaterial(cursor.x, cursor.y, currentMaterialId);

		if (inputManager.endSimulation())
			break;

		std::this_thread::sleep_for(
			std::chrono::milliseconds(
				Config::refreshMilliseconds(Config::frequency)
			)
		);
	}

	viewer.showCarriage();

	return 0;
}