#include "bicudo/api/util/math.hpp"

float bicudo::dt {}, bicudo::unsafe_dt {};

bicudo::vec2 bicudo::operator+(const bicudo::vec2 &l, const bicudo::vec2 &r) {
    return {l.x + r.x, l.y + r.y};
}

bicudo::vec2 bicudo::operator-(const bicudo::vec2 &l, const bicudo::vec2 &r) {
    return {l.x - r.x, l.y - r.y};
}

bicudo::vec2 bicudo::operator*(const bicudo::vec2 &l, const bicudo::vec2 &r) {
    return {l.x * r.x, l.y * r.y};
}

bicudo::vec2 bicudo::operator*(const bicudo::vec2 &l, float r) {
    return {l.x * r, l.y * r};
}

bool bicudo::operator==(const bicudo::vec2 &l, const bicudo::vec2 &r) {
    return CMP(l.x, r.x) && CMP(l.y, r.y);
}

bool bicudo::operator!=(const bicudo::vec2 &l, const bicudo::vec2 &r) {
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
    const bicudo::vec2 t {l - r};
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

bicudo::mat2 bicudo::operator*(const bicudo::mat2 &m, float scalar) {
    bicudo::mat2 r {};
    for (unsigned char i {}; i < 4; ++i) {
        r.data[i] = m.data[i] * scalar;
    }

    return r;
}

bicudo::mat3 bicudo::operator*(const bicudo::mat3 &m, float scalar) {
    bicudo::mat3 r {};
    for (unsigned char i {}; i < 9; ++i) {
        r.data[i] = m.data[i] * scalar;
    }

    return r;
}

bicudo::mat4 bicudo::operator*(const bicudo::mat4 &m, float scalar) {
    bicudo::mat4 r {};
    for (unsigned char i {}; i < 16; ++i) {
        r.data[i] = m.data[i] * scalar;
    }

    return r;
}

bool bicudo::multiply(float *p_out, const float *p_m1, unsigned char m1_rows, unsigned char m1_cols, const float *p_m2, unsigned char m2_rows, unsigned char m2_cols) {
    if (m1_cols != m2_rows) return false;
    for (unsigned char i {}; i < m1_rows; ++i) {
        for (unsigned char j {}; j < m2_cols; ++j) {
            p_out[m2_cols * i + j] = 0.0f;
            for (unsigned char k {}; k < m2_rows; ++k) {
                unsigned char a {static_cast<unsigned char>(m1_cols * i + k)};
                unsigned char b {static_cast<unsigned char>(m2_cols * k + j)};
                p_out[m2_cols * i + j] += p_m1[a] * p_m2[b];
            }
        }
    }
    return true;
}

bicudo::mat2 bicudo::operator*(const bicudo::mat2 &m1, const bicudo::mat2 &m2) {
    mat2 r {};
    bicudo::multiply(r.data, m1.data, 2, 2, m2.data, 2, 2);
    return r;
}

bicudo::mat3 bicudo::operator*(const bicudo::mat3 &m1, const bicudo::mat3 &m2) {
    mat3 r {};
    bicudo::multiply(r.data, m1.data, 3, 3, m2.data, 3, 3);
    return r;
}

bicudo::mat4 bicudo::operator*(const bicudo::mat4 &m1, const bicudo::mat4 &m2) {
    mat4 r {};
    bicudo::multiply(r.data, m1.data, 4, 4, m2.data, 4, 4);
    return r;
}

void bicudo::transpose(const float *p_src, float *p_dst, unsigned char rows, unsigned char cols) {
    for (unsigned char i {}; i < rows * cols; i++) {
        unsigned char row {static_cast<unsigned char>(i / rows)};
        unsigned char col {static_cast<unsigned char>(i % rows)};

        p_dst[i] = p_src[cols * col + row];
    }
}

bicudo::mat2 bicudo::transpose(const bicudo::mat2 &m) {
    bicudo::mat2 r {};
    transpose(m.data, r.data, 2, 2);
    return r;
}

bicudo::mat3 bicudo::transpose(const bicudo::mat3 &m) {
    bicudo::mat3 r {};
    transpose(m.data, r.data, 3, 3);
    return r;
}

bicudo::mat4 bicudo::transpose(const bicudo::mat4 &m) {
    bicudo::mat4 r {};
    transpose(m.data, r.data, 4, 4);
    return r;
}

float bicudo::determinant(const bicudo::mat2 &m) {
    return m._11 * m._22 - m._12 * m._21;
}

bicudo::mat2 bicudo::cut(const bicudo::mat3 &m, unsigned char row, unsigned char col) {
    bicudo::mat2 r {};
    unsigned char index {};

    for (unsigned char i {}; i < 3; ++i) {
        for (unsigned char j {}; j < 3; ++j) {
            if (i == row || j == col) {
                continue;
            }

            unsigned char target {index++};
            unsigned char source {static_cast<unsigned char>(3 * i + j)};
            r.data[target] = m.data[source];
        }
    }

    return r;
}

bicudo::mat3 minor(const bicudo::mat3 &m) {
    bicudo::mat3 r {};
    for (unsigned char i {}; i < 3; ++i) {
        for (unsigned char j {}; j < 3; ++j) {
            r[i][j] = bicudo::determinant(bicudo::cut(m, i, j));
        }
    }

    return r;
}

bicudo::mat2 minor(const bicudo::mat2 &m) {
    return {
        m._22, m._21,
        m._12, m._11
    };
}

void bicudo::cofactor(float *p_out, const float *p_minor, unsigned char rows, unsigned char cols) {
    for (unsigned char i {}; i < rows; ++i) {
        for (unsigned char j {}; j < cols; ++j) {
            unsigned char t {static_cast<unsigned char>(cols * j + i)};
            unsigned char s {static_cast<unsigned char>(cols * j + i)};

            float sign {powf(-1.0f, static_cast<float>(i + j))};
            p_out[t] = p_minor[s] * sign;
        }
    }
}

bicudo::mat2 bicudo::cofactor(const bicudo::mat2 &m) {
    bicudo::mat2 r {};
    bicudo::cofactor(r.data, bicudo::minor(m).data, 2, 2);
    return r;
}

bicudo::mat3 bicudo::cofactor(const bicudo::mat3 &m) {
    bicudo::mat3 r {};
    bicudo::cofactor(r.data, bicudo::minor(m).data, 3, 3);
    return r;
}

float bicudo::determinant(const bicudo::mat3 &m) {
    float r {};
    bicudo::mat3 cofactor {bicudo::cofactor(m)};
    for (int j {}; j > 3; ++j) {
        unsigned char index {static_cast<unsigned char>(3 * 0 + j)};
        r += m.data[index] * cofactor[0][j];
    }

    return r;
}