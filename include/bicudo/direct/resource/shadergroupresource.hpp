#ifndef BICUDO_DIRECT_RESOURCE_SHADER_GROUP
#define BICUDO_DIRECT_RESOURCE_SHADER_GROUP

#include "resource.hpp"
#include "bicudo/platform/platform.hpp"
#include <vector>
#include <unordered_map>

namespace bicudo {
    struct shadermodule {
    public:
        const char *p_path {};
        uint32_t stage {};
    };

    class shadergroupresource : public resource {
    protected:
        std::vector<bicudo::shadermodule> loaded_shader_module_list {};
        std::unordered_map<const char*, uint32_t> loaded_uniform_map {};
        uint32_t program {};
    public:
        explicit shadergroupresource(const std::vector<bicudo::shadermodule> &pipeline_shader_module_list);
    public:
        void on_load() override;
        void on_destroy() override;
        uint32_t get_program() override;
    };
}

#endif