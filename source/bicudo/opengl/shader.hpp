#ifndef BICUDO_OPENGL_SHADER_H
#define BICUDO_OPENGL_SHADER_H

#include <map>
#include <iostream>

namespace bicudo {
    class shader {
    protected:
        uint32_t buffer_shader_program {};
        std::map<std::string, uint32_t> shader_location_map {};
    public:
        explicit shader();
        ~shader();

        void invoke() const;
        void revoke() const;
    };
}

#endif