# ConsoleFallingSand

My take on cellular automata: simple materials simulation in Console output.

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

![demo](https://github.com/AlekseyLapunov/ConsoleFallingSand/blob/main/_.gif)

Output Terminal Settings (Windows):
```
Type: Developer PowerShell
Size at launch (characters): 120 x 30 (Columns x Rows)
Color scheme: Campbell
Font size: 12 (in points)
Font face: Cascadia Mono / Consolas
Line height: 1.2
Cursor shape: Bar "|"
```

Note: program is using [ANSI escape codes](https://en.wikipedia.org/wiki/ANSI_escape_code) for getting text formatting and colors.
