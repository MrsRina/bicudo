#pragma once
#include "includes/includes.h"

/**
 * Math utils.
 **/
namespace math {
    /**
     * Vector3D to directional or color.
     **/
    struct vec3 {
        float x = 0.0f, y = 0.0f, z = 0.0f;

        vec3() {}
        vec3(float x, float y, float z = 0.0f) {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        void operator -= (vec3 vec) {
            this->x -= vec.x;
            this->y -= vec.y;
            this->z -= vec.z;
        }

        vec3 operator - (vec3 vec) {
            return vec3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
        }

        vec3 operator - () {
            return vec3(-this->x, -this->y, -this->z);
        }

        vec3 operator + (vec3 vec) {
            return vec3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
        }

        void operator += (vec3 vec) {
            this->x += vec.x;
            this->y += vec.y;
            this->z += vec.z;
        }

        void operator *= (float n) {
            this->x *= n;
            this->y *= n;
            this->z *= n;
        }

        void operator *= (int n) {
            this->x *= n;
            this->y *= n;
            this->z *= n;
        }

        vec3 operator * (float n) {
            return vec3(this->x * n, this->y * n, this->z * n);
        }

        vec3 operator * (int n) {
            return vec3(this->x * n, this->y * n, this->z * n);
        }

        double dot(vec3 vec) {
            return (this->x * vec.x + this->y * vec.y + this->z * vec.z);
        }

        vec3 cross(vec3 vec) {
            return vec3(
                this->y * vec.z - this->z * vec.y,
                this->z * vec.x - this->x * vec.z,
                this->x * vec.y - this->y * vec.x
            );
        }

        float length() {
            return sqrt(this->x * this->x + this->y * this->y + this->y * this->y);
        }

        vec3 normalize() {
            float len = this->length();

            if (len > 0) {
                len = 1.0f / len;
            }

            return vec3(this->x * len, this->y * len, this->z * len);
        }

        float distance(vec3 vec) {
            float dx = this->x - vec.x;
            float dy = this->y - vec.y;
            float dz = this->z - vec.z;

            return sqrt(dx * dx + dy * dy + dz * dz);
        }
    };

    /**
     * Vector2D to directional or color.
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
            return (this->x * vec.y - this->y * vec.x);
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

    struct mat4 {
    protected:
        // 0, 1, 2, 3
        // 4, 5, 6, 7
        // 8, 9, 10, 11
        // 12, 13, 14, 15
        float matrix[16];
    public:
        mat4(float z) {
            this->matrix[3] = z;
            this->matrix[7] = z;
            this->matrix[11] = z;
            this->matrix[15] = z;
        }
    };

    struct mat3 {
    protected:
        float matrix[9];
    public:
        mat3(float z) {
            uint8_t i = 1;

            i += 3;
            this->matrix[i - 1] = z;

            i += 3;
            this->matrix[i - 1] = z;

            i += 3;
            this->matrix[i - 1] = z;
        }
    };

    struct mat2 {
    protected:
        float matrix[4];
    public:
        mat2(float z) {
            this->matrix[1] = z;
            this->matrix[3] = z;
        }
    };

    float clampf(float val, float min, float max);
    int32_t clampi(int32_t val, int32_t min, int32_t max);
    void clamp_vec2(vec2 vec, float min_vec_len, float max_vec_len);

    float radians(float degress);

    void perspective(float* mat, float fov, float aspect, float z_near, float);
    void look_at(float* mat, vec3 eye, vec3 center, vec3 up);
    void ortho2d(float* mat, float left, float right, float bottom, float top);
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