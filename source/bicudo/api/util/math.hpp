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

    /* Vectors segment. */

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

        float &operator[](unsigned char i) {
            return data[i];
        }
    } vec4;

    /* Matrices segment. */

    typedef struct mat2 {
        union {
            struct {
                float _11, _12;
                float _21, _22;
            };
        
            float data[4];
        };
    
        inline mat2(float identity = 0.0f) {
            _11 = _22 = identity;
            _12 = _21 = 0.0f;
        }

        inline mat2(float f11, float f12,
                    float f21, float f22) {
            _11 = f11; _12 = f12;
            _21 = f21; _22 = f22;
        }

        inline float *operator[](unsigned char i) {
            return &(data[i * 2]);
        }
    } mat2;

    typedef struct mat3 {
        union {
            struct {
                float _11, _12, _13;
                float _21, _22, _23;
                float _31, _32, _33;
            };

            float data[9];
        };

        inline mat3(float identity = 0.0f) {
            _11 = _22 = _33 = identity;
            _12 = _13 = _21 = 0.0f;
            _23 = _32 = _32 = 0.0f;
        }

        inline mat3(float f11, float f12, float f13,
                    float f21, float f22, float f23,
                    float f31, float f32, float f33) {
            _11 = f11; _12 = f12; _13 = f13;
            _21 = f21; _22 = f22; _23 = f23;
            _31 = f31; _32 = f32; _33 = f33;
        }

        inline float *operator[](unsigned char i) {
            return &(data[i * 3]);
        }
    } mat3;

    typedef struct mat4 {
        union {
            struct {
                float _11, _12, _13, _14;
                float _21, _22, _23, _24;
                float _31, _32, _33, _34;
                float _41, _42, _43, _44;
            };

            float data[16];
        };

        inline mat4(float identity = 0.0f) {
            _11 = _22 = _33 = _44 = identity;
            _12 = _13 = _14 = _21 = 0.0f;
            _23 = _24 = _31 = _32 = 0.0f;
            _34 = _41 = _42 = _43 = 0.0f;
        }

        inline mat4(float f11, float f12, float f13, float f14,
                    float f21, float f22, float f23, float f24,
                    float f31, float f32, float f33, float f34,
                    float f41, float f42, float f43, float f44) {
            _11 = f11; _12 = f12; _13 = f13; _14 = f14;
            _21 = f21; _22 = f22; _23 = f23; _24 = f24;
            _31 = f31; _32 = f32; _33 = f33; _34 = f34;
            _41 = f41; _41 = f42; _43 = f43; _44 = f44;
        }

        inline float *operator[](unsigned char i) {
            return &(data[i * 4]);
        }
    } mat4;

    mat2 operator*(const mat2 &m, float scalar);
    mat3 operator*(const mat3 &m, float scalar);
    mat4 operator*(const mat4 &m, float scalar);

    bool multiply(float *p_out, const float *p_m1, unsigned char m1_rows, unsigned char m1_cols, const float *p_m2, unsigned char m2_rows, unsigned char m2_cols);
    mat2 operator*(const mat2 &m1, const mat2 &m2);
    mat3 operator*(const mat3 &m1, const mat3 &m2);
    mat4 operator*(const mat4 &m1, const mat4 &m2);

    void transpose(const float *p_src, float *p_dst, unsigned char rows, unsigned char cols);
    mat2 transpose(const mat2 &m);
    mat3 transpose(const mat3 &m);
    mat4 transpose(const mat4 &m);

    float determinant(const mat2 &m);
    mat2 cut(const mat3 &m, unsigned char row, unsigned char col);
    mat2 minor(const mat2 &m);
    mat3 minor(const mat3 &m);

    void cofactor(float *p_out, const float *p_minor, unsigned char rows, unsigned char cols);
    mat3 cofactor(const bicudo::mat3 &m);
    mat2 cofactor(const bicudo::mat2 &m);

    float determinant(const mat3 &m);
}

#endif