#include "bicudo/service/service_physic_engine.hpp"
#include "bicudo/physic/physic_sat.hpp"
#include "bicudo/opengl/opengl_context_overview.hpp"

void bicudo::service_physic_engine::on_native_update() {
    /**
     * IMPORTANT NOTES!!
     *
     * 1- The iterations are currently temp. and are not the final result of Bicudo physics engine.
     * 2- GPU parallelism computation will be in main thread, GL context does not allow GL calls
     * inside others place of CPU (except at current context thread).
     * 3- The multi-threading solution will be not the focus, but perhaps I will implement a custom
     * physics loop using multi-threading chunks.
     * 4- Chunks or "iterations groups" are good techniques to improve real time physics simulation,
     * but increase O^2 complexity with good amount of chunks running, not the property solution.
     *
     * Att, Rina.
     **/

    for (int32_t accurate_iterations {}; accurate_iterations < 3; accurate_iterations++) {
        for (bicudo::feature<bicudo::rigid> *&p_feature_rigid_l : this->features) {
            for (bicudo::feature<bicudo::rigid> *&p_feature_rigid_r : this->features) {
                if (p_feature_rigid_l != p_feature_rigid_r && bicudo::checkcollision(p_feature_rigid_r->content, p_feature_rigid_l->content, this->collide_info)) {
                    this->process_displacement_resolution(p_feature_rigid_l->content, p_feature_rigid_r->content);
                }
            }
        }
    }
}

void bicudo::service_physic_engine::on_native_render() {

}

void bicudo::service_physic_engine::process_displacement_resolution(bicudo::rigid &r, bicudo::rigid &l) {

}

void bicudo::service_physic_engine::on_native_init() {
    float mesh[8] {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
    };

    uint8_t index[6] {
        1, 2, 4,
        4, 3, 1
    };

    std::string vsh {bicudo::gl_shading_version};
    vsh += "\n"
           "layout (location = 0) in vec2 VertexPos;\n"
           "layout (location = 1) in vec2 VertexTexCoords;\n"
           ""
           "uniform mat4 MVP;\n"
           "uniform vec4 Rectangle;\n"
           ""
           "out vec4 Rect;\n"
           "out vec2 TexCoords;\n"
           ""
           "void main() {\n"
           "    gl_Position = MVP * vec4((VertexPos.xy * Rectangle.zw) + Rectangle.xy, 0.0f, 1.0f);\n"
           "    Rect = Rectangle;\n"
           "    TexCoords = VertexTexCoords;\n"
           "}\n";

    std::string fsh {bicudo::gl_shading_version};
    fsh += "\n"
           "layout (location = 0) out vec4 FragColor;\n"
           ""
           "in vec2 Rect;\n"
           "in vec2 TexCoords;\n"
           ""
           "uniform vec4 Color;\n"
           ""
           "void main() {\n"
           "    vec4 sum = Color;\n"
           "    FragColor = sum;\n"
           "}\n";

    this->p_shader_debug = new bicudo::shader("physic.debug");
    bicudo::createshader(this->p_shader_debug, {{vsh, GL_VERTEX_SHADER, true}, {fsh, GL_FRAGMENT_SHADER, true}});

    this->buffer.invoke();

    /* Vertex pos layout binding. */
    this->buffer.bind(0, {GL_ARRAY_BUFFER, GL_FLOAT});
    this->buffer.send<float>(sizeof(mesh) / sizeof(float), mesh, GL_STATIC_DRAW);
    this->buffer.attach(0, 2);

    /* Vertex texture coordinates layout binding. */
    this->buffer.bind(1, {GL_ARRAY_BUFFER, GL_FLOAT});
    this->buffer.send<float>(sizeof(mesh) / sizeof(float), mesh, GL_STATIC_DRAW);
    this->buffer.attach(1, 2);

    /* Indexing rendering index mesh. */
    this->buffer.bind(2, {GL_ELEMENT_ARRAY_BUFFER, GL_UNSIGNED_BYTE});
    this->buffer.send<uint8_t>(sizeof(index) / sizeof(uint8_t), index, GL_STATIC_DRAW);
    this->buffer.revoke();
}

void bicudo::service_physic_engine::on_native_quit() {
    this->buffer.delete_buffers();
}
