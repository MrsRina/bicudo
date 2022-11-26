#include "bicudo/api/util/math.hpp"
#include <cmath>

float bicudo::dt {}, bicudo::unsafe_dt {};
bicudo::mat4 bicudo::mat::orthographic {};

bicudo::mat4::mat4(float z) {
    /* create an identity matrix */
    this->data[bicudo::mat::I11] = z;
    this->data[bicudo::mat::I22] = z;
    this->data[bicudo::mat::I33] = z;
    this->data[bicudo::mat::I44] = z;
}

float *bicudo::mat4::operator ~() {
    return this->data;
}

float &bicudo::mat4::operator [](char index) {
    return this->data[index];
}

void bicudo::mat4::operator *=(bicudo::mat4 &m) {
    bicudo::mat4 r {};
    r = *this;

    this->data[bicudo::mat::I11] = (r[bicudo::mat::I11] * m[bicudo::mat::I11]) + (r[bicudo::mat::I12] * m[bicudo::mat::I21]) + (r[bicudo::mat::I13] * m[bicudo::mat::I31]) + (r[bicudo::mat::I14] * m[bicudo::mat::I41]);
    this->data[bicudo::mat::I12] = (r[bicudo::mat::I11] * m[bicudo::mat::I21]) + (r[bicudo::mat::I12] * m[bicudo::mat::I22]) + (r[bicudo::mat::I13] * m[bicudo::mat::I32]) + (r[bicudo::mat::I14] * m[bicudo::mat::I42]);
    this->data[bicudo::mat::I13] = (r[bicudo::mat::I11] * m[bicudo::mat::I31]) + (r[bicudo::mat::I12] * m[bicudo::mat::I32]) + (r[bicudo::mat::I13] * m[bicudo::mat::I33]) + (r[bicudo::mat::I14] * m[bicudo::mat::I34]);
    this->data[bicudo::mat::I14] = (r[bicudo::mat::I11] * m[bicudo::mat::I41]) + (r[bicudo::mat::I12] * m[bicudo::mat::I42]) + (r[bicudo::mat::I13] * m[bicudo::mat::I43]) + (r[bicudo::mat::I14] * m[bicudo::mat::I44]);

    this->data[bicudo::mat::I21] = (r[bicudo::mat::I21] * m[bicudo::mat::I11]) + (r[bicudo::mat::I22] * m[bicudo::mat::I21]) + (r[bicudo::mat::I23] * m[bicudo::mat::I31]) + (r[bicudo::mat::I24] * m[bicudo::mat::I41]);
    this->data[bicudo::mat::I22] = (r[bicudo::mat::I21] * m[bicudo::mat::I21]) + (r[bicudo::mat::I22] * m[bicudo::mat::I22]) + (r[bicudo::mat::I23] * m[bicudo::mat::I32]) + (r[bicudo::mat::I24] * m[bicudo::mat::I42]);
    this->data[bicudo::mat::I23] = (r[bicudo::mat::I21] * m[bicudo::mat::I31]) + (r[bicudo::mat::I22] * m[bicudo::mat::I32]) + (r[bicudo::mat::I23] * m[bicudo::mat::I33]) + (r[bicudo::mat::I24] * m[bicudo::mat::I34]);
    this->data[bicudo::mat::I24] = (r[bicudo::mat::I21] * m[bicudo::mat::I41]) + (r[bicudo::mat::I22] * m[bicudo::mat::I42]) + (r[bicudo::mat::I23] * m[bicudo::mat::I43]) + (r[bicudo::mat::I24] * m[bicudo::mat::I44]);

    this->data[bicudo::mat::I31] = (r[bicudo::mat::I31] * m[bicudo::mat::I11]) + (r[bicudo::mat::I32] * m[bicudo::mat::I21]) + (r[bicudo::mat::I33] * m[bicudo::mat::I31]) + (r[bicudo::mat::I34] * m[bicudo::mat::I41]);
    this->data[bicudo::mat::I32] = (r[bicudo::mat::I31] * m[bicudo::mat::I21]) + (r[bicudo::mat::I32] * m[bicudo::mat::I22]) + (r[bicudo::mat::I33] * m[bicudo::mat::I32]) + (r[bicudo::mat::I34] * m[bicudo::mat::I42]);
    this->data[bicudo::mat::I33] = (r[bicudo::mat::I31] * m[bicudo::mat::I31]) + (r[bicudo::mat::I32] * m[bicudo::mat::I32]) + (r[bicudo::mat::I33] * m[bicudo::mat::I33]) + (r[bicudo::mat::I34] * m[bicudo::mat::I34]);
    this->data[bicudo::mat::I34] = (r[bicudo::mat::I31] * m[bicudo::mat::I41]) + (r[bicudo::mat::I32] * m[bicudo::mat::I42]) + (r[bicudo::mat::I33] * m[bicudo::mat::I43]) + (r[bicudo::mat::I34] * m[bicudo::mat::I44]);

    this->data[bicudo::mat::I41] = (r[bicudo::mat::I41] * m[bicudo::mat::I11]) + (r[bicudo::mat::I42] * m[bicudo::mat::I21]) + (r[bicudo::mat::I43] * m[bicudo::mat::I31]) + (r[bicudo::mat::I44] * m[bicudo::mat::I41]);
    this->data[bicudo::mat::I42] = (r[bicudo::mat::I41] * m[bicudo::mat::I21]) + (r[bicudo::mat::I42] * m[bicudo::mat::I22]) + (r[bicudo::mat::I43] * m[bicudo::mat::I32]) + (r[bicudo::mat::I44] * m[bicudo::mat::I42]);
    this->data[bicudo::mat::I43] = (r[bicudo::mat::I41] * m[bicudo::mat::I31]) + (r[bicudo::mat::I42] * m[bicudo::mat::I32]) + (r[bicudo::mat::I43] * m[bicudo::mat::I33]) + (r[bicudo::mat::I44] * m[bicudo::mat::I34]);
    this->data[bicudo::mat::I44] = (r[bicudo::mat::I41] * m[bicudo::mat::I41]) + (r[bicudo::mat::I42] * m[bicudo::mat::I42]) + (r[bicudo::mat::I43] * m[bicudo::mat::I43]) + (r[bicudo::mat::I44] * m[bicudo::mat::I44]);
}

