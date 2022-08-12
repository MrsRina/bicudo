#pragma once
#include "includes/includes.h"

/**
 * Math utils.
 **/
namespace math {
    /**
     * Vector4D to directional or color.
     **/
    struct vec4 {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float w = 0.0f;

        vec4() = default;

        vec4(float x, float y, float z, float w) {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        vec4(int32_t r, int32_t g, int32_t b, int32_t a = 255) {
            this->x = static_cast<float>(r) / 255;
            this->y = static_cast<float>(g) / 255;
            this->z = static_cast<float>(b) / 255;
            this->w = static_cast<float>(a) / 255;
        }
    };

    /**
     * Vector2D to directional or color.
     **/
    struct vec2 {
        static float data[2];
        float x = 0.0f, y = 0.0f;

        vec2() = default;
        vec2(float x, float y) {
            this->x = x;
            this->y = y;
        }

        void operator -= (vec2 vec) {
            this->x -= vec.x;
            this->y -= vec.y;
        }

        vec2 operator - (vec2 vec) const {
            return {this->x - vec.x, this->y - vec.y};
        }

        vec2 operator - () const {
            return {-this->x, -this->y};
        }

        vec2 operator + (vec2 vec) const {
            return {this->x + vec.x, this->y + vec.y};
        }

        void operator += (vec2 vec) {
            this->x += vec.x;
            this->y += vec.y;
        }

        void operator *= (float n) {
            this->x *= n;
            this->y *= n;
        }

        void operator *= (int n) {
            this->x *= static_cast<float>(n);
            this->y *= static_cast<float>(n);
        }

        vec2 operator * (float n) const {
            return {this->x * n, this->y * n};
        }

        vec2 operator * (int n) const {
            return {this->x * static_cast<float>(n), this->y * static_cast<float>(n)};
        }

        float dot(vec2 vec) const {
            return (this->x * vec.x + this->y * vec.y);
        }

        float cross(vec2 vec) const {
            return (this->x * vec.y - this->y * vec.x);
        }

        float length() const {
            return sqrt(this->x * this->x + this->y * this->y);
        }

        vec2 normalize() const {
            float len = this->length();

            if (len > 0) {
                len = 1.0f / len;
            }

            return {this->x * len, this->y * len};
        }

        float distance(vec2 vec) const {
            float dx = this->x - vec.x;
            float dy = this->y - vec.y;

            return sqrt(dx * dx + dy * dy);
        }

        vec2 rotate(vec2 center, float angle) const {
            vec2 temp = center;

            float dx = this->x - center.x;
            float dy = this->y - center.y;

            center.x = dx * cos(angle) - dy * sin(angle);
            center.y = dx * sin(angle) + dy * cos(angle);

            center += temp;
            return center;
        }

        float* to_ptr() const {
            data[0] = this->x;
            data[1] = this->y;

            return data;
        }
    };

    float radians(float degress);
    float clampf(float val, float min, float max);

    int32_t clampi(int32_t val, int32_t min, int32_t max);
    void clamp_vec2(vec2 vec, float min_vec_len, float max_vec_len);

    void perspective(float* mat, float fov, float aspect, float z_near, float);
    void look_at(float* mat, glm::vec3 eye, glm::vec3 center, glm::vec3 up);
    void ortho2d(float* mat, float left, float right, float bottom, float top);

    extern math::vec2 zero2f;
};

/**
 * Used in game to get files resource.
 **/
struct game_resource {
    float data1, data2;
    void* ptr;
    std::string str;
};

/**
 * Util to make easy some actions/events and reduce code writing.
 **/
namespace util {
    /**
     * Timer stamp to help in game.
     **/
    struct timing {
        static uint64_t previous_ticks, delta, locked_delta;
        static float delta_time, locked_delta_time;

        static void start() {
            previous_ticks = SDL_GetTicks();
        }

        static bool end_if(uint32_t ms) {
            return SDL_GetTicks() - previous_ticks > ms;
        }
    };

    void log(std::string string);
    void dispatch_event(SDL_Event &sdl_event);

    /**
     * Simple load and exists.
     **/
    struct file {
        static const uint8_t TO_STRING = 0;
        static const uint8_t TO_BYTE = 1;

        static bool exists(const char* path);
        static void load(game_resource &resource, const char* path, uint8_t mode = TO_STRING);
    };

    /**
     * Texture data.
     **/
    struct texture {
        GLuint id;

        uint32_t w;
        uint32_t h;
    };

    /**
     * Color data.
     **/
    struct color {
        uint8_t r, g, b, a;

        color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) {
            this->r = red;
            this->g = green;
            this->b = blue;
            this->a = alpha;
        }

        void set(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
        void set(uint8_t red, uint8_t green, uint8_t blue);

        float redf();
        float greenf();
        float bluef();
        float alphaf();
    };

    /**
     * Enum to visibility of something.
     **/
    enum visibility {
        LOW_PRIORITY, VISIBLE
    };
};