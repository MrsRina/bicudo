# bicudo

Hello, the project is not finished yet.

The game base is writen in C++ and uses SDL2 + OpenGL 3+.
Its a Minecraft clone game.

# details

Simple game base with modules system (most like scripts) with dynamic interactions,
works for 2D and 3D (require a minimal change into matrix proj and OpenGL setup).
The project only works for window and uses mingw32, consider having mingw64 installed in default path for
windows (C:mingw64/).

For compile and debug in VS Code: 
- 1 Move/copy include/ folder in external/ folder into MinGW/.
- 2 Import this project folder into VS Code.
- 3 Install C++ intellisense and debug tools plugin (Microsoft one).
- 4 Then you will add the tasks (automatically put in VS Code)
- 5 Go to Terminal -> Run Tasks | select compile or run.
- 6 :) <3 wooohhbiii uu

Or look into build folder where the exe is created.

# disclaimer

The libs of Glew does not come by default for mingw .a,
but I compiled to mingw so it works, you can use for different projects <3.

wooohuu!
