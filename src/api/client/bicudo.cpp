#include "bicudo.h"
#include "api/util/util.h"

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
    const char* name = game_core::client_name.c_str(); 
    this->sdl_window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game_core::screen_width, game_core::screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    
    // Set default OPENGL attributs to works with SDL2.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // As you can see, we are using OpenGL 4, "minimum supported version" is 3.
    
    this->sdl_gl_context = SDL_GL_CreateContext(this->sdl_window);
}

void game_core::init_context() {

}

void game_core::init_services() {

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
    
    if (SDL_Init(SDL_INIT_VIDEO)) {
        game_core::exception();
    }

    util::log("Initializing OpenGL.");

    glewExperimental = true;

    if (glewInit()) {
        game_core::exception();
    }

    util::log("Initializing window, context and services.");

    this->init_window();
    this->init_context();
    this->init_services();
}

void game_core::quit() {
    util::log("Game quit!");
}

void game_core::mainloop() {
    SDL_Event sdl_event;

    this->current_ticks = SDL_GetTicks();
    this->previous_ticks = SDL_GetTicks();
    this->is_running = true;

    while (this->is_running) {
        while (SDL_PollEvent(&sdl_event)) {
            this->on_event(sdl_event);
        }

        this->current_ticks = SDL_GetTicks() - this->previous_ticks;

        if (this->current_ticks > this->interval) {
            this->previous_ticks = SDL_GetTicks();
            this->delta += this->current_ticks;

            this->on_update();
            this->on_render();

            this->elapsed_frames++;

            // Swap buffers and flip.
            SDL_GL_SwapWindow(this->sdl_window);
        }

        if (this->delta > 1000) {
            this->fps = this->elapsed_frames;
            this->elapsed_frames = 0;
            this->delta = 0;
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
    }
}

void game_core::on_update() {
    
}

void game_core::on_render() {
    glClearColor(0.5, 0.5, 0.5, 0.5);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}