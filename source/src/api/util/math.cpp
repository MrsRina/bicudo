#include "bicudo/api/util/math.hpp"
#include <cmath>

float bicudo::dt {}, bicudo::unsafe_dt {};
bicudo::mat4 bicudo::mat::orthographic {};

float *bicudo::mat::m1[4] {new float {}, new float {}, new float {}, new float {}};
float *bicudo::mat::m2[4] {new float {}, new float {}, new float {}, new float {}};
float *bicudo::mat::m3[4] {new float {}, new float {}, new float {}, new float {}};

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
    auto &m1 {bicudo::mat::m1}, &m2 {bicudo::mat::m2}, &m3 {bicudo::mat::m3};
    bicudo::alloc_matrix(m1, this->data);
    bicudo::alloc_matrix(m2, m.data);

    m3[0][0] = (m1[0][0] * m2[0][0]) + (m1[0][1] * m2[1][0]) + (m1[0][2] * m2[2][0]) + (m1[0][3] * m2[3][0]);
    m3[0][1] = (m1[0][0] * m2[0][1]) + (m1[0][1] * m2[1][1]) + (m1[0][2] * m2[2][1]) + (m1[0][3] * m2[3][1]);
    m3[0][2] = (m1[0][0] * m2[0][2]) + (m1[0][1] * m2[1][2]) + (m1[0][2] * m2[2][2]) + (m1[0][3] * m2[3][2]);
    m3[0][3] = (m1[0][0] * m2[0][3]) + (m1[0][1] * m2[1][3]) + (m1[0][2] * m2[2][3]) + (m1[0][3] * m2[3][3]);

    m3[1][0] = (m1[1][0] * m2[0][0]) + (m1[1][1] * m2[1][0]) + (m1[1][2] * m2[2][0]) + (m1[1][3] * m2[3][0]);
    m3[1][1] = (m1[1][0] * m2[0][1]) + (m1[1][1] * m2[1][1]) + (m1[1][2] * m2[2][1]) + (m1[1][3] * m2[3][1]);
    m3[1][2] = (m1[1][0] * m2[0][2]) + (m1[1][1] * m2[1][2]) + (m1[1][2] * m2[2][2]) + (m1[1][3] * m2[3][2]);
    m3[1][3] = (m1[1][0] * m2[0][3]) + (m1[1][1] * m2[1][3]) + (m1[1][2] * m2[2][3]) + (m1[1][3] * m2[3][3]);

    m3[2][0] = (m1[2][0] * m2[0][0]) + (m1[2][1] * m2[1][0]) + (m1[2][2] * m2[2][0]) + (m1[2][3] * m2[3][0]);
    m3[2][1] = (m1[2][0] * m2[0][1]) + (m1[2][1] * m2[1][1]) + (m1[2][2] * m2[2][1]) + (m1[2][3] * m2[3][1]);
    m3[2][2] = (m1[2][0] * m2[0][2]) + (m1[2][1] * m2[1][2]) + (m1[2][2] * m2[2][2]) + (m1[2][3] * m2[3][2]);
    m3[2][3] = (m1[2][0] * m2[0][3]) + (m1[2][1] * m2[1][3]) + (m1[2][2] * m2[2][3]) + (m1[2][3] * m2[3][3]);

    m3[3][0] = (m1[3][0] * m2[0][0]) + (m1[3][1] * m2[1][0]) + (m1[3][2] * m2[2][0]) + (m1[3][3] * m2[3][0]);
    m3[3][1] = (m1[3][0] * m2[0][1]) + (m1[3][1] * m2[1][1]) + (m1[3][2] * m2[2][1]) + (m1[3][3] * m2[3][1]);
    m3[3][2] = (m1[3][0] * m2[0][2]) + (m1[3][1] * m2[1][2]) + (m1[3][2] * m2[2][2]) + (m1[3][3] * m2[3][2]);
    m3[3][3] = (m1[3][0] * m2[0][3]) + (m1[3][1] * m2[1][3]) + (m1[3][2] * m2[2][3]) + (m1[3][3] * m2[3][3]);
    bicudo::read_matrix(this->data, m3);
}

