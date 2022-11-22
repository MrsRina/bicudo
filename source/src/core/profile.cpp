#include "bicudo/core/profile.hpp"
#include "bicudo/api/event/event.hpp"
#include "bicudo/impl/render/immshape.hpp"
#include <thread>

void bicudo::profile::do_create() {
    this->logger = new bicudo::logger {"MAIN"};
    this->driver_impl_manager = new bicudo::glimpl {};
    this->handler = new bicudo::handler {};
    this->physic = new bicudo::physic {};
    this->input = new bicudo::input {};

    this->mainloop = true;
    this->logger->send_info("Bicudo core profile initialised!");
}

void bicudo::profile::do_destroy() {

}

void bicudo::profile::do_loop() {
    if (this->surfaces.empty()) {
        this->logger->send_warning("There is no surface, can not mainloop.");
        return;
    }

    this->driver_impl_manager->prepare_opengl_attributes();
    for (bicudo::surface* &surface : this->surfaces) {
        surface->on_create();
        this->set_capped_fps(surface->locked_fps);
    }

    this->driver_impl_manager->create_opengl_context();
    bicudo::immshape::init();
    this->update_render_matrices();

    static SDL_Event sdl_event {};
    static bicudo::event wrapped_sdl_event {};
    static std::thread unsafe_thread {bicudo::unsafe, this};
    uint64_t cpu_ticks_now {}, cpu_ticks_last {};

    while (this->mainloop) {
        cpu_ticks_last = cpu_ticks_now;
        cpu_ticks_now = SDL_GetPerformanceCounter();
        bicudo::dt = static_cast<float>(cpu_ticks_now - cpu_ticks_last) / static_cast<float>(SDL_GetPerformanceFrequency());

        while (SDL_PollEvent(&sdl_event)) {
            wrapped_sdl_event.native = &sdl_event;

            this->process_internal_event(wrapped_sdl_event);
            this->input->on_native_event(wrapped_sdl_event);
            this->handler->on_event(wrapped_sdl_event);
        }

        if (this->async_quit_stage == 2) {
            this->mainloop = false;
            break;
        }

        this->custom_gc.on_native_update();
        this->handler->on_native_update();
        this->physic->on_native_update();
        this->input->on_native_update();
        this->driver_impl_manager->clear_buffers();
        this->physic->on_native_render();

        SDL_GL_SwapWindow(this->surfaces[0]->root);
        SDL_Delay(this->cpu_ticks_interval);
    }

    this->logger->send_info("Main-thread shutdown.");
    unsafe_thread.detach();
}

void bicudo::profile::dispatch_surface(bicudo::surface *surf) {
    // todo: multi-task surface
    if (this->surfaces.empty()) {
        this->surfaces.push_back(surf);
    } else {
        this->surfaces[0] = surf;
    }
}

bicudo::garbage_collector &bicudo::profile::get_custom_gc() {
    return this->custom_gc;
}

bicudo::logger* bicudo::profile::get_logger() {
    return this->logger;
}

void bicudo::profile::set_capped_fps(uint64_t fps) {
    fps = fps < 0 ? fps + 1 : fps;
    if (!this->surfaces.empty()) {
        this->surfaces[0]->locked_fps = fps;
        this->cpu_ticks_interval = 1000 / fps;
    }
}

void bicudo::profile::set_vsync(bool vsync) {
    if (!this->surfaces.empty()) {
        this->surfaces[0]->vsync = vsync;
        SDL_GL_SetSwapInterval(!vsync);
    }
}

bicudo::handler *bicudo::profile::get_handler() {
    return this->handler;
}

void bicudo::profile::process_internal_event(bicudo::event &event) {
    switch (event.native->type) {
        case SDL_QUIT: {
            this->async_quit_stage = 1;
            break;
        }

        case SDL_WINDOWEVENT: {
            switch (event.native->window.event) {
                case SDL_WINDOWEVENT_SIZE_CHANGED: {
                    if (!this->surfaces.empty()) {
                        auto &surface {this->surfaces[0]};
                        surface->rect.w = static_cast<float>(event.native->window.data1);
                        surface->rect.w = static_cast<float>(event.native->window.data1);
                        this->update_render_matrices();
                    }
                    break;
                }
            }
            break;
        }
    }
}

void bicudo::profile::update_render_matrices() {
    auto &surface {this->surfaces[0]};

    bicudo::orthographic(bicudo::matrix::orthographic, 0, surface->rect.w, surface->rect.h, 0);
    bicudo::immshape::matrix();
}

bool bicudo::profile::is_mainloop_running() {
    return this->mainloop && this->async_quit_stage == 0;
}

void bicudo::profile::end_mainloop() {
    this->async_quit_stage = 2;
    this->logger->send_info("Unsafe thread shutdown.");
}

bicudo::physic *bicudo::profile::get_physic() {
    return this->physic;
}

void bicudo::profile::do_unsafe_update() {
    this->physic->on_native_unsafe_update();
}

bicudo::input *bicudo::profile::get_input() {
    return this->input;
}

void bicudo::unsafe(bicudo::profile *profile) {
    while (profile->is_mainloop_running()) {
        profile->do_unsafe_update();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    profile->end_mainloop();
    profile->get_logger()->send_info("Unsafe thread destroyed.");
}
