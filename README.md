# ConsoleFallingSand

My take on cellular automata: simple materials simulation in Console output.

Using "windows.h" library (and "ncurses.h" for Linux) functions for getting keyboard input (more: [input_manager.hpp](https://github.com/AlekseyLapunov/ConsoleFallingSand/blob/main/ConsoleSand/helpers/input_manager.hpp) & [input_manager.cpp](https://github.com/AlekseyLapunov/ConsoleFallingSand/blob/main/ConsoleSand/helpers/input_manager.cpp)).

Console Application controls:
```
Move cursor: W A S D
Toggle cursor visibility: H
Material choice: Q E
Spawn material particle: Space
Clear All: C
End simulation: Escape
```
Quick Demo GIF:

![demo](https://github.com/AlekseyLapunov/ConsoleFallingSand/blob/main/_.gif)

Output Terminal Settings (Windows):
```
Type: Developer PowerShell
Size at launch (characters, Columns x Rows): 120 x 30
Color scheme: Campbell
Font size (points): 12
Font face: Cascadia Mono / Consolas
Line height: 1.2
Cursor shape: Bar "|"
```

Note: program is using [ANSI escape codes](https://en.wikipedia.org/wiki/ANSI_escape_code) for getting text formatting and colors.
