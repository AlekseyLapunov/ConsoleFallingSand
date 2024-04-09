#include <chrono>
#include <thread>

#include "grid.hpp"
#include "grid_viewer.hpp"
#include "input_manager.hpp"

#define GRID_HEIGHT	22
#define GRID_WIDTH	50

#define FREQUENCY 500

int main(int argc, char* argv[])
{
	Grid grid(GRID_HEIGHT, GRID_WIDTH);

	GridViewer viewer(&grid, CURSOR, 0, 0);

	GridViewer::Cursor* cursor = viewer.cursor();

	InputManager inputManager(cursor, GRID_WIDTH, GRID_HEIGHT);

	viewer.hideCarriage();
	viewer.displayControlsHint();

	materialId currentMaterialId = Air;

	while (true)
	{
		grid.process();

		viewer.display();
		viewer.displayMaterialHint(currentMaterialId);

		inputManager.moveCursor();
		inputManager.cursorVisibility();
		inputManager.materialChoice(currentMaterialId, Air, Gas);
		if (inputManager.spawnMaterial())
			grid.spawnMaterial(cursor->y, cursor->x, currentMaterialId);

		std::this_thread::sleep_for(
			std::chrono::milliseconds(
				int(1000.0f / FREQUENCY)
			)
		);
	}

	viewer.showCarriage();

	return 0;
}