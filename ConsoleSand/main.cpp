
#include <iostream>
#include <chrono>
#include <thread>

#include "grid.hpp"
#include "grid_viewer.hpp"
#include "input_manager.hpp"
#include "argument_parser.hpp"

#define GRID_HEIGHT	22
#define GRID_WIDTH	50

#define FREQUENCY 500

int main(int argc, char* argv[])
{
	Args::Codes code = Args::check(argc, argv);
	if (code != Args::Codes::Good)
	{
		std::cout << Args::codeInfo(code) << "\n";
		std::cout << Args::help() << "\n";
		return 0;
	}
	std::cout << Args::fileName(argv);

	Grid grid(GRID_HEIGHT, GRID_WIDTH);

	GridViewer viewer(&grid, CURSOR, GRID_WIDTH/2, GRID_HEIGHT/2);

	GridViewer::Cursor* const cursor = viewer.cursor();

	InputManager inputManager(cursor, GRID_WIDTH, GRID_HEIGHT);

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