#ifndef BICUDO_IMPL_RENDER_IMMEDIATE_SHAPE_H
#define BICUDO_IMPL_RENDER_IMMEDIATE_SHAPE_H

#include "bicudo/gpu/buffering.hpp"
#include "bicudo/api/shader/shader.hpp"
#include "bicudo/api/util/math.hpp"

namespace bicudo {
    class immediate_shape {
    protected:
        static bicudo::shader shader;
        static bicudo::buffering gpu_buffering;

        float color[4] {}, rect[4] {};
        float depth_testing {};
    public:
        static void init();

        void invoke(float = 0.0f);
        void prepare(const bicudo::vec4&);
        void draw();
        void revoke();
    };
}

#endif