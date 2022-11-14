#ifndef BICUDO_API_UTIL_MATH_H
#define BICUDO_API_UTIL_MATH_H

namespace bicudo {
    struct vec2 {
        float x {}, y {};
    };

    struct vec4 {
        float x {}, y {}, z {}, w {};
    };

    struct matrix {
        static float orthographic[16];
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

    /*
     * Compute matrix orthographic values.
     */
    void orthographic(float*, float, float, float, float);
};

#endif