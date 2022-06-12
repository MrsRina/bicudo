#include "bicudo.h"
#include "api/util/util.h"
#include "instance.h"
#include "api/render/shader.h"
#include "api/render/tessellator.h"

void update_task(task* atomic_task) {
    if (atomic_task == nullptr) {
        return;
    }

    uint64_t previous_ticks = SDL_GetTicks64();
    uint64_t current_ticks = SDL_GetTicks64();
    uint8_t interval = 16;

    while (!atomic_task->get_atomic_boolean_state()) {
        if (atomic_task == nullptr) {
            break;
        }

        current_ticks = SDL_GetTicks64() - previous_ticks;

        if (current_ticks > interval) {
            previous_ticks = SDL_GetTicks64();

            // Set the locked dt.
            util::timing->locked_delta_time = current_ticks;

            // Call main object into this thread.
            BICUDO->mainloop_locked_update();
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

void game_core::display(gui* new_gui) {
    BICUDO->set_guiscreen(new_gui);
}

void game_core::set_guiscreen(gui* new_gui) {
    if (this->guiscreen != nullptr && new_gui != nullptr && this->guiscreen->get_name() == new_gui->get_name()) {
        delete new_gui;
        return;
    }

    bool phase_remove_gui = (new_gui == nullptr && this->guiscreen != nullptr) ||
                            (new_gui != nullptr && this->guiscreen != nullptr && this->guiscreen->get_name() != new_gui->get_name());

    if (phase_remove_gui) {
        this->guiscreen->on_end();
            
        delete this->guiscreen;
        this->guiscreen = nullptr;
    }

    if (new_gui != nullptr && phase_remove_gui) {
        this->guiscreen = new_gui;
        this->guiscreen->on_start();
    }
}

gui* game_core::get_guiscreen() {
    return this->guiscreen;
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

    // Set default OpenGL attributs to works with SDL2.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
}

void game_core::init_context() {
    this->game_context->on_start();

    // Init static components.
    shader::init();
    draw::immediate::init();
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

void game_core::init() {
    util::log("Powered by Bicudo!");
    util::log("Game start!");
    util::log("Initializing SDL2.");
    util::log("Initializing OpenGL.");
    util::log("Initializing window, context and services.");

    this->init_window();
    this->init_services();
    this->init_context();
}

void game_core::quit() {
    // Set gui to none.
    game_core::display(nullptr);

    this->service_module_manager.on_end();
    this->service_scene_manager.on_end();
    this->service_task_manager.on_end();

    util::log("Game quit!");
}

void game_core::mainloop() {
    SDL_Event sdl_event;

    this->current_ticks = SDL_GetTicks64();
    this->previous_ticks = SDL_GetTicks64();
    this->is_running = true;

    // The concurrent delta time for get the FPS.
    uint64_t concurrent_dt = SDL_GetTicks64();

    // Initialize the locked task.
    std::thread thread_locked_update(update_task, task_service::run("locked-update"));

    /*
     * The game mainloop.
     */
    while (this->is_running) {
        // Update input and events unsynchronized.
        while (SDL_PollEvent(&sdl_event)) {
            this->on_event(sdl_event);
        }

        // Get the difference from previous tick.
        this->current_ticks = SDL_GetTicks64() - this->previous_ticks;

        // If the difference is not less than interval tick,
        // we update and render this moment tick.
        if (this->current_ticks > this->interval) {
            this->previous_ticks = SDL_GetTicks64();
            concurrent_dt += current_ticks;
    
            this->on_update();
            this->on_render();
            this->elapsed_frames++;

            // Swap buffers and flip.
            SDL_GL_SwapWindow(this->sdl_window);
        
            // Reset delta and get the game fps.
            if (concurrent_dt > 1000) {
                this->fps = this->elapsed_frames;
                this->elapsed_frames = 0;
                concurrent_dt = 0;
            }
        }
    }
}

uint64_t game_core::get_fps() {
    return this->fps;
}

void game_core::on_event(SDL_Event &sdl_event) {
    switch (sdl_event.type) {
        case SDL_QUIT: {
            this->is_running = false;
            util::log("Starting game shutdown!");
            break;
        }

        default: {
            break;
        }
    }
}

void game_core::mainloop_locked_update() {
    this->service_scene_manager.on_locked_update();
    this->service_module_manager.on_locked_update();

    if (this->guiscreen != nullptr) {
        this->guiscreen->on_locked_update();
    }
}

void game_core::on_update() {
    this->game_context->on_update();
    this->service_scene_manager.on_update();
    this->service_module_manager.on_update();

    if (this->guiscreen != nullptr) {
        this->guiscreen->on_update();
    }
}

void game_core::on_render() {
    shader::context();

    glClearColor(0.5, 0.5, 0.5, 0.5);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->service_scene_manager.on_render();
    this->service_module_manager.on_render();

    if (this->guiscreen != nullptr) {
        this->guiscreen->on_render();
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

void game_core::set_game_context(context* raw_game_context) {
    this->game_context = raw_game_context;
}

context* game_core::get_game_context() {
    return this->game_context;
}