bicudo::mat4 bicudo::mat4::operator *(bicudo::mat4 &m) {
    bicudo::mat4 r {}, result {};
    r = *this;

    result[bicudo::mat::I11] = (r[bicudo::mat::I11] * m[bicudo::mat::I11]) + (r[bicudo::mat::I12] * m[bicudo::mat::I21]) + (r[bicudo::mat::I13] * m[bicudo::mat::I31]) + (r[bicudo::mat::I14] * m[bicudo::mat::I41]);
    result[bicudo::mat::I12] = (r[bicudo::mat::I11] * m[bicudo::mat::I21]) + (r[bicudo::mat::I12] * m[bicudo::mat::I22]) + (r[bicudo::mat::I13] * m[bicudo::mat::I32]) + (r[bicudo::mat::I14] * m[bicudo::mat::I42]);
    result[bicudo::mat::I13] = (r[bicudo::mat::I11] * m[bicudo::mat::I31]) + (r[bicudo::mat::I12] * m[bicudo::mat::I32]) + (r[bicudo::mat::I13] * m[bicudo::mat::I33]) + (r[bicudo::mat::I14] * m[bicudo::mat::I34]);
    result[bicudo::mat::I14] = (r[bicudo::mat::I11] * m[bicudo::mat::I41]) + (r[bicudo::mat::I12] * m[bicudo::mat::I42]) + (r[bicudo::mat::I13] * m[bicudo::mat::I43]) + (r[bicudo::mat::I14] * m[bicudo::mat::I44]);

    result[bicudo::mat::I21] = (r[bicudo::mat::I21] * m[bicudo::mat::I12]) + (r[bicudo::mat::I22] * m[bicudo::mat::I21]) + (r[bicudo::mat::I23] * m[bicudo::mat::I31]) + (r[bicudo::mat::I24] * m[bicudo::mat::I41]);
    result[bicudo::mat::I22] = (r[bicudo::mat::I21] * m[bicudo::mat::I12]) + (r[bicudo::mat::I22] * m[bicudo::mat::I12]) + (r[bicudo::mat::I23] * m[bicudo::mat::I32]) + (r[bicudo::mat::I24] * m[bicudo::mat::I42]);
    result[bicudo::mat::I23] = (r[bicudo::mat::I21] * m[bicudo::mat::I12]) + (r[bicudo::mat::I22] * m[bicudo::mat::I12]) + (r[bicudo::mat::I23] * m[bicudo::mat::I33]) + (r[bicudo::mat::I24] * m[bicudo::mat::I34]);
    result[bicudo::mat::I24] = (r[bicudo::mat::I21] * m[bicudo::mat::I12]) + (r[bicudo::mat::I22] * m[bicudo::mat::I12]) + (r[bicudo::mat::I23] * m[bicudo::mat::I43]) + (r[bicudo::mat::I24] * m[bicudo::mat::I44]);

    result[bicudo::mat::I31] = (r[bicudo::mat::I31] * m[bicudo::mat::I11]) + (r[bicudo::mat::I32] * m[bicudo::mat::I21]) + (r[bicudo::mat::I33] * m[bicudo::mat::I31]) + (r[bicudo::mat::I34] * m[bicudo::mat::I41]);
    result[bicudo::mat::I32] = (r[bicudo::mat::I31] * m[bicudo::mat::I21]) + (r[bicudo::mat::I32] * m[bicudo::mat::I22]) + (r[bicudo::mat::I33] * m[bicudo::mat::I32]) + (r[bicudo::mat::I34] * m[bicudo::mat::I42]);
    result[bicudo::mat::I33] = (r[bicudo::mat::I31] * m[bicudo::mat::I31]) + (r[bicudo::mat::I32] * m[bicudo::mat::I32]) + (r[bicudo::mat::I33] * m[bicudo::mat::I33]) + (r[bicudo::mat::I34] * m[bicudo::mat::I34]);
    result[bicudo::mat::I34] = (r[bicudo::mat::I31] * m[bicudo::mat::I41]) + (r[bicudo::mat::I32] * m[bicudo::mat::I42]) + (r[bicudo::mat::I33] * m[bicudo::mat::I43]) + (r[bicudo::mat::I34] * m[bicudo::mat::I44]);

    result[bicudo::mat::I41] = (r[bicudo::mat::I41] * m[bicudo::mat::I11]) + (r[bicudo::mat::I42] * m[bicudo::mat::I21]) + (r[bicudo::mat::I43] * m[bicudo::mat::I31]) + (r[bicudo::mat::I44] * m[bicudo::mat::I41]);
    result[bicudo::mat::I42] = (r[bicudo::mat::I41] * m[bicudo::mat::I21]) + (r[bicudo::mat::I42] * m[bicudo::mat::I22]) + (r[bicudo::mat::I43] * m[bicudo::mat::I32]) + (r[bicudo::mat::I44] * m[bicudo::mat::I42]);
    result[bicudo::mat::I43] = (r[bicudo::mat::I41] * m[bicudo::mat::I31]) + (r[bicudo::mat::I42] * m[bicudo::mat::I32]) + (r[bicudo::mat::I43] * m[bicudo::mat::I33]) + (r[bicudo::mat::I44] * m[bicudo::mat::I34]);
    result[bicudo::mat::I44] = (r[bicudo::mat::I41] * m[bicudo::mat::I41]) + (r[bicudo::mat::I42] * m[bicudo::mat::I42]) + (r[bicudo::mat::I43] * m[bicudo::mat::I43]) + (r[bicudo::mat::I44] * m[bicudo::mat::I44]);

    return result;
}