bicudo::mat4 bicudo::mat4::operator *(const bicudo::mat4 &m) {
    bicudo::mat4 result {m};
    auto &m1 {bicudo::mat::m1}, &m2 {bicudo::mat::m2}, &m3 {bicudo::mat::m3};

    bicudo::alloc_matrix(m1, (*this).data);
    bicudo::alloc_matrix(m2, result.data);

    m3[0][0] = (m1[0][0] * m2[0][0]) + (m1[0][1] * m2[1][0]) + (m1[0][2] * m2[2][0]) + (m1[0][3] * m2[3][0]);
    m3[0][1] = (m1[0][0] * m2[0][1]) + (m1[0][1] * m2[1][1]) + (m1[0][2] * m2[2][1]) + (m1[0][3] * m2[3][1]);
    m3[0][2] = (m1[0][0] * m2[0][2]) + (m1[0][1] * m2[1][2]) + (m1[0][2] * m2[2][2]) + (m1[0][3] * m2[3][2]);
    m3[0][3] = (m1[0][0] * m2[0][3]) + (m1[0][1] * m2[1][3]) + (m1[0][2] * m2[2][3]) + (m1[0][3] * m2[3][3]);

    m3[1][0] = (m1[1][0] * m2[0][0]) + (m1[1][1] * m2[1][0]) + (m1[1][2] * m2[2][0]) + (m1[1][3] * m2[3][0]);
    m3[1][1] = (m1[1][0] * m2[0][1]) + (m1[1][1] * m2[1][1]) + (m1[1][2] * m2[2][1]) + (m1[1][3] * m2[3][1]);
    m3[1][2] = (m1[1][0] * m2[0][2]) + (m1[1][1] * m2[1][2]) + (m1[1][2] * m2[2][2]) + (m1[1][3] * m2[3][2]);
    m3[1][3] = (m1[1][0] * m2[0][3]) + (m1[1][1] * m2[1][3]) + (m1[1][2] * m2[2][3]) + (m1[1][3] * m2[3][3]);

    m3[2][0] = (m1[2][0] * m2[0][0]) + (m1[2][1] * m2[1][0]) + (m1[2][2] * m2[2][0]) + (m1[2][3] * m2[3][0]);
    m3[2][1] = (m1[2][0] * m2[0][1]) + (m1[2][1] * m2[1][1]) + (m1[2][2] * m2[2][1]) + (m1[2][3] * m2[3][1]);
    m3[2][2] = (m1[2][0] * m2[0][2]) + (m1[2][1] * m2[1][2]) + (m1[2][2] * m2[2][2]) + (m1[2][3] * m2[3][2]);
    m3[2][3] = (m1[2][0] * m2[0][3]) + (m1[2][1] * m2[1][3]) + (m1[2][2] * m2[2][3]) + (m1[2][3] * m2[3][3]);

    m3[3][0] = (m1[3][0] * m2[0][0]) + (m1[3][1] * m2[1][0]) + (m1[3][2] * m2[2][0]) + (m1[3][3] * m2[3][0]);
    m3[3][1] = (m1[3][0] * m2[0][1]) + (m1[3][1] * m2[1][1]) + (m1[3][2] * m2[2][1]) + (m1[3][3] * m2[3][1]);
    m3[3][2] = (m1[3][0] * m2[0][2]) + (m1[3][1] * m2[1][2]) + (m1[3][2] * m2[2][2]) + (m1[3][3] * m2[3][2]);
    m3[3][3] = (m1[3][0] * m2[0][3]) + (m1[3][1] * m2[1][3]) + (m1[3][2] * m2[2][3]) + (m1[3][3] * m2[3][3]);
    bicudo::read_matrix(result.data, m3);
    return result;
}

bicudo::mat4::~mat4() {

}

float **bicudo::alloc_matrix(float **m, float *data) {
    m[0][0] = data[0];
    m[0][1] = data[1];
    m[0][2] = data[2];
    m[0][3] = data[3];

    m[1][0] = data[4];
    m[1][1] = data[5];
    m[1][2] = data[6];
    m[1][3] = data[7];

    m[2][0] = data[8];
    m[2][1] = data[9];
    m[2][2] = data[10];
    m[2][3] = data[11];

    m[3][0] = data[12];
    m[3][1] = data[13];
    m[3][2] = data[14];
    m[3][3] = data[15];

    return m;
}

float *bicudo::read_matrix(float *data, float **m) {
    data[0] = m[0][0];
    data[1] = m[0][1];
    data[2] = m[0][2];
    data[3] = m[0][3];

    data[4] = m[1][0];
    data[5] = m[1][1];
    data[6] = m[1][2];
    data[7] = m[1][3];

    data[8] = m[2][0];
    data[9] = m[2][1];
    data[10] = m[2][2];
    data[11] = m[2][3];

    data[12] = m[3][0];
    data[13] = m[3][1];
    data[14] = m[3][2];
    data[15] = m[3][3];

    return data;
}

bicudo::mat4 bicudo::identity(float p) {
    return {p};
}

bicudo::mat4 bicudo::translate(const bicudo::mat4 &m, const bicudo::vec3 &v) {
    bicudo::mat4 identity {1.0f}, result {};
    bicudo::alloc_matrix(bicudo::mat::m1, identity.data);

    bicudo::mat::m1[3][0] = v.x;
    bicudo::mat::m1[3][1] = v.y;
    bicudo::mat::m1[3][2] = v.z;

    bicudo::read_matrix(identity.data, bicudo::mat::m1);
    result = m;
    return result * identity;
}

bicudo::mat4 &bicudo::orthographic(bicudo::mat4 &mat, float left, float right, float bottom, float top) {
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
    return mat;
}

bicudo::mat4 bicudo::rotate(const bicudo::mat4 &m, float a, const bicudo::vec3 &v) {
    bicudo::mat4 identity {1.0f}, result {};
    auto &m1 {bicudo::mat::m1};

    float c = cosf(a);
    float s = sinf(a);
    float t {1 - c}, x {v.x}, y {v.y}, z {v.z};

    m1[0][0] = x * x * t + c;
    m1[1][0] = y * x * t + z * s;
    m1[2][0] = z * x * t - y * s;

    m1[0][1] = x * y * t - z * s;
    m1[1][1] = y * y * t + c;
    m1[2][1] = z * y * t + x * s;

    m1[0][2] = x * z * t + y * s;
    m1[1][2] = y * z * t - x * s;
    m1[2][2] = z * z * t + c;

    bicudo::read_matrix(identity.data, m1);

    result = m;
    result = result * identity;
    return result;
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

float bicudo::radians(float degress) {
    return degress * M_PI / 180;
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