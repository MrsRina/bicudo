# Bicudo

Bicudo is one framework to create 2D games, the first version has no GPU accelerated physics system.    
The proposite of this framework is not make only games but learn physics, multi-threading & parallel tasks.

Physics use the concept of SAT (separation axis theorem) to repruduce displacement of collisions.
Renderer engine of Bicudo is made in API OpenGL 4.

# Building

If you are on Windows, please replace '"Unix Makefiles" with "MinGW Makefiles", run the command:  
`cmake -S . -B ./cmake-build-debug/ -G "Unix Makefiles" && cmake --build ./cmake-build-debug/"`

Native "library" location:  
Linux: `build/libs/linuxbicudo.so`
Windows: `build/libs/winbicudo.so`

note: remember to add the ´include/´ headers too.

# Tutorials

Unfortunately Bicudo has no documentation & tutorials now, soon...

# License

Bicudo use MIT license, we do not care for what purpose you use it, just follow the MIT terms.
