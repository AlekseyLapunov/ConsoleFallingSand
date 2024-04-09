# ConsoleFallingSand

My take on cellular automata: simple sand simulation (no friction constants, no gravity, no forces, etc) in Console output.

Using "windows.h" library functions for getting keyboard input (more: input_manager.hpp & input_manager.cpp).

Project can be built either via Visual Studio or using compilers such as MinGW:

```
cd ConsoleSand
g++ *.cpp -o ./app.exe
```
Console Application controls:
```
Move cursor: W A S D
Toggle cursor visibility: H
Material choice: Q E
Spawn material particle: Space
```
Quick Demo GIF:
![](https://github.com/AlekseyLapunov/ConsoleFallingSand/blob/main/_.gif)
