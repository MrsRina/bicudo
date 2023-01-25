#ifndef BICUDO_OPENGL_SHADER_H
#define BICUDO_OPENGL_SHADER_H

#include <map>
#include <iostream>
#include <vector>

namespace bicudo {
    struct shading {
        std::string path {};
        uint32_t stage {};
        bool path_is_resource {};
    };

    class shader {
    protected:
        std::map<std::string, uint32_t> shader_location_map {};
    public:
        explicit shader();
        explicit shader(std::string_view shading_name);
        ~shader();

        std::string name {};
        uint32_t buffer_shader_program {};

        void invoke() const;
        void revoke() const;
    };

    bool createshader(bicudo::shader *&p_shader, const std::vector<bicudo::shading> &shading_list);
}

#endif