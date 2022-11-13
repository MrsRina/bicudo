#include "bicudo/impl/render/immediate_shape.hpp"
#include "bicudo/gpu/shading_program.hpp"

bicudo::buffering bicudo::immediate_shape::gpu_buffering {};
bicudo::shader bicudo::immediate_shape::shader {};

void bicudo::immediate_shape::init() {
    std::string vertex_shader {bicudo::gl_version};
    vertex_shader += "\n"
                     "layout (location = 0) in vec2 VertexPosition;\n"
                     "layout (location = 1) in vec2 VertexTextureCoords;\n"
                     "out vec4 Rect;\n"
                     "out vec2 TextureCoords;\n"
                     "uniform mat4 MatrixProjection;\n"
                     "uniform vec4 DataRect;\n"
                     "uniform float LayerLever;\n"
                     "void main() {\n"
                     "  gl_Position = MatrixProjection * vec4((VertexPosition * DataRect.zw) + DataRect.xy, layerLevel, 1.0f);\n"
                     "  Rect = DataRect;\n"
                     "  TextureCoords = VertexTextureCoords;\n"
                     "}";

    std::string fragment_shader {bicudo::gl_version};
    vertex_shader += "\n"
                     "layout (location = 0) out vec4 FragColor;\n"
                     "out vec2 TextureCoords;\n"
                     "out vec4 Rect;\n"
                     "uniform vec4 Color;"
                     "void main() {\n"
                     "  FinalColor = Color;\n"
                     "}";

    bicudo::create_shading_program(bicudo::immediate_shape::shader.shading_program_id, {
        {vertex_shader, bicudo::shaderstages::vertex},
        {fragment_shader, bicudo::shaderstages::fragment}
    });
}

void bicudo::immediate_shape::invoke(float initial_depth_testing) {
    this->depth_testing = initial_depth_testing;
}

void bicudo::immediate_shape::prepare(const bicudo::vec4&) {

}

void bicudo::immediate_shape::draw() {

}

void bicudo::immediate_shape::revoke() {

}
