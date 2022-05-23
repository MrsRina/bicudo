#include "api/client/bicudo.h"
#include "api/util/util.h"

std::string game_core::client_name        = "";
std::string game_core::client_version_str = "";

void game_core::init_window() {

}

void game_core::init_context() {

}

void game_core::init_services() {

}

void game_core::init() {
    util::log("Powered by Bicudo!");
    util::log("Game start!");
    util::log("Initializing SDL2.");
    
    if (SDL_Init(SDL_INIT_VIDEO)) {

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
    
}