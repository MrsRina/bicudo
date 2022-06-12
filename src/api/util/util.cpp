#include "util.h"

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

bool util::file::exists(const char* path) {
    FILE* f = fopen(path, "r");
    bool flag = f != nullptr;

    if (flag) {
        fclose(f);
    }

    return flag;
}

game_resource util::file::load(const char* path, uint8_t mode) {
    game_resource resource;

    if (mode == util::file::TO_STRING) {
        std::ifstream ifs(path);
        std::string string_builder;

        if (ifs.is_open()) {
            std::string string_buffer;

            while (getline(ifs, string_buffer)) {
                string_builder += "\n" + string_buffer;
            }

            ifs.close();
            resource.str = string_builder;
        }
    } else if (mode == util::file::TO_BYTE) {

    }

    return resource;
}

void util::math::ortho2d(float* mat, float left, float right, float bottom, float top) {
    const float zNear = -1.0f;
    const float zFar = 1.0f;
    const float inv_z = 1.0f / (zFar - zNear);
    const float inv_y = 1.0f / (top - bottom);
    const float inv_x = 1.0f / (right - left);

    // first column
    *mat++ = (2.0f * inv_x);
    *mat++ = (0.0f);
    *mat++ = (0.0f);
    *mat++ = (0.0f);

    // second
    *mat++ = (0.0f);
    *mat++ = (2.0 * inv_y);
    *mat++ = (0.0f);
    *mat++ = (0.0f);

    // third
    *mat++ = (0.0f);
    *mat++ = (0.0f);
    *mat++ = (-2.0f * inv_z);
    *mat++ = (0.0f);

    // fourth
    *mat++ = (-(right + left) * inv_x);
    *mat++ = (-(top + bottom) * inv_y);
    *mat++ = (-(zFar + zNear) * inv_z);
    *mat++ = (1.0f);
}