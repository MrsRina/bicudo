#ifndef BICUDO_UTIL_MATH_H
#define BICUDO_UTIL_MATH_H

#include <iostream>
#include <cmath>
#include <cfloat>

#define ASSERT_FLOAT(x, y) (fabsf((x) - (y)) <= FLT_EPSILON * fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))))
#define DEG2RAD(x) ((x) * 0.0174533f)
#define PI 3.14159265358979323846

namespace bicudo {
    typedef struct mat2 {
        union {
            struct {
                float i11, i12,
                      i21, i22;
            };

            float data[4] {};
        };

        inline float *operator[](int32_t index) {
            return &(this->data[index * 2]);
        }

        inline explicit mat2(float scale = 0.0f) :
                i11(scale), i12(0.0f),
                i21(0.0f), i22(scale) {};

        inline mat2(float _11, float _12,
                    float _21, float _22) :
                i11(_11), i12(_12),
                i21(_21), i22(_22) {};
    } mat2;

    typedef struct mat3 {
        union {
            struct {
                float i11, i12, i13,
                      i21, i22, i23,
                      i31, i32, i33;
            };

            float data[9] {};
        };

        inline float *operator[](int32_t index) {
            return &(this->data[index * 3]);
        }

        inline explicit mat3(float scale = 0.0f) :
                i11(scale), i12(0.0f), i13(0.0f),
                i21(0.0f), i22(scale), i23(0.0f),
                i31(0.0f), i32(0.0f), i33(scale) {};

        inline mat3(float _11, float _12, float _13,
                    float _21, float _22, float _23,
                    float _31, float _32, float _33) :
                i11(_11), i12(_12), i13(_13),
                i21(_21), i22(_22), i23(_23),
                i31(_31), i32(_32), i33(_33) {}
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

        inline float *operator[](int32_t index) {
            return &(this->data[index * 4]);
        }

        inline explicit mat4(float scale = 0.0f) :
                    i11(scale), i12(0.0f), i13(0.0f), i14(0.0f),
                    i21(0.0f), i22(scale), i23(0.0f), i24(0.0f),
                    i31(0.0f), i32(0.0f), i33(scale), i34(0.0f),
                    i41(0.0f), i42(0.0f), i43(0.0f), i44(scale) {};

        inline mat4(float _11, float _12, float _13, float _14,
                    float _21, float _22, float _23, float _24,
                    float _31, float _32, float _33, float _34,
                    float _41, float _42, float _43, float _44) :

                    i11(_11), i12(_12), i13(_13), i14(_14),
                    i21(_21), i22(_22), i23(_23), i24(_24),
                    i31(_31), i32(_32), i33(_33), i34(_34),
                    i41(_41), i42(_42), i43(_43), i44(_44) {}
    } mat4;

    typedef struct vec2 {
        union {
            struct {
                float x, y;
            };

            float data[2] {};
        };

        float &operator[](int32_t index) {
            return this->data[index];
        }

        inline vec2() : x(0.0f), y(0.0f) {}
        inline vec2(float _x, float _y) : x(_x), y(_y) {}
    } vec2;

    typedef struct vec3 {
        union {
            struct {
                float x, y, z;
            };

            float data[3] {};
        };

        float &operator[](int32_t index) {
            return this->data[index];
        }

        inline vec3() : x(0.0f), y(0.0f), z(0.0f) {}
        inline vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    } vec3;

    typedef struct vec4 {
        union {
            struct {
                float x;
                float y;
                float z;
                float w;
            };

            float data[4] {};
        };

        float &operator[](int32_t index) {
            return this->data[index];
        }

        inline vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        inline vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    } vec4;

    typedef struct ivec2 {
        union {
            struct {
                int32_t x, y;
            };

            int32_t data[2] {};
        };

        int32_t &operator[](int32_t index) {
            return this->data[index];
        }

        inline ivec2() : x(0), y(0) {}
        inline ivec2(int32_t _x, int32_t _y) : x(_x), y(_y) {}
    } ivec2;

    typedef struct ivec3 {
        union {
            struct {
                int32_t x, y, z;
            };

            int32_t data[3] {};
        };

        int32_t &operator[](int32_t index) {
            return this->data[index];
        }

        inline ivec3() : x(0), y(0), z(0) {}
        inline ivec3(int32_t _x, int32_t _y, int32_t _z) : x(_x), y(_y), z(_z) {}
    } ivec3;

