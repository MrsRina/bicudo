#include "tessellator.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "api/client/instance.h"

fx draw::batch2d::fx_shape2d;
fx draw::shape2d_builder::fx_shape_builder;

GLuint draw::shape2d_builder::vbo_mesh = 0;
GLuint draw::shape2d_builder::vao = 0;

void draw::init() {
    draw::batch2d::init();
    draw::shape2d_builder::init();
}

void draw::batch2d::init() {
    shader::load(batch2d::fx_shape2d, "data/fx/fx_shape2d.vsh", "data/fx/fx_shape2d.fsh");
}

void draw::batch2d::xy(float x, float y) {
    if (this->allocated_gpu_data[this->sizeof_allocated_gpu_data].skip) {
        return;
    }

    this->allocated_vertices.push_back(x);
    this->allocated_vertices.push_back(y);
    this->sizeof_instanced_allocated_vertexes++;
}

void draw::batch2d::uv(float u, float v) {
    if (this->allocated_gpu_data[this->sizeof_allocated_gpu_data].skip) {
        return;
    }

    this->allocated_coordinates.push_back(u);
    this->allocated_coordinates.push_back(v);
}

void draw::batch2d::invoke() {
    this->sizeof_instanced_allocated_vertexes = 0;
    this->sizeof_allocated_vertexes = 0;
    this->sizeof_allocated_gpu_data = 0;
    this->should_alloc_new_gpu_data = false;
}

void draw::batch2d::revoke() {
    if (this->should_create_buffers) {
        glGenVertexArrays(1, &this->vertex_arr_object);
        glGenBuffers(1, &this->vbo_vertices);
        glGenBuffers(1, &this->vbo_texture_coordinates);

        this->sizeof_previous_allocated_gpu_data = 0;
        this->should_create_buffers = false;
    }

    bool flag = this->should_alloc_new_gpu_data || this->sizeof_allocated_gpu_data != this->sizeof_previous_allocated_gpu_data;

    if (flag) {
        util::log("Batch 2d ticked changed buffer.");
        glBindVertexArray(this->vertex_arr_object);

        // Location 0 of shaders.
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo_vertices);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->allocated_vertices.size(), &this->allocated_vertices[0], GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        // Location 1 of shader.
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo_texture_coordinates);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->allocated_coordinates.size(), &this->allocated_coordinates[0], GL_STATIC_DRAW);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    this->sizeof_previous_allocated_gpu_data = this->sizeof_allocated_gpu_data;
    this->allocated_vertices.clear();
    this->allocated_coordinates.clear();
}

void draw::batch2d::draw() {
    draw::batch2d::fx_shape2d.use();
    draw::batch2d::fx_shape2d.set_mat4x4("u_mat_view", shader::mat4x4_ortho2d);

    glm::mat4 matrix_rotate;
    glm::mat4 matrix_rotate_default = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

    glBindVertexArray(this->vertex_arr_object);

    for (uint32_t i = 0; i < this->sizeof_allocated_gpu_data; i++) {
        gpu_data &data = this->allocated_gpu_data[i];

        if (data.angle != 0.0f) {
            matrix_rotate = glm::mat4(1.0f);
            matrix_rotate = glm::translate(matrix_rotate, glm::vec3(data.rect[2], data.rect[3], 0.0f));
            matrix_rotate = glm::rotate(matrix_rotate, data.angle, glm::vec3(0.0f, 0.0f, 1.0f));
            matrix_rotate = glm::translate(matrix_rotate, glm::vec3(-data.rect[2], -data.rect[3], 0.0f));

            draw::batch2d::fx_shape2d.set_mat4x4("u_mat_rotate", &matrix_rotate[0][0]);
        } else {
            draw::batch2d::fx_shape2d.set_mat4x4("u_mat_rotate", &matrix_rotate_default[0][0]);
        }

        draw::batch2d::fx_shape2d.set_float("u_float_z_depth", data.z_depth);
        draw::batch2d::fx_shape2d.set_vec2f("u_vec_pos", data.rect);
        draw::batch2d::fx_shape2d.set_vec4f("u_vec_color", data.color);

        glDrawArrays(GL_TRIANGLES, data.begin, data.end);
    }

    glBindVertexArray(0);
}

