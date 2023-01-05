#ifndef BICUDO_API_UTIL_MATH_H
#define BICUDO_API_UTIL_MATH_H

#include <cmath>
#include <cfloat>

#define CMP(x, y) \
(fabsf((x) - (y))) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y)))

#define RAD2DEG(x) ((x * 57.295754f))
#define DEG2RAD(x) ((x * 0.0174533f))

namespace bicudo {
    extern float dt, unsafe_dt;

    typedef struct vec2 {
        union {
            struct {
                float x;
                float y;
            };

            float data[2];
        };

        float &operator[](unsigned char i) {
            return data[i];
        }
    } vec2;

    vec2 operator+(const vec2 &l, const vec2 &r);
    vec2 operator-(const vec2 &l, const vec2 &r);
    vec2 operator*(const vec2 &l, const vec2 &r);
    vec2 operator*(const vec2 &l, float r);

    bool operator==(const vec2 &l, const vec2 &r);
    bool operator!=(const vec2 &l, const vec2 &r);

    float dot(const vec2 &l, const vec2 &r);
    float length(const vec2 &l);

    float lengthsq(const vec2 &l);
    float distance(const vec2 &l, const vec2 &r);

    vec2 normalize(const vec2 &l);
    float angle(const vec2 &l, const vec2 &r);

    float degree(float r);
    float radians(float d);

    typedef struct vec4 {
        union {
            struct {
                float x;
                float y;
                float z;
                float w;
            };

            float data[4];
        };

        float & operator[](unsigned char i) {
            return data[i];
        }
    } vec4;
}

#endif