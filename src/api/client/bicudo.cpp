#include <ekg/ekg.hpp>
#include "instance.h"

void update_task(task* atomic_task) {
    if (atomic_task == nullptr) {
        return;
    }

    uint64_t current_ticks = SDL_GetTicks64();
    uint64_t elapsed_ticks = SDL_GetTicks64();
    uint32_t interval = 16;
    util::timing::locked_delta_time = 0.16f;

    while (!atomic_task->get_atomic_boolean_state()) {
        current_ticks = SDL_GetTicks64();

        if (current_ticks - elapsed_ticks > interval) {
            elapsed_ticks = current_ticks;

            // Call main object into this thread.
            BICUDO->mainloop_locked_update();
        }
    }

    atomic_task->set_atomic_boolean_end_state(true);
}

std::string game_core::client_name;
std::string game_core::client_version_str;

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
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetSwapInterval(1);
}

void game_core::init_context() {
    this->game_context->on_start();

    // Init static components.
    shader::init();
    draw::batch2d::init();

    this->the_camera = new camera();

    // Init EKG.
    ekg::set_font("data/fonts/microsoft-segoe-ui/SEGOEUI.TTF");
    ekg::init(this->sdl_window);
    ekg::set_font_size(56);
}

void game_core::init_services() {
    this->service_module_manager.set_name("Module");
    this->service_scene_manager.set_name("Service");
    this->service_task_manager.set_name("Task");
    this->service_physic_manager.set_name("Physic");

    // Call the first methods.
    this->service_module_manager.on_start();
    this->service_scene_manager.on_start();
    this->service_task_manager.on_start();
    this->service_physic_manager.on_start();
}

void game_core::refresh() {
    SDL_DisplayMode sdl_display_mode;
    SDL_GetDisplayMode(0, 0, &sdl_display_mode);

    game_core::screen_width = sdl_display_mode.w;
    game_core::screen_height = sdl_display_mode.h;

    // There is no setting manager yet.
    this->interval = 1000 / 60;
}

void game_core::init() {
    util::log("Powered by Bicudo!");
    util::log("Game invoke!");
    util::log("Initializing SDL2.");
    util::log("Initializing OpenGL.");
    util::log("Initializing window, context and services.");

    this->init_window();
    this->init_services();
    this->init_context();
}

void game_core::quit() {
    bicudo::set_guiscreen(nullptr);
    bicudo::set_scene(nullptr);

    this->service_module_manager.on_end();
    this->service_scene_manager.on_end();

    util::log("Game quit!");
}

void game_core::mainloop() {
    this->current_ticks = SDL_GetTicks64();
    this->previous_ticks = SDL_GetTicks64();

    this->is_stopping_run = false;
    this->is_running = true;

    // The concurrent delta time for get the FPS.
    uint64_t concurrent_dt = SDL_GetTicks64();

    // Initialize the locked task.
    std::thread thread_locked_update(update_task, bicudo::create_task("locked-update"));

    /*
     * The game mainloop.
     */
    while (this->is_running) {
        // Get the difference from previous tick.
        this->current_ticks = SDL_GetTicks64() - this->previous_ticks;

        // If the difference is not less than interval tick,
        // we update and render this moment tick.
        if (this->current_ticks > this->interval) {
            SDL_Event sdl_event;

            // Update input and events unsynchronized.
            while (SDL_PollEvent(&sdl_event)) {
                ekg::poll_event(sdl_event);
                BICUDO->on_event(sdl_event);
            }

            this->previous_ticks = SDL_GetTicks64();
            concurrent_dt += this->current_ticks;

            util::timing::delta += this->current_ticks;
            util::timing::delta_time = static_cast<float>(this->current_ticks) / 100.0f;

            this->on_update();
            this->on_render();
            this->elapsed_frames++;

            if (concurrent_dt > 1000)  {
                this->fps = this->elapsed_frames;
                this->elapsed_frames = 0;
                concurrent_dt = 0;
            }

            // Swap buffers and flip.
            SDL_GL_SwapWindow(this->sdl_window);
        }
    }

    thread_locked_update.join();
}

uint64_t game_core::get_fps() {
    return this->fps;
}

void game_core::on_event(SDL_Event &sdl_event) {
    switch (sdl_event.type) {
        case SDL_QUIT: {
            // Calling on_end service task method automatically put off the locked-update task (multi-thread)
            // and others tasks (threads).
            if (!this->is_stopping_run) {
                this->is_stopping_run = true;
                this->service_task_manager.on_end();

                util::log("Starting game shutdown!");
            }

            break;
        }

        case SDL_WINDOWEVENT: {
            if (sdl_event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                int32_t w, h;
                SDL_GetWindowSize(this->sdl_window, &w, &h);

                screen_width = w;
                screen_height = h;
            
                glViewport(0, 0, screen_width, screen_height);
            }

            break;
        }
    }

    this->service_scene_manager.on_event(sdl_event);
    this->service_module_manager.on_event(sdl_event);
    this->service_physic_manager.on_event(sdl_event);

    if (this->guiscreen != nullptr) {
        this->guiscreen->on_event(sdl_event);
    }
}

void game_core::mainloop_locked_update() {
    this->service_scene_manager.on_locked_update();
    this->service_module_manager.on_locked_update();
    this->service_physic_manager.on_locked_update();

    if (this->guiscreen != nullptr) {
        this->guiscreen->on_locked_update();
    }
}

void game_core::on_update() {
    if (this->is_stopping_run) {
        this->is_running = !bicudo::is_task_done("locked-update");
    }

    this->game_context->on_update();
    this->service_task_manager.on_update();
    this->service_scene_manager.on_update();
    this->service_module_manager.on_update();
    this->service_physic_manager.on_update();

    if (this->guiscreen != nullptr) {
        this->guiscreen->on_update();
    }

    // Update EKG.
    ekg::update(util::timing::delta_time);
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

    ekg::render();
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

physic_service &game_core::get_physic_manager() {
    return this->service_physic_manager;
}

void game_core::set_game_context(context* raw_game_context) {
    this->game_context = raw_game_context;
}

context* game_core::get_game_context() {
    return this->game_context;
}

camera *game_core::get_camera() {
    return this->the_camera;
}

SDL_Window *game_core::get_sdl_win() {
    return this->sdl_window;
}
