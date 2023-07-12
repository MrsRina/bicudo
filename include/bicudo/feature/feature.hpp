#ifndef BICUDO_FEATURE_H
#define BICUDO_FEATURE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <type_traits>

namespace bicudo {
    template<typename T>
    class feature {
    protected:
    public:
        explicit feature() = default;
        explicit feature(T instance) {
            this->content = instance;
        }

        ~feature() {
            if (std::is_pointer<T>::value) {
                delete this->content;
            }
        }

        std::string tag {};
        T content;
    };
}

#endif