#ifndef BICUDO_GRAPHICS_MEMORY_METADATA_H
#define BICUDO_GRAPHICS_MEMORY_METADATA_H

#include <functional>

namespace bicudo {
    struct memorymetadata {
        std::function<void(void*)> realloc {};
        std::function<void(void*)> draw {};
        void *p_gpu_feature {};
    }; 
}

#endif