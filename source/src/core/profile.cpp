#include "bicudo/core/profile.hpp"

void bicudo::profile::do_create() {
    this->logger = new bicudo::logger {"MAIN"};
    this->driver_impl_manager = new bicudo::driver_impl_manager {};
    this->mainloop = true;
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
        this->capped_fps = surface->locked_fps;
    }

    this->driver_impl_manager->create_opengl_context();
    static bicudo::timing cpu_reduce_ticks_timing {};
    uint64_t fps_interval {1000 / this->capped_fps};

    while (this->mainloop) {
        if (bicudo::reach(cpu_reduce_ticks_timing, fps_interval)) {
            bicudo::reset(cpu_reduce_ticks_timing);

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

bicudo::gc &bicudo::profile::get_custom_gc() {
    return this->custom_gc;
}

bicudo::logger* bicudo::profile::get_logger() {
    return this->logger;
}