void draw::batch2d::pos(float x, float y, bool skip) {
    gpu_data &data = this->allocated_gpu_data[this->sizeof_allocated_gpu_data];

    data.rect[0] = x;
    data.rect[1] = y;
    data.skip = skip;
}

void draw::batch2d::rect(float x, float y, float w, float h) {
    if (this->allocated_gpu_data[this->sizeof_allocated_gpu_data].skip) {
        return;
    }

    this->xy(x, y);
    this->xy(x, y + h);
    this->xy(x + w, y + h);
    this->xy(x + w, y + h);
    this->xy(x + w, y);
    this->xy(x, y);

    int32_t factor = 0;

    // We can not divide it by 0.
    if (h == 0.0f) {
        this->should_alloc_new_gpu_data = true;
    } else {
        factor = static_cast<int32_t>(w) / static_cast<int32_t>(h);

        if (this->previous_allocated_gpu_data_factor != factor) {
            this->should_alloc_new_gpu_data = true;
        }
    }

    this->allocated_gpu_data[this->sizeof_allocated_gpu_data].factor = factor;
}

void draw::batch2d::modal(float x, float y, float w, float h) {
    if (this->allocated_gpu_data[this->sizeof_allocated_gpu_data].skip) {
        return;
    }

    this->uv(x, y);
    this->uv(x, y + h);
    this->uv(x + w, y + h);
    this->uv(x + w, y + h);
    this->uv(x + w, y);
    this->uv(x, y);
}

void draw::batch2d::color(float r, float g, float b, float a) {
    if (this->allocated_gpu_data[this->sizeof_allocated_gpu_data].skip) {
        return;
    }

    gpu_data &data = this->allocated_gpu_data[this->sizeof_allocated_gpu_data];

    data.color[0] = r;
    data.color[1] = g;
    data.color[2] = b;
    data.color[3] = a;
}

void draw::batch2d::start_instance() {
    gpu_data &data = this->allocated_gpu_data[this->sizeof_allocated_gpu_data];

    data.begin = this->sizeof_allocated_vertexes;
    data.z_depth = 1.0f;
    this->previous_allocated_gpu_data_factor = data.factor;
}

void draw::batch2d::end_instance() {
    if (this->allocated_gpu_data[this->sizeof_allocated_gpu_data].skip) {
        return;
    }

    this->allocated_gpu_data[this->sizeof_allocated_gpu_data].end = this->sizeof_instanced_allocated_vertexes;
    this->sizeof_allocated_vertexes += this->sizeof_instanced_allocated_vertexes;
    this->sizeof_instanced_allocated_vertexes = 0;
    this->sizeof_allocated_gpu_data++;
}

void draw::batch2d::rotate(float angle, math::vec2 center) {
    gpu_data &data = this->allocated_gpu_data[this->sizeof_allocated_gpu_data];

    data.angle = angle;
    data.rect[2] = center.x;
    data.rect[3] = center.y;
}

