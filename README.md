# Bicudo

Bicudo is an object-state-based and entity component system framework to create 2D games, the first version has no GPU-accelerated physics system.    
The purpose of creating this framework is to make games and learn physics, multi-threading & parallel tasks.

Physics uses the concept of SAT (separation axis theorem) to compute the displacement of collisions.
The renderer engine of Bicudo is made in API OpenGL and uses SDL to handle native windows & physical devices input.
Bicudo uses the same concept as Vulkan but is not directly low-level.

Mainly features:
* Multi-threading.
* GPU accelerated (rendering).
* Mathematical API library.
* Built on SDL.

---

# Building

If you are on Windows, please replace `"Unix Makefiles"` with `"Ninja"` or whatever toolchain makefile generator you want, run the command:  
`cmake -S . -B ./cmake-build-debug/ -G "Unix Makefiles" && cmake --build ./cmake-build-debug/"`

Native "library" location:  
Linux: `build/libs/linux/libbicudo.a`  
Windows: `build/libs/win32/libbicudo.a (win32 but bicudo native library is actually 64)`

# Get started

the library is having changes, and most of the features are rewritten.  
The mathematical part is very fun!

```c++
bicudo::vec2 a = bicudo::vec2(00.0f, 0.03940492304f);
bicudo::vec2 b {2.0f, 2.0f};

/* basic arithmetic vectorial operations. */
a = a * b + a - b * a;
a += b;
a -= b;
a *= b;
b /= 2.0f;
a /= b; // yes it exists.
a *= 2.0f; // scalar.

bicudo::dot(a, b);
bicudo::cross(a, b);
bicudo::normalize(a);
bicudo::rotate(a, RAD2DEG(90.0f));
bicudo::rotate(a, 0.0920399f, b); // center

/* There is only multiplication. */
bicudo::mat4 c = bicudo::mat4(1.0f); // identity
bicudo::mat4 d {1.0f};
bicudo::mat4 e = c * d;

bicudo::scale(e, {23.0f, 23.0f, 232.0f});
bicudo::rotate(e, {0, 1, 0});
bicudo::translate(e, {1.0, 4000.0f, 9999.0f});
```

# License
Bicudo uses MIT license, I do not care for what purpose you use it, just follow the MIT terms.
