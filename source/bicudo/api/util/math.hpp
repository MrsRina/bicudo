#ifndef BICUDO_API_UTIL_MATH_H
#define BICUDO_API_UTIL_MATH_H

namespace bicudo {
    extern float dt, unsafe_dt;

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

    struct vec3 {
        float x {}, y {}, z {};
    };

    struct vec4 {
        float x {}, y {}, z {}, w {};
    };

    struct mat4 {
    protected:
        float data[16] {};
    public:
        mat4(float = 0.0f);
        ~mat4();

        float *operator ~();
        float &operator [](char);
    };

    struct matrix {
        static bicudo::mat4 orthographic;
        const static char I11 {0},  I12 {1},  I13 {2},  I14{3},
                          I21 {4},  I22 {5},  I23 {6},  I24{7},
                          I31 {8},  I32 {9},  I33 {10}, I34{11},
                          I41 {12}, I42 {13}, I43 {14}, I44{14};
    };

    struct collideinfo {
        bicudo::vec2 start {}, end {}, normal {};
        float depth {};
    };

    /*
     * Identity matrix (matrix).
     * Create identity matrix 4x4.
     */
    void identity(bicudo::mat4&);

    /*
     * Translate matrix 4x4 (matrix, position)
     * Translate matrix by given a pos.
     */
    void translate(bicudo::mat4&, const bicudo::vec3&);

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
    void orthographic(bicudo::mat4&, float, float, float, float);
}

#endif