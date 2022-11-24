#include "bicudo/impl/render/immshape.hpp"
#include "bicudo/gpu/shading_program.hpp"
#include "bicudo/bicudo.hpp"

bicudo::buffering bicudo::immshape::gpu_buffering {};
bicudo::shader bicudo::immshape::shader {};

void bicudo::immshape::init() {
    std::string vertex_shader {bicudo::gl_version};
    vertex_shader += "\n"
                     "layout (location = 0) in vec2 VertexPosition;\n"
                     "layout (location = 1) in vec2 VertexTextureCoords;\n"
                     "out vec4 Rect;\n"
                     "out vec2 TextureCoords;\n"
                     "uniform mat4 MatrixProjection;\n"
                     "uniform vec4 DataRect;\n"
                     "uniform float LayerLevel;\n"
                     "void main() {\n"
                     "  gl_Position = MatrixProjection * vec4((VertexPosition * DataRect.zw) + DataRect.xy, LayerLevel, 1);\n"
                     "  Rect = DataRect;\n"
                     "  TextureCoords = VertexTextureCoords;\n"
                     "}";

    std::string fragment_shader {bicudo::gl_version};
    fragment_shader += "\n"
                       "layout (location = 0) out vec4 FragColor;\n"
                       "in vec2 TextureCoords;\n"
                       "in vec4 Rect;\n"
                       "uniform vec4 Color;\n"
                       "void main() {\n"
                       "  FragColor = Color;\n"
                       "}";

    bicudo::create_shading_program(bicudo::immshape::shader.shading_program_id, {
            {vertex_shader, bicudo::shaderstages::vertex},
            {fragment_shader, bicudo::shaderstages::fragment}
    }, false);

    std::vector<float> vertexes {
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0
    };

    bicudo::mesh mesh {vertexes, vertexes};
    auto &buffering {bicudo::immshape::gpu_buffering};
    buffering.invoke();
    buffering.compile_mesh(mesh);
    buffering.revoke();
}

void bicudo::immshape::matrix() {
    auto &shading_program {bicudo::immshape::shader};
    shading_program.use();
    shading_program.set_uniform_matrix4x4("MatrixProjection", bicudo::matrix::orthographic);
    shading_program.unuse();
}

void bicudo::immshape::invoke(float initial_depth_testing) {
    this->depth_testing = initial_depth_testing;
    bicudo::immshape::shader.use();
}

void bicudo::immshape::prepare(float x, float y, float w, float h, const bicudo::vec4 &color) {
    this->rect[0] = x;
    this->rect[1] = y;
    this->rect[2] = w;
    this->rect[3] = h;
    
    this->shape_color[0] = color.x;
    this->shape_color[1] = color.y;
    this->shape_color[2] = color.z;
    this->shape_color[3] = color.w;
}

void bicudo::immshape::rotate(float angle) {
    angular_rotation
}

void bicudo::immshape::draw() {
    auto &shading_program {bicudo::immshape::shader};
    shading_program.set_uniform_vec4("DataRect", this->rect);
    shading_program.set_uniform_vec4("Color", this->shape_color);
    shading_program.set_uniform("LayerLevel", this->depth_testing);
    
    bicudo::immshape::gpu_buffering.draw();
    this->depth_testing += 0.001f;
}

void bicudo::immshape::revoke() {
    bicudo::immshape::shader.unuse();
}
