#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

#include "common/config.hpp"
#include "common/materials.hpp"
#include "helpers/input_manager.hpp"
#include "grid/grid.hpp"
#include "grid/grid_viewer.hpp"

int main(int argc, char* argv[])
{
	Grid grid(Config::Grid::width, Config::Grid::height);

	GridViewer viewer(&grid, Config::ViewPort::width, Config::ViewPort::height);

	GridViewer::Cursor& cursor = viewer.cursor();

	InputManager inputManager(cursor, Config::Grid::width, Config::Grid::height);

	viewer.hideCarriage();
	viewer.displayControlsHint();

	Materials::Id currentMaterialId = Materials::Id::Air;

	while (true)
	{
		grid.process();

		viewer.display();
		viewer.displayMaterialHint(currentMaterialId);

		inputManager.moveCursor();
		inputManager.cursorVisibility();
		inputManager.materialChoice(currentMaterialId, Materials::Id::Air,
			static_cast<Materials::Id>(Materials::materials.size() - 1));

		if (inputManager.clearGrid())
			grid.clearAll();

		if (inputManager.spawnMaterial())
			grid.spawnMaterial(cursor.x, cursor.y, currentMaterialId);

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