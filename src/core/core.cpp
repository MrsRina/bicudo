#include "GL/glew.h"
#include "bicudo/core/core.hpp"
#include "bicudo/util/priority.hpp"

void bicudo::core::on_init_all() {
    this->running_mainloop = true;
    this->capped_fps = 60;

    this->p_display_service = new bicudo::displayservice();
    this->p_display_service->on_init();
}

void bicudo::core::on_quit_all() {
    this->p_display_service->on_quit();
    delete this->p_display_service;
}

int32_t bicudo::core::mainloop() {
    this->on_init_all();

    uint64_t old_ticks {};
    uint64_t current_ticks {SDL_GetPerformanceCounter()};
    uint64_t performance_frequency {1};

    auto p_display {this->p_display_service->get(bicudo::toplevel)};
    SDL_Event sdl_event {};
    glDisable(GL_DEPTH_TEST);

    while (this->running_mainloop) {
        old_ticks = current_ticks;

        current_ticks = SDL_GetPerformanceCounter();
        performance_frequency += SDL_GetPerformanceFrequency();

        this->delta = static_cast<float>(current_ticks - old_ticks) / static_cast<float>(performance_frequency);
        performance_frequency = 0;

        while (SDL_PollEvent(&sdl_event)) {
            switch (sdl_event.type) {
                case SDL_QUIT: {
                    this->running_mainloop = false;
                    break;
                }
                default: {
                    if (sdl_event.type == SDL_WINDOWEVENT && sdl_event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                        p_display->size.x = static_cast<int32_t>(sdl_event.window.data1);
                        p_display->size.y = static_cast<int32_t>(sdl_event.window.data2);
                    }

                    break;
                }
            }
        }
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SDL_GL_SwapWindow(p_display->root());
        SDL_Delay(1000 / this->capped_fps);
    }

    this->on_quit_all();
    return 0;
}
