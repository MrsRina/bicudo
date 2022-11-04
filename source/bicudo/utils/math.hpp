#ifndef BICUDO_UTILS_MATH_H
#define BICUDO_UTILS_MATH_H

namespace bicudo {
    struct vec2 {
        float x {}, y {};
    };

    /*
     * Linear interpolation (a, b, dt)
     * Returns interpolated value between a - b in type float.
     */
    float lerpf(float, float, float);

    /*
     * Linear interpolation (a, b, dt)
     * Returns interpolated value between a - b in type double.
     */
    double lerpd(double, double, double);

    /*
     * Length (vec)
     * Returns magnitude of a vector.
     */
    float length(const bicudo::vec2&);


    /*
     * Normalize (vec)
     * Returns normalized (between -1 and 1) axis values of a vector.
     */
    bicudo::vec2 normalize(const bicudo::vec2&);
};

#endif