bicudo::mat4::~mat4() {

}

void bicudo::identity(bicudo::mat4 &mat) {
    mat[bicudo::mat::I11] = 1.0f;
    mat[bicudo::mat::I22] = 1.0f;
    mat[bicudo::mat::I33] = 1.0f;
    mat[bicudo::mat::I44] = 1.0f;
}

void bicudo::translate(bicudo::mat4 &m, const bicudo::vec3 &v) {
    bicudo::mat4 identity {};
    bicudo::identity(identity);

    identity[bicudo::mat::I41] = v.x;
    identity[bicudo::mat::I42] = v.y;
    identity[bicudo::mat::I43] = v.z;
    m = m * identity;
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

void bicudo::orthographic(bicudo::mat4 &mat, float left, float right, float bottom, float top) {
    const float min_depth = -1.0f;
    const float max_depth = 1.0f;
    const float invz = 1.0f / (max_depth - min_depth);
    const float invy = 1.0f / (top - bottom);
    const float invx = 1.0f / (right - left);

    mat[bicudo::mat::I11] = 2.0f * invx;
    mat[bicudo::mat::I12] = 0.0f;
    mat[bicudo::mat::I13] = 0.0f;
    mat[bicudo::mat::I14] = 0.0f;

    mat[bicudo::mat::I21] = 0.0f;
    mat[bicudo::mat::I22] = 2.0f * invy;;
    mat[bicudo::mat::I23] = 0.0f;
    mat[bicudo::mat::I24] = 0.0f;

    mat[bicudo::mat::I31] = 0.0f;
    mat[bicudo::mat::I32] = 0.0f;
    mat[bicudo::mat::I33] = -2.0f * invz;
    mat[bicudo::mat::I34] = 0.0f;
    
    mat[bicudo::mat::I41] = -(right + left) * invx;
    mat[bicudo::mat::I42] = -(top + bottom) * invy;
    mat[bicudo::mat::I43] = -(max_depth + min_depth) * invz;
    mat[bicudo::mat::I44] = 1.0f;
}

void bicudo::set(bicudo::collideinfo &collideinfo, float depth, bicudo::vec2 normal, bicudo::vec2 start) {
    collideinfo.depth = depth;
    collideinfo.normal = normal;
    collideinfo.start = start;
    collideinfo.end = start + normal * depth;
}

void bicudo::rotate(bicudo::mat4 &m, float a, const bicudo::vec3 &v) {
    if (v.x != 0) {
        m[bicudo::mat::I22] = cosf(a);
        m[bicudo::mat::I23] = -sinf(a);
        m[bicudo::mat::I31] = sinf(a);
        m[bicudo::mat::I33] = cosf(a);
    }

    if (v.y != 0) {
        m[bicudo::mat::I11] = cosf(a);
        m[bicudo::mat::I31] = -sinf(a);
        m[bicudo::mat::I13] = sinf(a);
        m[bicudo::mat::I33] = cosf(a);
    }

    if (v.z != 0) {
        m[bicudo::mat::I11] = cosf(a);
        m[bicudo::mat::I12] = -sinf(a);
        m[bicudo::mat::I21] = sinf(a);
        m[bicudo::mat::I22] = cosf(a);
    }
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