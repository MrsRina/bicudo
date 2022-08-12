#include "util.h"

uint64_t util::timing::previous_ticks = 0;
uint64_t util::timing::delta = 0;
uint64_t util::timing::locked_delta = 0;

float util::timing::delta_time = 0.0f;
float util::timing::locked_delta_time = 0.0f;

math::vec2 math::zero2f = math::vec2(0, 0);

void util::log(std::string string) {
    string = "[MAIN] " + string;
    std::cout << string.c_str() << "\n";
}

void util::dispatch_event(SDL_Event &sdl_event) {
    sdl_event.type = SDL_USEREVENT;
    SDL_PushEvent(&sdl_event);
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

void util::file::load(game_resource &resource, const char* path, uint8_t mode) {
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
}

float math::radians(float degress) {
    return degress * (M_PI / 180.0f);
}

void math::perspective(float* mat, float fov, float aspect, float z_near, float z_far) {
    fov = math::radians(fov);
    float f = tan(fov / 2.0f);
    uint8_t i = 0;

    mat[i++] = (1.0f / (aspect * f));
    mat[i++] = (0.0f);
    mat[i++] = (0.0f);
    mat[i++] = (0.0f);

    mat[i++] = (0.0f);
    mat[i++] = (1.0f / f);
    mat[i++] = (0.0f);
    mat[i++] = (0.0f);

    mat[i++] = (0.0f);
    mat[i++] = (0.0f);
    mat[i++] = (-(z_far + z_near) / (z_far - z_near));
    mat[i++] = (-1.0f);

    mat[i++] = (0.0f);
    mat[i++] = (0.0f);
    mat[i++] = (-(2.0f * z_far * z_near) / (z_far - z_near));
    mat[i++] = (0.0f);
}

void math::look_at(float* mat, glm::vec3 eye, glm::vec3 center, glm::vec3 up) {
}

void math::ortho2d(float* mat, float left, float right, float bottom, float top) {
    const float zNear = -1.0f;
    const float zFar = 1.0f;
    const float inv_z = 1.0f / (zFar - zNear);
    const float inv_y = 1.0f / (top - bottom);
    const float inv_x = 1.0f / (right - left);

    uint8_t i = 0;

    mat[i++] = (2.0f * inv_x);
    mat[i++] = (0.0f);
    mat[i++] = (0.0f);
    mat[i++] = (0.0f);

    mat[i++] = (0.0f);
    mat[i++] = (2.0 * inv_y);
    mat[i++] = (0.0f);
    mat[i++] = (0.0f);

    mat[i++] = (0.0f);
    mat[i++] = (0.0f);
    mat[i++] = (-2.0f * inv_z);
    mat[i++] = (0.0f);

    mat[i++] = (-(right + left) * inv_x);
    mat[i++] = (-(top + bottom) * inv_y);
    mat[i++] = (-(zFar + zNear) * inv_z);
    mat[i++] = (1.0f);
}

float math::clampf(float val, float min, float max) {
    return val < min ? min : val > max ? max : val;
}

int32_t math::clampi(int32_t val, int32_t min, int32_t max) {
    return val < min ? min : val > max ? max : val;;
}

void math::clamp_vec2(math::vec2 vec, float min_vec_len, float max_vec_len) {

}
