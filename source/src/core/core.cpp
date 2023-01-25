#include "GL/glew.h"
#include "bicudo/core/core.hpp"
#include "bicudo/util/priority.hpp"
#include "bicudo/opengl/opengl_context_overview.hpp"

void bicudo::core::on_native_init() {
    this->running_mainloop = true;
    this->service_physic_engine.on_native_init();
}

void bicudo::core::on_native_quit() {
    this->service_physic_engine.on_native_quit();
}

int32_t bicudo::core::mainloop() {
    this->on_native_init();
    SDL_Event sdl_event {};

    while (this->running_mainloop) {
        while (SDL_PollEvent(&sdl_event)) {
            switch (sdl_event.type) {
                case SDL_QUIT: {
                    this->running_mainloop = false;
                    break;
                }

                default: {
                    break;
                }
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SDL_GL_SwapWindow(this->service_display.get_display(bicudo::stack::toplevel).root());
        SDL_Delay(this->capped_fps / 1000);
    }

    this->on_native_quit();
    return 0;
}
