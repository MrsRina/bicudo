# Bicudo

Bicudo is one framework to create 2D games, the first version has no GPU accelerated physics system.    
The purpose of creating this framework is not only to make games but learn physics, multi-threading & parallel tasks.

Physics use the concept of SAT (separation axis theorem) to compute displacement of collisions.
Renderer engine of Bicudo is made in API OpenGL 4.

There is bicudo-1 version, but that version is deprecated, but I recommend you take a look in that branch.

---

# Building

If you are on Windows, please replace `"Unix Makefiles"` with `"MinGW Makefiles"`, run the command:  
`cmake -S . -B ./cmake-build-debug/ -G "Unix Makefiles" && cmake --build ./cmake-build-debug/"`

Native "library" location:  
Linux: `build/libs/win32/libbicudo.a`  
Windows: `build/libs/linux/libbicudo.a`

note: remember to add `include/` headers too.

# Get started

First, remember to link SDL2, GLEW and FreeType library together with Bicudo. Download the latest Bicudo  
version in releases, setup `include/` and `libs/` in your project workspace folder or just move for compiler  
folder.

Let us understand how Bicudo works and why.
```c++
#include <bicudo/bicudo.hpp>

class game_scene : public bicudo::scene {
public:
    void on_create() override {
        // do your project stuff here.
        // it is called only once.
    };
    
    void on_destroy() override {
        // do your project stuff here.
        // it is called only once.
    };
    
    void on_unsafe_update() override {
        // unsafe because this method runs in a different thread.
        // called 60 times per second (60 fps)
    };
    
    void on_update() override {
        // main thread method.
        // called capped times per second or maximum frames per second.
    };
};

int main(int, char**) {
    bicudo::init();
    
    /* first you need to create one surface */
    bicudo::surface window {};
    bicudo::create(&window);
    
    /* second you need to configure the surface dimensions */
    window.rect = {bicudo::centered, bicudo::centered, 1280, 800};
    window.tag = "Bird Game";
    
    /* Create the first scene, in this case is game_scene */
    /* you do not need to worry about the ptr, bicudo is memory safe */
    game_scene *defaut_scene {new game_scene {}};
    bicudo::makecurrent(default_scene);
    
    /* run main thread mainloop */
    bicudo::mainloop();

    /* after mainloop is the shutdown segment */
    return 0;
}
```

# License

Bicudo use MIT license, we do not care for what purpose you use it, just follow the MIT terms.
