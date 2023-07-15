#include "bicudo/core/core.hpp"

void bicudo::core::set_core_property(bicudo::coreproperty &core_property) {
    this->p_display_service = core_property.p_display_service;
    this->p_scene_service = core_property.p_scene_service;
}

bicudo::task &bicudo::core::generate_task() {
    return this->task_queue.emplace();
}

void bicudo::core::on_init_all() {
    SDL_Init(SDL_INIT_VIDEO);

    this->running_mainloop = true;
    this->capped_fps = 60;

    this->p_display_service->on_init();
    this->p_scene_service->on_init();
}

void bicudo::core::on_quit_all() {
    this->p_display_service->on_quit();
    this->p_display_service->on_quit();
}

int32_t bicudo::core::mainloop() {
    this->on_init_all();

    uint64_t old_ticks {};
    uint64_t current_ticks {SDL_GetPerformanceCounter()};
    uint64_t performance_frequency {1};

    auto p_display {this->p_display_service->get(bicudo::stack::toplevel)};
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

                    if (this->p_scene_service->p_current_scene != nullptr) {
                        this->p_scene_service->p_current_scene->on_event(sdl_event);
                    }

                    break;
                }
            }
        }
        
        while (!this->task_queue.empty()) {
            auto &task {this->task_queue.front()};
            task.function(task.p_data);
            this->task_queue.pop();
        }

        if (this->p_scene_service->p_current_scene != nullptr) {
            this->p_scene_service->p_current_scene->on_update();
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (this->p_scene_service->p_current_scene != nullptr) {
            this->p_scene_service->p_current_scene->on_render();
        }

        SDL_GL_SwapWindow(p_display->root());
        SDL_Delay(1000 / this->capped_fps);
    }

    this->on_quit_all();
    return 0;
}