#ifndef BICUDO_UTIL_MATH_H
#define BICUDO_UTIL_MATH_H

#include <iostream>
#include <cmath>
#include <cfloat>

#define ASSERT_FLOAT(x, y) (fabsf((x) - (y)) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))
#define DEG2RAD(x) ((x) * 0.0174533f)

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
            return &(this->data[index * 2]);
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
            return &(this->data[index * 3]);
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

            float data[16] {};
        };

        inline explicit mat4(float identity_value = 1.0f) {
            this->i11 = identity_value;
            this->i12 = 0;
            this->i13 = 0;
            this->i14 = 0;

            this->i21 = 0;
            this->i22 = identity_value;
            this->i23 = 0;
            this->i24 = 0;

            this->i31 = 0;
            this->i32 = 0;
            this->i33 = identity_value;
            this->i34 = 0;

            this->i41 = 0;
            this->i42 = 0;
            this->i43 = 0;
            this->i44 = identity_value;
        }

        inline mat4(float _11, float _12, float _13, float _14,
                    float _21, float _22, float _23, float _24,
                    float _31, float _32, float _33, float _34,
                    float _41, float _42, float _43, float _44) {
            this->i11 = _11; this->i12 = _12; this->i13 = _13; this->i14 = _14;
            this->i21 = _21; this->i22 = _22; this->i23 = _23; this->i24 = _24;
            this->i31 = _31; this->i32 = _32; this->i33 = _33; this->i34 = _34;
            this->i41 = _41; this->i42 = _42; this->i43 = _43; this->i44 = _44;
        }

        float *operator[](uint8_t index) {
            return &(this->data[index * 4]);
        }
    } mat4;

    typedef struct vec2 {
        union {
            struct {
                float x, y;
            };

            float data[2] {};
        };

        explicit inline vec2() = default;
        inline vec2(float _x, float _y) {
            this->x = _x;
            this->y = _y;
        }

        inline float &operator[](uint8_t index) {
            return this->data[index];
        }
    } vec2;

    typedef struct vec3 {
        union {
            struct {
                float x,  y, z;
            };

            float data[3] {};
        };

        inline float &operator[](uint8_t index) {
            return this->data[index];
        }
    } vec3;

    typedef struct vec4 {
        union {
            struct {
                float x, y, z, w;
            };

            float data[4] {};
        };

        inline float &operator[](uint8_t index) {
            return this->data[index];
        }
    } vec4;

    typedef struct ivec2 {
        union {
            struct {
                int32_t x, y;
            };

            int32_t data[2] {};
        };

        inline int32_t &operator[](uint8_t index) {
            return this->data[index];
        }
    } ivec2;

    typedef struct ivec3 {
        union {
            struct {
                int32_t x, y, z;
            };

            int32_t data[3] {};
        };

        inline int32_t &operator[](uint8_t index) {
            return this->data[index];
        }
    } ivec3;

    typedef struct ivec4 {
        union {
            struct {
                int32_t x, y, z, w;
            };

            int32_t data[4] {};
        };

        inline int32_t &operator[](uint8_t index) {
            return this->data[index];
        }
    } ivec4;

    /* Start of vec2 mathematical operators. */
    inline bicudo::vec2 operator+(const bicudo::vec2 &l, const bicudo::vec2 &r) {
        return {l.x + r.x, l.y + r.y};
    }

    inline bicudo::vec2 operator-(const bicudo::vec2 &l, const bicudo::vec2 &r) {
        return {l.x - r.x, l.y - r.y};
    }

    inline bicudo::vec2 operator*(const bicudo::vec2 &l, const bicudo::vec2 &r) {
        return {l.x * r.x, l.y * r.y};
    }

    inline bicudo::vec2 operator/(const bicudo::vec2 &l, const bicudo::vec2 &r) {
        return {l.x / r.x, l.y / r.y};
    }

    inline bicudo::vec2 operator+(const bicudo::vec2 &l, float add) {
        return {l.x + add, l.y + add};
    }

    inline bicudo::vec2 operator-(const bicudo::vec2 &l, float subtract) {
        return {l.x - subtract, l.y - subtract};
    }

    inline bicudo::vec2 operator*(const bicudo::vec2 &l, float scalar) {
        return {l.x * scalar, l.y * scalar};
    }

    inline bicudo::vec2 operator/(const bicudo::vec2 &l, float div) {
        float x = l.x;
        float y = l.y;

        if (div != 0.0f) {
            x /= div;
            y /= div;
        }

        return {x, y};
    }

    inline bool operator==(const bicudo::vec2 &l, const bicudo::vec2 &r) {
        return ASSERT_FLOAT(l.x, r.x) && ASSERT_FLOAT(l.y, r.y);
    }

    inline bool operator!=(const bicudo::vec2 &l, const bicudo::vec2 &r) {
        return !(l == r);
    }

    inline float distance(const bicudo::vec2 &l, const bicudo::vec2 &r) {
        bicudo::vec2 diff {l - r};
        return sqrtf(diff.x * diff.x + diff.y * diff.y);
    }

    inline bicudo::vec2 normalize(const bicudo::vec2 &l) {
        float mag {sqrtf(l.x * l.x + l.y * l.y)};
        if (mag > 0) {
            mag = 1.0f / mag;
        }

        return {l.x * mag, l.y * mag};
    }

    inline float magnitude(const bicudo::vec2 &l) {
        return sqrtf(l.x * l.x + l.y * l.y);
    }

    inline float dot(const bicudo::vec2 &l, const bicudo::vec2 &r) {
        return l.x * r.x + l.y * r.y;
    }

    inline float cross(const bicudo::vec2 &l, const bicudo::vec2 &r) {
        return l.x * r.y - l.y * r.x;
    }

    inline bicudo::vec2 rotate(const bicudo::vec2 &l, float angle) {
        angle = DEG2RAD(angle);
        return {l.x * cosf(angle) - l.y * sinf(angle), l.x * sinf(angle) + l.y * cosf(angle)};
    }

    inline bicudo::vec2 rotate(const bicudo::vec2 &vec, float angle, const bicudo::vec2 &center) {
        bicudo::vec2 displacement {vec - center};
        displacement = bicudo::rotate(displacement, angle);
        return displacement + center;
    }

    inline bicudo::vec2 &operator/=(bicudo::vec2 &l, float div) {
        return (l = l / div);
    }

    inline bicudo::vec2 &operator+=(bicudo::vec2 &l, float add) {
        return (l = l + add);
    }

    inline bicudo::vec2 &operator-=(bicudo::vec2 &l, float subtract) {
        return (l = l - subtract);
    }

    inline bicudo::vec2 &operator*=(bicudo::vec2 &l, float scalar) {
        return (l = l * scalar);
    }

    inline bicudo::vec2 &operator-=(bicudo::vec2 &l, const bicudo::vec2 &r) {
        return (l = l - r);
    }

    inline bicudo::vec2 &operator+=(bicudo::vec2 &l, const bicudo::vec2 &r) {
        return (l = l + r);
    }

    inline bicudo::vec2 &operator/=(bicudo::vec2 &l, const bicudo::vec2 &r) {
        return (l = l / r);
    }

    inline bicudo::vec2 &operator*=(bicudo::vec2 &l, const bicudo::vec2 &r) {
        return (l = l * r);
    }

    /* Start of vec3 overload operators. */

    /* Start of mat4 overload operators. */
    inline void multiply(float *p_out, const float *p_m_a, int32_t a_rows, int32_t a_cols, const float *p_m_b, int32_t b_rows, int32_t b_cols) {
        int32_t rr_a {};
        int32_t rr_b {};

        for (int32_t i {}; i < a_rows; ++i) {
            for (int32_t j {}; j < b_cols; ++j) {
                p_out[b_cols * i + j] = 0.0f;

                for (int32_t it {}; it < b_rows; ++it) {
                    rr_a = a_cols * i + it;
                    rr_b = b_cols * it + j;
                    p_out[b_cols * i + j] += p_m_a[rr_a] * p_m_b[rr_b];
                }
            }
        }
    }

    inline bicudo::mat4 operator*(const bicudo::mat4 &l, float scalar) {
        bicudo::mat4 r {1.0f};
        for (uint32_t it {}; it < 16; it++) {
            r.data[it] = l.data[it] * scalar;
        }
        return r;
    }

    inline bicudo::mat4 operator*(const bicudo::mat4 &m_l, const bicudo::mat4 &m_r) {
        bicudo::mat4 r {};
        bicudo::multiply(r.data, m_l.data, 4, 4, m_r.data, 4, 4);
        return r;
    }

    inline bicudo::mat4 orthographic(float left, float right, float bottom, float top) {
        const float near {-1.0f};
        const float far {1.0f};
        const float inv_z {1.0f / (far - near)};
        const float inv_y {1.0f / (top - bottom)};
        const float inv_x {1.0f / (right - left)};

        return {
            2.0f * inv_x, 0.0f, 0.0f, 0.0f,
            0.0f, 2.0f * inv_y, 0.0f, 0.0f,
            0.0f, 0.0f, -2.0f * inv_z, 0.0f,
            -(right + left) * inv_x, -(top + bottom) * inv_y, -(far + near) * inv_z, 1.0f
        };
    }

    inline bicudo::mat4 translate(bicudo::mat4 &m, bicudo::vec3 &p) {
        bicudo::mat4 t {1.0f};

        t[3][0] = p.x;
        t[3][1] = p.y;
        t[3][2] = p.z;

        return m * t;
    }

    inline bicudo::mat4 scale(bicudo::mat4 &m, bicudo::vec3 &s) {
        bicudo::mat4 t {1.0f};

        t[0][0] = s.x;
        t[1][1] = s.y;
        t[2][2] = s.z;

        return m * t;
    }

    inline bicudo::mat4 rotate(float angle, const bicudo::vec3 &a) {
        bicudo::mat4 r {};
        angle = DEG2RAD(angle);

        if (a.x != 0) {
            r[1][1] = cosf(angle);
            r[1][2] = sinf(angle);
            r[2][1] = -sinf(angle);
            r[2][2] = cosf(angle);
        } else if (a.y != 0) {
            r[0][0] = cosf(angle);
            r[0][2] = -sinf(angle);
            r[2][0] = sinf(angle);
            r[2][2] = cosf(angle);
        } else if (a.z != 0) {
            r[0][0] = cosf(angle);
            r[0][1] = sinf(angle);
            r[1][0] = -sinf(angle);
            r[1][1] = cosf(angle);
        }

        return r;
    }

    inline bicudo::mat4 rotate(const bicudo::mat4 &m, float angle, const bicudo::vec3 &a) {
        bicudo::mat4 r {bicudo::rotate(angle, a)};
        return m * r;
    }

    inline bicudo::mat4 &operator*=(bicudo::mat4 &m, float scalar) {
        return (m = m * scalar);
    }

    inline bicudo::mat4 &operator*=(bicudo::mat4 &m, const bicudo::mat4 &r) {
        return (m = m * r);
    }

    /* Empty mathematical primitives. */
    const static bicudo::vec2 vec2zero {0.0f, 0.0f};
    const static bicudo::vec3 vec3zero {0.0f, 0.0f, 0.0f};
    const static bicudo::vec4 vec4zero {0.0f, 0.0f, 0.0f, 0.0f};
    
    const static bicudo::mat2 mat2zero {0.0f, 0.0f, 0.0f, 0.0f};
    const static bicudo::mat3 mat3zero {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    const static bicudo::mat4 mat4zero {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    
    const float zero {0.0f};
}

#endif