#include "bicudo/api/util/math.hpp"
#include <cmath>

float bicudo::dt {}, bicudo::unsafe_dt {};
float bicudo::matrix::orthographic[16] {};

bicudo::mat4 mat4(float z) {
    this->data[3] = z;
    this->data[7] = z;
    this->data[11] = z;
    this->data[15] = z;
}

float &operator [](int32_t index) {
    return this->data[index];
}

void bicudo::identity(bicudo::mat4 &mat) {
    mat[0][3] = 1.0f;
    mat[1][3] = 1.0f;
    mat[2][3] = 1.0f;
    mat[3][3] = 1.0f;
}

void bicudo::mat4 operator *(const bicudo::mat4 &mat) {
    this->data[0] = mat[0]
}

void bicudo::translate(bicudo::mat4 &mat, const bicudo::vec3 &pos) {
    bicudo::mat4 identity {};
    bicudo::identity(identity);

    identity[3][0] = pos.x;
    identity[3][1] = pos.y;
    identity[3][2] = pos.z;

    for (int8_t i {}; i < 4; i++) {
        for (int8_t k {}; k < 4; k++) {
            for (int8_t j {}; j < 4; j++) {
                identity[i][j] += 
            }
        }
    }
}

float bicudo::lerpf(float a, float b, float t) {
    if (t < 0 || b >= 1.0f) {
        return a;
    }

    return a + (b - a) * t;
}

double bicudo::lerpd(double a, double b, double t) {
    if (t < 0 || b >= 1.0f) {
        return a;
    }

    return a + (b - a) * t;
}

float bicudo::length(const bicudo::vec2 &vec) {
    return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

bicudo::vec2 bicudo::normalize(const bicudo::vec2 &vec) {
    float l {bicudo::length(vec)};
    if (l != 0) {
        l = 1.0f / l;
    }

    return {vec.x * l, vec.y * l};
}

float bicudo::cross(const bicudo::vec2& v1, const bicudo::vec2& v2) {
    return v1.x * v2.y - v1.y * v2.x;
}

bicudo::vec2 bicudo::rotate(const bicudo::vec2 &vec, const bicudo::vec2 &center, float angle) {
    auto centered {vec - center};
    bicudo::vec2 rotated {};

    rotated.x = centered.x * cosf(angle) - centered.y * sinf(angle);
    rotated.y = centered.x * sinf(angle) + centered.y * cosf(angle);
    rotated += center;

    return rotated;
}

float bicudo::dot(const bicudo::vec2 &v1, const bicudo::vec2 &v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

void bicudo::orthographic(float* m, float left, float right, float bottom, float top) {
    const float min_depth = -1.0f;
    const float max_depth = 1.0f;
    const float invz = 1.0f / (max_depth - min_depth);
    const float invy = 1.0f / (top - bottom);
    const float invx = 1.0f / (right - left);

    m[0] = 2.0f * invx;
    m[1] = 0.0f;
    m[2] = 0.0f;
    m[3] = 0.0f;

    m[4] = 0.0f;
    m[5] = 2.0f * invy;;
    m[6] = 0.0f;
    m[7] = 0.0f;

    m[8] = 0.0f;
    m[9] = 0.0f;
    m[10] = -2.0f * invz;
    m[11] = 0.0f;
    
    m[12] = -(right + left) * invx;
    m[13] = -(top + bottom) * invy;
    m[14] = -(max_depth + min_depth) * invz;
    m[15] = 1.0f;
}

void bicudo::set(bicudo::collideinfo &collideinfo, float depth, bicudo::vec2 normal, bicudo::vec2 start) {
    collideinfo.depth = depth;
    collideinfo.normal = normal;
    collideinfo.start = start;
    collideinfo.end = start + normal * depth;
}

bicudo::vec2 bicudo::vec2::operator*(float v) const {
    return {this->x * v, this->y * v};
}

bicudo::vec2 bicudo::vec2::operator+(float v) const {
    return {this->x + v, this->y + v};
}

bicudo::vec2 bicudo::vec2::operator-(float v) const {
    return {this->x - v, this->y - v};
}

bicudo::vec2 bicudo::vec2::operator/(float v) const {
    return {this->x / v, this->y / v};
}

bicudo::vec2 bicudo::vec2::operator+(const bicudo::vec2 &vec) const {
    return {this->x + vec.x, this->y + vec.y};
}

bicudo::vec2 bicudo::vec2::operator-(const bicudo::vec2 &vec) const {
    return {this->x - vec.x, this->y - vec.y};
}

bicudo::vec2 bicudo::vec2::operator*(const bicudo::vec2 &vec) const {
    return {this->x * vec.x, this->y * vec.y};
}

bicudo::vec2 bicudo::vec2::operator/(const bicudo::vec2 &vec) const {
    return {this->x / vec.x, this->y / vec.y};
}

void bicudo::vec2::operator-=(const bicudo::vec2 &vec) {
    this->x = this->x - vec.x;
    this->y = this->y - vec.y;
}

void bicudo::vec2::operator+=(const bicudo::vec2 &vec) {
    this->x = this->x + vec.x;
    this->y = this->y + vec.y;
}

void bicudo::vec2::operator+=(float v) {
    this->x = this->x + v;
    this->y = this->y + v;
}

void bicudo::vec2::operator-=(float v) {
    this->x = this->x - v;
    this->y = this->y - v;
}

void bicudo::vec2::operator*=(float v) {
    this->x = this->x * v;
    this->y = this->y * v;
}

void bicudo::vec2::operator/=(float v) {
    this->x = this->x * v;
    this->y = this->y * v;
}