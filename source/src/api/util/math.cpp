#include "bicudo/api/util/math.hpp"

float bicudo::dt {}, bicudo::unsafe_dt {};

bicudo::vec2 bicudo::operator+(const vec2 &l, const vec2 &r) {
    return {l.x + r.x, l.y + r.y};
}

bicudo::vec2 bicudo::operator-(const vec2 &l, const vec2 &r) {
    return {l.x - r.x, l.y - r.y};
}

bicudo::vec2 bicudo::operator*(const vec2 &l, const vec2 &r) {
    return {l.x * r.x, l.y * r.y};
}

bicudo::vec2 bicudo::operator*(const vec2 &l, float r) {
    return {l.x * r, l.y * r};
}

bool bicudo::operator==(const vec2 &l, const vec2 &r) {
    return CMP(l.x, r.x) && CMP(l.y, r.y);
}

bool bicudo::operator!=(const vec2 &l, const vec2 &r) {
    return !(l == r);
}

float bicudo::dot(const bicudo::vec2 &l, const bicudo::vec2 &r) {
    return l.x * r.x + l.y * r.y;
}

float bicudo::length(const bicudo::vec2 &l) {
    return sqrtf(bicudo::dot(l, l));
}

float bicudo::lengthsq(const bicudo::vec2 &l) {
    return bicudo::dot(l, l);
}

float bicudo::distance(const bicudo::vec2 &l, const bicudo::vec2 &r) {
    const vec2 t {l - r};
    return bicudo::length(t);
}

bicudo::vec2 bicudo::normalize(const bicudo::vec2 &l) {
    float len {bicudo::length(l)};
    if (len != 0) len = 1.0f / len;
    return l * len;
}

float bicudo::angle(const bicudo::vec2 &l, const bicudo::vec2 &r) {
    const float m {sqrtf(bicudo::lengthsq(l) * bicudo::lengthsq(r))};
    return acosf(bicudo::dot(l, r) / m);
}

float bicudo::degree(float r) {
    return RAD2DEG(r);
}

float bicudo::radians(float d) {
    return DEG2RAD(d);
}
