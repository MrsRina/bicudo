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
    string = "[MAIN] " + string;
    std::cout << string.c_str() << "\n";
}

void util::color::set(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    this->r = red;
    this->g = green;
    this->b = blue;
    this->a = alpha;
}

void util::color::set(uint8_t red, uint8_t green, uint8_t blue) {
    this->r = red;
    this->g = green;
    this->b = blue;
}

float util::color::redf() {
    return (float) this->r / 255.0;
}

float util::color::greenf() {
    return (float) this->g / 255.0;
}

float util::color::bluef() {
    return (float) this->b / 255.0;
}

float util::color::alphaf() {
    return (float) this->a / 255.0;
}

bool util::file::exists(const std::string &path) {
    FILE* f = fopen(path.c_str(), "r");
    bool flag = _file != nullptr;

    if (flag) {
        fclose(f);
    }

    return flag;
}

void* util::file::load(const char* path, uint8_t mode) {
    if (mode == util::file::TO_STRING) {
        std::ifstream ifs(path);
        std::string string_builder;

        if (ifs.is_open()) {
            std::string string_buffer;

            while (getline(ifs, string_buffer)) {
                strning_builder += "\n" + string_buffer;
            }

            ifs.close();

            return &string_builder;
        }
    } else if (mode == util::file::TO_BYTE) {

    }

    return nullptr;
}