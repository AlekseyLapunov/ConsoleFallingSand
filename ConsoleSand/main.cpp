
#include <iostream>
#include <chrono>
#include <thread>

#include "grid.hpp"
#include "grid_viewer.hpp"
#include "input_manager.hpp"
#include "argument_parser.hpp"
#include "file_manager.h"

#define GRID_HEIGHT	22
#define GRID_WIDTH	50

#define FREQUENCY 500

int main(int argc, char* argv[])
{
	Args::Codes code = Args::check(argc, argv);
	if (code != Args::Codes::Good)
	{
		std::cerr << Args::codeInfo(code) << "\n";
		std::cerr << Args::help() << "\n";
	}
	
	FileManager::Output fm = FileManager::readFile(Args::fileName(argv));
	
	uint8_t gridHeight = GRID_HEIGHT;
	uint8_t gridWidth = GRID_WIDTH;

	if (!fm.ok)
		std::cerr << fm.description << "\n";
	else
	{
		gridHeight = fm.rows;
		gridHeight = fm.cols;
	}

	Grid grid(gridHeight, gridWidth);

	GridViewer viewer(&grid, CURSOR, gridWidth/2, gridHeight/2);

	GridViewer::Cursor* const cursor = viewer.cursor();

	InputManager inputManager(cursor, gridWidth, gridHeight);

	viewer.hideCarriage();
	viewer.displayControlsHint();

	MaterialId currentMaterialId = MaterialId::Air;

	while (true)
	{
		grid.process();

		viewer.display();
		viewer.displayMaterialHint(currentMaterialId);

		inputManager.moveCursor();
		inputManager.cursorVisibility();
		inputManager.materialChoice(currentMaterialId, MaterialId::Air, static_cast<MaterialId>(materials.size() - 1));

		if (inputManager.clearGrid())
			grid.clearAll();

		if (inputManager.spawnMaterial())
			grid.spawnMaterial(cursor->y, cursor->x, currentMaterialId);

		if (inputManager.endSimulation())
			break;

		std::this_thread::sleep_for(
			std::chrono::milliseconds(
				int(1000.0f / FREQUENCY)
			)
		);
	}

	viewer.showCarriage();

	return 0;
}