void draw::shape2d_builder::init() {
    shader::load(draw::shape2d_builder::fx_shape_builder, "data/fx/fx_shape_builder.vsh", "data/fx/fx_shape_builder.fsh");

    float mesh[12] = {
        0.0f, 0.0f, // x, y
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
    };

    // Gen the buffers for send data to GPU.
    glGenVertexArrays(1, &draw::shape2d_builder::vao);
    glGenBuffers(1, &draw::shape2d_builder::vbo_mesh);

    glBindVertexArray(draw::shape2d_builder::vao);
    glEnableVertexAttribArray(0);
    
    // Send a simple mesh normalised to GPU.
    glBindBuffer(GL_ARRAY_BUFFER, draw::shape2d_builder::vbo_mesh);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, mesh, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

    // End the buffers process.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

gpu_data &draw::shape2d_builder::get_gpu_data() {
    return this->concurrent_gpu_data;
}

void draw::shape2d_builder::set_default_depth_dist(float depth_dist) {
    this->default_depth_dist = depth_dist;
}

float draw::shape2d_builder::get_default_depth_dist() {
    return this->default_depth_dist;
}

void draw::shape2d_builder::invoke() {
    this->concurrent_gpu_data.z_depth = this->default_depth_dist;

    // Enable the shader for this tick shape.
    draw::shape2d_builder::fx_shape_builder.use();
    draw::shape2d_builder::fx_shape_builder.set_mat4x4("u_mat_perspective", shader::mat4x4_ortho2d);

    // Enable the VAO object.
    glBindVertexArray(draw::shape2d_builder::vao);
}

void draw::shape2d_builder::build(const draw::shape &mode, const math::vec4 &color, GLuint texture_id) {
    this->enum_flag_shape_mode = mode;
    this->outline_line_thickness = 0;
    this->concurrent_gpu_data.angle = 0.0f;
    this->concurrent_gpu_data.end = 6;
    this->concurrent_gpu_data.z_depth += 0.00001f;

    this->concurrent_gpu_data.color[0] = color.x;
    this->concurrent_gpu_data.color[1] = color.y;
    this->concurrent_gpu_data.color[2] = color.z;
    this->concurrent_gpu_data.color[3] = color.w;

    draw::shape2d_builder::fx_shape_builder.set_float("u_float_depth", this->concurrent_gpu_data.z_depth);
    draw::shape2d_builder::fx_shape_builder.set_vec4f("u_vec_color", this->concurrent_gpu_data.color);

    if (texture_id != 0) {
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glActiveTexture(GL_TEXTURE0);

        draw::shape2d_builder::fx_shape_builder.set_int("u_bool_texture_enabled", true);
        draw::shape2d_builder::fx_shape_builder.set_int("u_sampler_texture_slot", 0);
    }
}

void draw::shape2d_builder::modal(float tx, float ty, float tw, float th) {
    this->concurrent_gpu_data.rect[0] = tx;
    this->concurrent_gpu_data.rect[1] = ty;
    this->concurrent_gpu_data.rect[2] = tw;
    this->concurrent_gpu_data.rect[3] = th;

    draw::shape2d_builder::fx_shape_builder.set_vec4f("u_vec_texture_rect", this->concurrent_gpu_data.rect);
}

void draw::shape2d_builder::rotate(float angle) {
    this->concurrent_gpu_data.angle = angle;
}

void draw::shape2d_builder::outline(int32_t line_thickness) {
    this->outline_line_thickness = line_thickness;
}

void draw::shape2d_builder::draw(float x, float y, float w, float h) {
    this->concurrent_gpu_data.rect[0] = x;
    this->concurrent_gpu_data.rect[1] = y;
    this->concurrent_gpu_data.rect[2] = w;
    this->concurrent_gpu_data.rect[3] = h;

    float cx = x + (w / 2);
    float cy = y + (h / 2);

    this->matrix_rotate = glm::mat4(1.0f);
    this->matrix_rotate = glm::translate(this->matrix_rotate, glm::vec3(cx, cy, 0.0f));
    this->matrix_rotate = glm::rotate(this->matrix_rotate, this->concurrent_gpu_data.angle, glm::vec3(0.0f, 0.0f, 1.0f));
    this->matrix_rotate = glm::translate(this->matrix_rotate, glm::vec3(-cx, -cy, 0.0f));

    draw::shape2d_builder::fx_shape_builder.set_vec4f("u_vec_rect", this->concurrent_gpu_data.rect);
    draw::shape2d_builder::fx_shape_builder.set_mat4x4("u_mat_rotate", &this->matrix_rotate[0][0]);
    draw::shape2d_builder::fx_shape_builder.set_int("u_int_shape_mode_id", this->enum_flag_shape_mode);
    draw::shape2d_builder::fx_shape_builder.set_int("u_int_line_thickness", this->outline_line_thickness);

    glDrawArrays(GL_TRIANGLES, 0, this->concurrent_gpu_data.end);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void draw::shape2d_builder::revoke() {
    glBindVertexArray(0);
    glUseProgram(0);
}