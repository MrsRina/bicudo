#include "bicudo/api/util/math.hpp"
#include <cmath>

float bicudo::dt {}, bicudo::unsafe_dt {};
bicudo::mat4 bicudo::matrix::orthographic {};

bicudo::mat4::mat4(float z) {
    /* create an identity matrix */
    this->data[bicudo::matrix::I11] = z;
    this->data[bicudo::matrix::I22] = z;
    this->data[bicudo::matrix::I33] = z;
    this->data[bicudo::matrix::I44] = z;
}

float *bicudo::mat4::operator ~() {
    return this->data;
}

float &bicudo::mat4::operator [](char index) {
    return this->data[index];
}


void bicudo::operator *=(const bicudo::mat4 &m) {
    bicudo::mat4 r {};
    r = *this;

    this->data[bicudo::matrix::I11] = (r[bicudo::matrix::I11] * m[bicudo::matrix::I11]) + (r[bicudo::matrix::I12] * m[bicudo::matrix::I21]) + (r[bicudo::matrix::I13] * m[bicudo::matrix::I31]) + (r[bicudo::matrix::I14] * m[bicudo::matrix::I41]);
    this->data[bicudo::matrix::I12] = (r[bicudo::matrix::I11] * m[bicudo::matrix::I12]) + (r[bicudo::matrix::I12] * m[bicudo::matrix::I22]) + (r[bicudo::matrix::I13] * m[bicudo::matrix::I32]) + (r[bicudo::matrix::I14] * m[bicudo::matrix::I42]);
    this->data[bicudo::matrix::I13] = (r[bicudo::matrix::I11] * m[bicudo::matrix::I13]) + (r[bicudo::matrix::I12] * m[bicudo::matrix::I23]) + (r[bicudo::matrix::I13] * m[bicudo::matrix::I33]) + (r[bicudo::matrix::I14] * m[bicudo::matrix::I43]);
    this->data[bicudo::matrix::I14] = (r[bicudo::matrix::I11] * m[bicudo::matrix::I14]) + (r[bicudo::matrix::I12] * m[bicudo::matrix::I24]) + (r[bicudo::matrix::I14] * m[bicudo::matrix::I34]) + (r[bicudo::matrix::I14] * m[bicudo::matrix::I44]);
}

bicudo::mat4 operator *(const bicudo::mat4&);

bicudo::mat4::~mat4() {

}

void bicudo::identity(bicudo::mat4 &mat) {
    mat[bicudo::matrix::I11] = 1.0f;
    mat[bicudo::matrix::I22] = 1.0f;
    mat[bicudo::matrix::I33] = 1.0f;
    mat[bicudo::matrix::I44] = 1.0f;
}

void bicudo::translate(bicudo::mat4 &mat, const bicudo::vec3 &pos) {
    bicudo::mat4 result {};
    result = mat;

    result[bicudo::matrix::I41] = (mat[bicudo::matrix::I11] * pos.x) + (mat[bicudo::matrix::I21] * pos.y) + (mat[bicudo::matrix::I31] * pos.z + mat[bicudo::matrix::I41]);
    result[bicudo::matrix::I42] = (mat[bicudo::matrix::I12] * pos.x) + (mat[bicudo::matrix::I22] * pos.y) + (mat[bicudo::matrix::I32] * pos.z + mat[bicudo::matrix::I42]);
    result[bicudo::matrix::I43] = (mat[bicudo::matrix::I13] * pos.x) + (mat[bicudo::matrix::I23] * pos.y) + (mat[bicudo::matrix::I33] * pos.z + mat[bicudo::matrix::I43]);
    result[bicudo::matrix::I44] = (mat[bicudo::matrix::I14] * pos.x) + (mat[bicudo::matrix::I24] * pos.y) + (mat[bicudo::matrix::I34] * pos.z + mat[bicudo::matrix::I44]);
    mat = result;
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

    mat[bicudo::matrix::I11] = 2.0f * invx;
    mat[bicudo::matrix::I12] = 0.0f;
    mat[bicudo::matrix::I13] = 0.0f;
    mat[bicudo::matrix::I14] = 0.0f;

    mat[bicudo::matrix::I21] = 0.0f;
    mat[bicudo::matrix::I22] = 2.0f * invy;;
    mat[bicudo::matrix::I23] = 0.0f;
    mat[bicudo::matrix::I24] = 0.0f;

    mat[bicudo::matrix::I31] = 0.0f;
    mat[bicudo::matrix::I32] = 0.0f;
    mat[bicudo::matrix::I33] = -2.0f * invz;
    mat[bicudo::matrix::I34] = 0.0f;
    
    mat[bicudo::matrix::I41] = -(right + left) * invx;
    mat[bicudo::matrix::I42] = -(top + bottom) * invy;
    mat[bicudo::matrix::I43] = -(max_depth + min_depth) * invz;
    mat[bicudo::matrix::I44] = 1.0f;
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