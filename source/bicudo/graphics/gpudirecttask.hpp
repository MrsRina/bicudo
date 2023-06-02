#ifndef BICUDO_GRAPHICS_GPU_DIRECT_TASK_H
#define BICUDO_GRAPHICS_GPU_DIRECT_TASK_H

#include <functional>

namespace bicudo {
    struct gpudirecttask {
    public:
        std::function<void(void*)> fun {};
        void *p_gpu_feature {};
    public:
        inline explicit gpudirecttask(void *p_gpu_featured, const std::function<void(void*)> &const_fun) : fun(const_fun), p_gpu_feature(p_gpu_featured) {};
    }; 
}

#endif