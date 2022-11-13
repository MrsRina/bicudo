#include "bicudo/core/profile.hpp"
#include "bicudo/api/event/event.hpp"
#include "bicudo/impl/render/immediate_shape.hpp"

void bicudo::profile::do_create() {
    this->logger = new bicudo::logger {"MAIN"};
    this->driver_impl_manager = new bicudo::driver_impl_manager {};
    this->handler = new bicudo::handler {};
    this->mainloop = true;
    this->logger->send_info("bicudo core profile initialised!");
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
    bicudo::immediate_shape::init();

    static bicudo::timing cpu_reduce_ticks_timing {};
    SDL_Event sdl_event {};
    bicudo::event wrapped_sdl_event {};

    while (this->mainloop) {
        if (bicudo::reach(cpu_reduce_ticks_timing, this->cpu_interval_ticks) &&  bicudo::reset(cpu_reduce_ticks_timing)) {
            while (SDL_PollEvent(&sdl_event)) {
                if (sdl_event.type == SDL_QUIT) {
                    this->mainloop = false;
                    break;
                }

                wrapped_sdl_event.native = &sdl_event;
                this->handler->on_event(wrapped_sdl_event);
            }

            this->handler->on_native_update();
            this->driver_impl_manager->clear_buffers();
            SDL_GL_SwapWindow(this->surfaces[0]->root);
        }
    }
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
        this->cpu_interval_ticks = 1000 / fps;
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
