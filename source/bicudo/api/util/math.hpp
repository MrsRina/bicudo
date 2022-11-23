#ifndef BICUDO_API_UTIL_MATH_H
#define BICUDO_API_UTIL_MATH_H

namespace bicudo {
    extern float dt, dt_unsafe;

    struct vec2 {
        float x {}, y {};

        vec2 operator *(float) const;
        vec2 operator +(float) const;
        vec2 operator -(float) const;
        vec2 operator /(float) const;
        vec2 operator +(const vec2&) const;
        vec2 operator -(const vec2&) const;
        vec2 operator *(const vec2&) const;
        vec2 operator /(const vec2&) const;

        void operator -=(const vec2&);
        void operator +=(const vec2&);
        void operator *=(float);
        void operator +=(float);
        void operator -=(float);
        void operator /=(float);
    };

    struct vec4 {
        float x {}, y {}, z {}, w {};
    };

    struct matrix {
        static float orthographic[16];
    };

    struct collideinfo {
        bicudo::vec2 start {}, end {}, normal {};
        float depth {};
    };

    /*
     * Set collide info (depth, normal, start)
     * End is the product of (start + normal * depth)
     */
    void set(bicudo::collideinfo&, float, bicudo::vec2, bicudo::vec2);

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
     * Dot (vec)
     * Return the dot product of vector.
     */
    float dot(const bicudo::vec2&, const bicudo::vec2&);

    /*
     * Length (vec)
     * Return magnitude of a vector.
     */
    float length(const bicudo::vec2&);

    /*
     * Cross (v1, v2)
     * Return the cross X product (x1 * y2 + y1 * x2) 
     */
    float cross(const bicudo::vec2&, const bicudo::vec2&);

    /*
     * Rotate (vec)
     * Return rotated vec based on radians angle.
     */
    bicudo::vec2 rotate(const bicudo::vec2&, const bicudo::vec2&, float);

    /*
     * Normalize (vec)
     * Return normalized (between -1 and 1) axis values of a vector.
     */
    bicudo::vec2 normalize(const bicudo::vec2&);

    /*
     * Compute matrix orthographic values.
     */
    void orthographic(float*, float, float, float, float);
}

#endif