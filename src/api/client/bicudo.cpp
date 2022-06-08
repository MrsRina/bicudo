#include "bicudo.h"
#include "api/util/util.h"
#include "instance.h"

void update_task(task* raw_task) {
    uint64_t previous_ticks = SDL_GetTicks();
    uint64_t current_ticks = SDL_GetTicks();
    uint8_t interval = 16;
    uint16_t delta = 0;

    while (!raw_task->get_atomic_boolean_state()) {
        current_ticks = SDL_GetTicks() - previous_ticks;

        if (current_ticks > interval) {
            previous_ticks = SDL_GetTicks();
            delta += interval;

            // Call main object into this thread.
            BICUDO->set_locked_delta(delta);
            BICUDO->mainloop_locked_update();

            if (delta > 1000) {
                delta = 0;
            }
        }
    }
}

std::string game_core::client_name        = "";
std::string game_core::client_version_str = "";

uint16_t game_core::screen_width  = 800;
uint16_t game_core::screen_height = 600;

int16_t game_core::internal_flag = 0;

void game_core::edit_client_details(const std::string &name, const std::string &ver_str) {
    game_core::client_name = name;
    game_core::client_version_str = ver_str;
}

void game_core::exception() {
    game_core::internal_flag = -1;
}

void game_core::init_window() {
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        game_core::exception();
    }

    const char* name = game_core::client_name.c_str(); 
    this->sdl_window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game_core::screen_width, game_core::screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    // As you can see, we are using OpenGL 3, "minimum supported version" is 3.
    this->sdl_gl_context = SDL_GL_CreateContext(this->sdl_window);

    // Init glew.
    glewExperimental = true;

    if (glewInit()) {
        game_core::exception();
    }

    // Set default OPENGL attributs to works with SDL2.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void game_core::init_context() {

}

void game_core::init_services() {
    // Call the first methods.
    this->service_module_manager.on_start();
    this->service_scene_manager.on_start();
    this->service_task_manager.on_start();
}

void game_core::refresh() {
    SDL_DisplayMode sdl_display_mode;
    SDL_GetDisplayMode(0, 0, &sdl_display_mode);

    game_core::screen_width = sdl_display_mode.w;
    game_core::screen_height = sdl_display_mode.h;

    // We still not have a setting manager to here, load a fps, but I want to use 60.
    this->interval = 1000 / 60;
}

void game_core::refresh_features() {
    for (int i = 0; i < this->buffer_update_iterator; i++) {
        auto features = this->buffer_update[i];
        
        if (features != nullptr && !features->is_alive()) {
            delete features;
        }
    }

    // Swap buffer after safe delete all.
    this->refresh_feature_buffers();
}

void game_core::refresh_feature_buffers() {
    std::array<ifeature*, FEATURE_BUFFER_LIMIT> buffer_copy;
    uint32_t buffer_copy_iterator = 0;

    // Clean the render buffer.
    this->buffer_render.fill(0);
    this->buffer_render_iterator = 0;

    // Pass the concurrent buffers to copy and visual buffer.
    for (ifeature* &features : this->buffer_update) {
        if (features != nullptr) {
            buffer_copy[buffer_copy_iterator++] = features;

            if (features->get_visibility() == util::visibility::VISIBLE && features->is_alive()) {
                this->buffer_render[this->buffer_render_iterator++] = features;
            }
        }
    }

    // Swap update buffer to copy.
    this->buffer_update = buffer_copy;
    this->buffer_update_iterator = buffer_copy_iterator;
}

void game_core::init() {
    util::log("Powered by Bicudo!");
    util::log("Game start!");
    util::log("Initializing SDL2.");
    util::log("Initializing OpenGL.");
    util::log("Initializing window, context and services.");

    this->init_window();
    this->init_services();
    this->init_context();
    this->refresh_feature_buffers();
}

void game_core::quit() {
    this->service_module_manager.on_end();
    this->service_scene_manager.on_end();
    this->service_task_manager.on_end();

    util::log("Game quit!");
}

