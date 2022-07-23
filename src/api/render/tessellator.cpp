#include "tessellator.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "api/client/instance.h"

fx draw::batch2d::fx_shape2d;

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
            matrix_rotate = glm::translate(matrix_rotate, glm::vec3(data.pos[2], data.pos[3], 0.0f));
            matrix_rotate = glm::rotate(matrix_rotate, data.angle, glm::vec3(0.0f, 0.0f, 1.0f));
            matrix_rotate = glm::translate(matrix_rotate, glm::vec3(-data.pos[2], -data.pos[3], 0.0f));

            draw::batch2d::fx_shape2d.set_mat4x4("u_mat_rotate", &matrix_rotate[0][0]);
        } else {
            draw::batch2d::fx_shape2d.set_mat4x4("u_mat_rotate", &matrix_rotate_default[0][0]);
        }

        draw::batch2d::fx_shape2d.set_float("u_float_z_depth", data.z_depth);
        draw::batch2d::fx_shape2d.set_vec2f("u_vec_pos", data.pos);
        draw::batch2d::fx_shape2d.set_vec4f("u_vec_color", data.color);

        glDrawArrays(GL_TRIANGLES, data.begin, data.end);
    }

    glBindVertexArray(0);
}

void draw::batch2d::pos(float x, float y, bool skip) {
    gpu_data &data = this->allocated_gpu_data[this->sizeof_allocated_gpu_data];

    data.pos[0] = x;
    data.pos[1] = y;
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
    data.pos[2] = center.x;
    data.pos[3] = center.y;
}
