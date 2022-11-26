#ifndef BICUDO_IMPL_RENDER_IMMSHAPE_H
#define BICUDO_IMPL_RENDER_IMMSHAPE_H

#include "bicudo/gpu/buffering.hpp"
#include "bicudo/api/shader/shader.hpp"
#include "bicudo/api/util/math.hpp"

namespace bicudo {
    class immshape {
    protected:
        static bicudo::shader shader;
        static bicudo::buffering gpu_buffering;

        float shape_color[4] {}, rect[4] {};
        float depth_testing {}, angular_amount {};
        bicudo::mat4 model {};
    public:
        static void init();
        static void matrix();

        void invoke(float = 0.0f);
        void prepare(float, float, float, float, const bicudo::vec4&);
        void rotate(float);
        void draw();
        void revoke();
    };
}

#endif