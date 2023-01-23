# Bicudo

Bicudo is one framework to create 2D games, the first version has no GPU accelerated physics system.    
The purpose of creating this framework is not only to make games but learn physics, multi-threading & parallel tasks.

Physics use the concept of SAT (separation axis theorem) to compute displacement of collisions.
Renderer engine of Bicudo is made in API OpenGL 4.

There is bicudo-1 version, but that version is deprecated, but I recommend you take a look in that branch.  
Bicudo-3 physics engine is in progress.

Third rewrite of Bicudo.

---

# Building

If you are on Windows, please replace `"Unix Makefiles"` with `"MinGW Makefiles"`, run the command:  
`cmake -S . -B ./cmake-build-debug/ -G "Unix Makefiles" && cmake --build ./cmake-build-debug/"`

Native "library" location:  
Linux: `build/libs/linux/libbicudo.a`  
Windows: `build/libs/win32/libbicudo.a (win32 but bicudo native library is actually 64)`

note: remember to add `include/` headers too.

# Get started


# Credits & License

Thank you Michael Tanaya, Huaming Chen, Jebediah Pavleas & Kelvin Sung. Thanks for the awesome published book by Aprees.  
Bicudo use MIT license, we do not care for what purpose you use it, just follow the MIT terms.
