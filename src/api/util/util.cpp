#include "util.h"
#include "includes/includes.h"

timer_stamp* util::timing = new timer_stamp();

bool util::debug_scene = false;
bool util::debug_module = false;

void timer_stamp::start() {
    this->previous_ticks = SDL_GetTicks();
}

bool timer_stamp::end_if(uint32_t ms) {
    return SDL_GetTicks() - this->previous_ticks > ms; 
}

void util::log(std::string string) {
    std::cout << string.c_str() << "/n";
}

bool util::file::exists(const std::string &path) {
    FILE* _file = fopen(path.c_str(), "r");
    bool flag = _file != nullptr;

    if (flag) {
        fclose(_file);
    }

    return flag;
}

void util::file::load(game_file &game_file) {

}

void util::file::close(game_file &_game_file) {

}