    typedef struct ivec4 {
        union {
            struct {
                int32_t x, y, z, w;
            };

            int32_t data[4] {};
        };

        int32_t &operator[](int32_t index) {
            return this->data[index];
        }

        inline ivec4() : x(0), y(0), z(0), w(0) {}
        inline ivec4(int32_t _x, int32_t _y, int32_t _z) : x(_x), y(_y), z(_z), w(_z) {}
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
        if (mag > 0.0f) {
            mag = 1.0f / mag;
        }

        return {l.x * mag, l.y * mag};
    }

    inline bicudo::vec3 normalize(const bicudo::vec3 &l) {
        float mag {sqrtf(l.x * l.x + l.y * l.y + l.z * l.z)};
        if (mag > 0.0f) {
            mag = 1.0f / mag;
        }

        return {l.x * mag, l.y * mag, l.z * mag};
    }

    inline float magnitude(const bicudo::vec3 &l) {
        return sqrtf(l.x * l.x + l.y * l.y + l.z * l.z);
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

    inline bicudo::vec3 operator-(const bicudo::vec3 &l) {
        return {-l.x, -l.y, -l.z};
    }

    /* Start of mat4 overload operators. */
    inline void multiply(float *p_out, const float *p_m_a, int32_t a_rows, int32_t a_cols, const float *p_m_b, int32_t b_rows, int32_t b_cols) {
        int32_t rr_a {};
        int32_t rr_b {};

        for (int32_t i {}; i < a_rows; ++i) {
            for (int32_t j {}; j < b_cols; ++j) {
                p_out[b_cols * i + j] = 0.0f;

                for (int32_t k {}; k < b_rows; ++k) {
                    rr_a = a_cols * i + k;
                    rr_b = b_cols * k + j;
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
        bicudo::mat4 r {1.0f};
        bicudo::multiply(r.data, m_l.data, 4, 4, m_r.data, 4, 4);
        return r;
    }

    inline bicudo::mat4 operator+(const bicudo::mat4 &m_l, const bicudo::mat4 &m_r) {
        bicudo::mat4 r {1.0f};
        for (uint32_t it {}; it < 16; it++) {
            r.data[it] = m_l.data[it] * m_r.data[it];
        }
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

    inline bicudo::mat4 translate(bicudo::mat4 &m, const bicudo::vec3 &p) {
        m[3][0] += p.x;
        m[3][1] += p.y;
        m[3][2] += p.z;

        return m;
    }

    inline bicudo::mat4 scale(bicudo::mat4 &m, const bicudo::vec3 &s) {
        bicudo::mat4 t {1.0f};

        t[0][3] *= s.x;
        t[1][3] *= s.y;
        t[2][3] *= s.z;

        return m;
    }

    inline bicudo::mat4 rotate(float angle, const bicudo::vec3 &a) {
        bicudo::mat4 r {1.0f};

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

    inline bicudo::mat4 rotate(bicudo::mat4 &m, float a, const bicudo::vec3 &axis) {
//        float c {cosf(a)};
//        float s {sinf(a)};
//        float t {1.0f - c};

//        bicudo::vec3 v {bicudo::normalize(axis)};

//        float x {v.x};
//        float y {v.y};
//        float z {v.z};

//        bicudo::mat4 r {
//            t*(x*x) + c, t*x*y + s*z, t*x*z - s*y, 0.0f,
//            t*x*y - s*z, t*(y*y) + c, t*y*z + s*x, 0.0f,
//            t*x*z + s*y, t*y*z - s*x, t*(z*z) + c, 0.0f,
//            0.0f, 0.0f, 0.0f, 1.0f
//        };

        if (axis.x != 0) {
            m[1][1] *= cosf(a);
            m[1][2] *= sinf(a);
            m[2][1] *= -sinf(a);
            m[2][2] *= cosf(a);
        } else if (axis.y != 0) {
            m[0][0] *= cosf(a);
            m[0][2] *= -sinf(a);
            m[2][0] *= sinf(a);
            m[2][2] *= cosf(a);
        } else if (axis.z != 0) {
            m[0][0] *= cosf(a);
            m[0][1] *= sinf(a);
            m[1][0] *= -sinf(a);
            m[1][1] *= cosf(a);
        }

        return m;
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