void game_core::mainloop() {
    SDL_Event sdl_event;

    this->current_ticks = SDL_GetTicks();
    this->previous_ticks = SDL_GetTicks();
    this->is_running = true;

    // Initialize the locked task.
    //this->service_task_manager->start("locked-update", update_task, 0);

    while (this->is_running) {
        // Update input and events unsynchronized.
        while (SDL_PollEvent(&sdl_event)) {
            this->on_event(sdl_event);
        }

        // Get the difference from previous tick.
        this->current_ticks = SDL_GetTicks() - this->previous_ticks;

        // If the difference is not less than interval tick,
        // we update and render this moment tick.
        if (this->current_ticks > this->interval) {
            this->previous_ticks = SDL_GetTicks();
            this->delta += this->current_ticks;
    
            this->on_update();
            this->on_render();
            this->elapsed_frames++;

            // Swap buffers and flip.
            SDL_GL_SwapWindow(this->sdl_window);
        
            // Reset delta and get the game fps.
            if (this->delta > 1000) {
                this->fps = this->elapsed_frames;
                this->elapsed_frames = 0;
                this->delta = 0;
            }
        }
    }
}

void game_core::set_locked_delta(uint64_t delta_val) {
    this->locked_delta = delta_val;
}

uint64_t game_core::get_fps() {
    return this->fps;
}

ifeature* game_core::get_feature_by_id(uint32_t feature_id) {
    for (ifeature* &features : this->buffer_update) {
        if (features != nullptr && features->get_feature_id() == feature_id) {
            return features;
        }
    }

    return NULL;
}

void game_core::registry_feature(ifeature* feature) {
    if (feature == NULL) {
        return;
    }

    this->previous_feature_id_used++;
    this->buffer_update[this->buffer_update_iterator++] = feature;

    if (feature->get_visibility() == util::visibility::VISIBLE) {
        this->buffer_render[this->buffer_render_iterator++] = feature;
    }

    feature->set_feature_id(this->previous_feature_id_used);
}

void game_core::remove_feature(uint32_t feature_id) {
    ifeature* feature = this->get_feature_by_id(feature_id);

    if (feature != NULL) {
        feature->set_alive_state(false);
        this->should_refresh_features = true;
    }
}

void game_core::on_event(SDL_Event &sdl_event) {
    switch (sdl_event.type) {
        case SDL_QUIT: {
            this->is_running = false;
            util::log("Starting game shutdown!");
            break;
        }

        default: {
            for (uint32_t i = 0; i < this->buffer_update_iterator; i++) {
                ifeature* features = this->buffer_update[i];

                if (features != nullptr) {
                    features->on_event(sdl_event);
                }
            }

            break;
        }
    }
}

void game_core::mainloop_locked_update() {
    for (uint32_t i = 0; i < this->buffer_update_iterator; i++) {
        ifeature* features = this->buffer_update[i];

        if (features != nullptr) {
            features->on_locked_update(this->locked_delta);
        }
    }
}

void game_core::on_update() {
    if (this->should_refresh_features) {
        this->refresh_features();
        this->should_refresh_features = false;
    }

    for (uint32_t i = 0; i < this->buffer_update_iterator; i++) {
        ifeature* features = this->buffer_update[i];

        if (features != nullptr) {
            features->on_update(this->delta);
        }
    }
}

void game_core::on_render() {
    glViewport(0, 0, this->screen_width, this->screen_width);

    glClearColor(0.5, 0.5, 0.5, 0.5);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (uint32_t i = 0; i < this->buffer_render_iterator; i++) {
        ifeature* features = this->buffer_render[i];

        if (features != nullptr) {
            features->on_render(this->render_time);
        }
    }
}

module_service &game_core::get_module_manager() {
    return this->service_module_manager;
}

scene_service &game_core::get_scene_manager() {
    return this->service_scene_manager;
}

task_service &game_core::get_task_manager() {
    return this->service_task_manager;
}