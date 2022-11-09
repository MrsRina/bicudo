#include "bicudo/core/profile.hpp"

void bicudo::profile::do_create() {
    this->logger = new bicudo::logger {"MAIN"};
    this->mainloop = true;
}

void bicudo::profile::do_destroy() {
}

void bicudo::profile::do_loop() {
    if (this->surfaces.empty()) {
        this->logger.send_warning("There is no surface, can not mainloop.");
        return;
    }

    // setup opengl version

    for (bicudo::surface* &surface : this->surfaces) {
        surface->on_create();
    }

    // opengl init glew context

    static bicudo::timing cpu_reduce_ticks_timing {};
    uint64_t fps_interval {1000 / };

    while (this->mainloop) {
        if (bicudo::reach(cpu_reduce_ticks_timing, ))
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

bicudo::gc &bicudo::get_custom_garbage_collector() {
    return this->custom_gc;
}

bicudo::logger* bicudo::get_logger() {
    return this->logger;
}