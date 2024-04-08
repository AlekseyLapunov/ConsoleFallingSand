# ConsoleFallingSand

My take on cellular automata: simple sand simulation (no friction constants, no gravity, no forces, etc) in Console output.

Using "windows.h" library functions for getting keyboard input (more: input_manager.hpp & input_manager.cpp).

For now the only material with some implemented logic is Sand.

Project can be built either via Visual Studio or using compilers such as MinGW:

```
cd ConsoleSand
g++ *.cpp -o ./app.exe
```
Console Application controls:
```
Move cursor: W A S D
Choose material: Q E
Spawn material particle: Space
Toggle cursor visibility: H
```
