#include "GL/glew.h"
#include "bicudo/core/core.hpp"
#include "bicudo/util/priority.hpp"
#include "bicudo/opengl/opengl_context_overview.hpp"

void bicudo::core::on_native_init() {
    this->running_mainloop = true;
    this->service_physic_engine.on_native_init();
    this->capped_fps = 60;
}

void bicudo::core::on_native_quit() {
    this->service_physic_engine.on_native_quit();
}

int32_t bicudo::core::mainloop() {
    this->on_native_init();
    SDL_Event sdl_event {};

    uint64_t old_ticks {};
    uint64_t current_ticks {};

    glDisable(GL_DEPTH_TEST);

    while (this->running_mainloop) {
        old_ticks = current_ticks;
        current_ticks = SDL_GetPerformanceCounter();

        this->delta = static_cast<float>(current_ticks - old_ticks) / static_cast<float>(SDL_GetPerformanceFrequency());
        auto &display {this->service_display.get_display(bicudo::stack::toplevel)};

        while (SDL_PollEvent(&sdl_event)) {
            switch (sdl_event.type) {
                case SDL_QUIT: {
                    this->running_mainloop = false;
                    break;
                }
                default: {
                    if (sdl_event.type == SDL_WINDOWEVENT && sdl_event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        display.rect[2] = sdl_event.window.data1;
                        display.rect[3] = sdl_event.window.data2;
                    }
                    break;
                }
            }
        }

        this->service_physic_engine.on_native_update();

        glViewport(0, 0, display.rect[2], display.rect[3]);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->service_physic_engine.on_native_render();

        SDL_GL_SwapWindow(display.root());
        SDL_Delay(1000 / this->capped_fps);
    }

    this->on_native_quit();
    return 0;
}
