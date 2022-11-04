# Bicudo

Bicudo is one framework to create 2D games, the first version has no GPU acceleration to physics sysstem, this version (bicudo 2) contains this feature.  
The proposite of this framework is not make only games but learn physics, multi-threading & parallel tasks.

# Building

If you are on Windows, please replace '"Unix Makefiles"~ with ~"MinGW Makefiles"~, run the command:  
~cmake -S . -B ./cmake-build-debug/ -G "Unix Makefiles" && cmake --build ./cmake-build-debug/"~

Native "library" location:
| Linux: build/libs/linuxbicudo.so
| Windows: build/libs/winbicudo.so

note: remember to add the ~includes/~ headers too.

# Tutorials

Unfortunately Bicudo has no documentation & tutorials, soon...

# License

The bicudo use MIT license, we do not care for what purpose you use it, just follow the MIT terms.
