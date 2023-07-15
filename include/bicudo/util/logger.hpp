#ifndef BICUDO_UTIL_LOG_H
#define BICUDO_UTIL_LOG_H

#include <iostream>
#include <sstream>

namespace bicudo {
    struct log {
    protected:
        std::ostringstream o_string_stream {}; 
    public:
        explicit log() {
            this->o_string_stream << "--- [B]icudo.Log - ";
        };

        ~log() {
            std::cout << this->o_string_stream.str() << '\n';
        }

        template<typename t>
        bicudo::log &operator<<(t message) {
            this->o_string_stream << message;
            return *this;
        }
    };
}

#define bassert(condition, message) \
    if (!(condition)) { \
        std::cerr << "--- [B]icudo.Log - Assert failed: " << #condition << ", " << message << std::endl; \
    } \

#endif