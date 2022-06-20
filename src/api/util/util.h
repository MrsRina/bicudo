#pragma once
#include "includes/includes.h"

/**
 * Math utils.
 **/
namespace math {
    void ortho2d(float* mat, float left, float right, float bottom, float top);

    /**
     * Vector to directional or color.
     **/
    struct vec2 {
        float x = 0.0f, y = 0.0f;

        vec2() {}
        vec2(float x, float y) {
            this->x = x;
            this->y = y;
        }

        void operator -= (vec2 vec) {
            this->x -= vec.x;
            this->y -= vec.y;
        }

        vec2 operator - (vec2 vec) {
            return vec2(this->x - vec.x, this->y - vec.y);
        }

        vec2 operator - () {
            return vec2(-this->x, -this->y);
        }

        vec2 operator + (vec2 vec) {
            return vec2(this->x + vec.x, this->y + vec.y);
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
            this->x *= n;
            this->y *= n;
        }

        vec2 operator * (float n) {
            return vec2(this->x * n, this->y * n);
        }

        vec2 operator * (int n) {
            return vec2(this->x * n, this->y * n);
        }

        float dot(vec2 vec) {
            return (this->x * vec.x + this->y * vec.y);
        }

        float cross(vec2 vec) {
            return (this->x * vec.x - this->y * vec.y);
        }

        float length() {
            return sqrt(this->x * this->x + this->y * this->y);
        }

        vec2 normalize() {
            float len = this->length();

            if (len > 0) {
                len = 1.0f / len;
            }

            return vec2(this->x * len, this->y * len);
        }

        float distance(vec2 vec) {
            float dx = this->x - vec.x;
            float dy = this->y - vec.y;

            return sqrt(dx * dx + dy * dy);
        }

        vec2 rotate(vec2 center, float angle) {
            vec2 temp = center;

            float dx = this->x - center.x;
            float dy = this->y - center.y;

            center.x = dx * cos(angle) - dy * sin(angle);
            center.y = dx * sin(angle) + dy * cos(angle);

            center += temp;
            return center;
        }
    };
};

/**
 * Timer stamp to help in game.
 **/
struct timer_stamp {
    uint64_t previous_ticks, delta, locked_delta;
    float delta_time, locked_delta_time;

    void start();
    bool end_if(uint32_t ms);
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
struct util {
    static timer_stamp* timing;

    static bool debug_scene;
    static bool debug_module;

    static void log(std::string string);

    /**
     * Simple load and exists.
     **/
    struct file {
        static const uint8_t TO_STRING = 0;
        static const uint8_t TO_BYTE = 1;

        static bool exists(const char* path);
        static game_resource load(const char* path, uint8_t mode = TO_STRING);
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