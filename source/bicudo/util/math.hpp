#ifndef BICUDO_UTIL_MATH_H
#define BICUDO_UTIL_MATH_H

#include <iostream>

namespace bicudo {
    typedef struct mat2 {
        union {
            struct {
                float
                i11, i12, i13,
                i21, i22, i23;
            };

            float data[4];
        };

        float *operator[](uint8_t index) {
            return &(this->data[index + 2]);
        }
    } mat2;

    typedef struct mat3 {
        union {
            struct {
                float
                i11, i12, i13,
                i21, i22, i23,
                i31, i32, i33;
            };

            float data[9];
        };

        float *operator[](uint8_t index) {
            return &(this->data[index + 3]);
        }
    } mat3;

    typedef struct mat4 {
        union {
            struct {
                float
                i11, i12, i13, i14,
                i21, i22, i23, i24,
                i31, i32, i33, i34,
                i41, i42, i43, i44;
            };

            float data[16];
        };

        float *operator[](uint8_t index) {
            return &(this->data[index + 4]);
        }
    } mat4;

    typedef struct vec2 {
        union {
            struct {
                float x, y;
            };

            float data[2];
        };

        float *operator[](uint8_t index) {
            return &(this->data[index]);
        }
    } vec2;

    typedef struct vec3 {
        union {
            struct {
                float x, y, z;
            };

            float data[3];
        };

        float *operator[](uint8_t index) {
            return &(this->data[index]);
        }
    } vec3;

    typedef struct vec4 {
        union {
            struct {
                float x, y, z, w;
            };

            float data[4];
        };

        float *operator[](uint8_t index) {
            return &(this->data[index]);
        }
    } vec4;

    typedef struct ivec2 {
        union {
            struct {
                int32_t x, y;
            };

            int32_t data[2];
        };

        int32_t *operator[](uint8_t index) {
            return &(this->data[index]);
        }
    } ivec2;

    typedef struct ivec3 {
        union {
            struct {
                int32_t x, y, z;
            };

            int32_t data[3];
        };

        int32_t *operator[](uint8_t index) {
            return &(this->data[index]);
        }
    } ivec3;

    typedef struct ivec4 {
        union {
            struct {
                int32_t x, y, z, w;
            };

            int32_t data[4];
        };

        int32_t *operator[](uint8_t index) {
            return &(this->data[index]);
        }
    } ivec4;
}

#endif