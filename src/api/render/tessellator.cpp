#include "tessellator.h"
#include "api/client/instance.h"

#include <glm/gtc/matrix_transform.hpp>

GLuint draw::mesh2d::attribute_material = 0;
GLuint draw::mesh2d::attribute_vertex   = 0;
GLuint draw::mesh2d::draw_mode          = 0;

GLuint draw::mesh2d::buffer_vertex   = 0;
GLuint draw::mesh2d::buffer_material = 0;
GLuint draw::mesh2d::buffer_texture  = 0;
GLuint draw::mesh2d::bind_texture    = 0;

util::color draw::mesh2d::material_color = util::color(0, 0, 0);
uint32_t draw::mesh2d::iterator_vertex   = 0;
uint32_t draw::mesh2d::iterator_material = 0;
uint32_t draw::mesh2d::size_of_draw      = 0;

bool draw::mesh2d::flag_texture = false;
bool draw::mesh2d::flag_fx = false;

fx draw::mesh2d::concurrent_fx;

void draw::init() {
    draw::mesh2d::init();
}

void draw::shape::add_color_to_mesh_material_rgba(util::color &color) {
    float r = color.redf(), g = color.greenf(), b = color.bluef(), a = color.alphaf();
    MESH_ITERATOR = 0;

    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = r;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = g;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = b;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = a;

    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = r;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = g;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = b;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = a;

    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = r;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = g;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = b;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = a;

    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = r;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = g;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = b;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = a;

    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = r;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = g;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = b;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = a;
        
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = r;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = g;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = b;
    MESH_MATERIAL_COLOR_RGBA[MESH_ITERATOR++] = a;
}

void draw::shape::rect(float x, float y, float w, float h, material &material_data) {
    MESH_ITERATOR = 0;

    MESH_RECT_XYZ[MESH_ITERATOR++] = x;
    MESH_RECT_XYZ[MESH_ITERATOR++] = y;
    MESH_RECT_XYZ[MESH_ITERATOR++] = 0;

    MESH_RECT_XYZ[MESH_ITERATOR++] = x;
    MESH_RECT_XYZ[MESH_ITERATOR++] = y + h;
    MESH_RECT_XYZ[MESH_ITERATOR++] = 0;

    MESH_RECT_XYZ[MESH_ITERATOR++] = x + w;
    MESH_RECT_XYZ[MESH_ITERATOR++] = y + h;
    MESH_RECT_XYZ[MESH_ITERATOR++] = 0;

    MESH_RECT_XYZ[MESH_ITERATOR++] = x + w;
    MESH_RECT_XYZ[MESH_ITERATOR++] = y + h;
    MESH_RECT_XYZ[MESH_ITERATOR++] = 0;
    
    MESH_RECT_XYZ[MESH_ITERATOR++] = x + w;
    MESH_RECT_XYZ[MESH_ITERATOR++] = y;
    MESH_RECT_XYZ[MESH_ITERATOR++] = 0;

    MESH_RECT_XYZ[MESH_ITERATOR++] = x;
    MESH_RECT_XYZ[MESH_ITERATOR++] = y;
    MESH_RECT_XYZ[MESH_ITERATOR++] = 0;

    // Start draw us shape.
    draw::mesh2d::batch(GL_TRIANGLES);

    if (material_data.texture.id != 0) {
        draw::mesh2d::material(material_data.texture);
    } else {
        draw::shape::add_color_to_mesh_material_rgba(material_data.color);
    }

    if (!draw::mesh2d::flag_fx) {
        draw::mesh2d::get_fx().use();
    }

    draw::mesh2d::get_fx().set_float("u_center_x", x + (w / 2.0f));
    draw::mesh2d::get_fx().set_float("u_center_y", y + (h / 2.0f));
    draw::mesh2d::draw();
}

void draw::shape::circle(float x, float y, float radius, material &material_data) {
    draw::mesh2d::active_fx();
    draw::mesh2d::get_fx().set_bool("u_set_radius", true);
    draw::mesh2d::get_fx().set_float("u_radius_dist", radius);

    draw::shape::rect(x - (radius / 2), y - (radius / 2), radius, radius, material_data);
}

void draw::shape::shape(math::vec2 &v0, math::vec2 &v1, math::vec2 &v2, math::vec2 &v3, material &material_data) {
    MESH_ITERATOR = 0;

    MESH_RECT_XYZ[MESH_ITERATOR++] = v0.x;
    MESH_RECT_XYZ[MESH_ITERATOR++] = v0.y;
    MESH_RECT_XYZ[MESH_ITERATOR++] = 0;

    MESH_RECT_XYZ[MESH_ITERATOR++] = v3.x;
    MESH_RECT_XYZ[MESH_ITERATOR++] = v3.y;
    MESH_RECT_XYZ[MESH_ITERATOR++] = 0;

    MESH_RECT_XYZ[MESH_ITERATOR++] = v2.x;
    MESH_RECT_XYZ[MESH_ITERATOR++] = v2.y;
    MESH_RECT_XYZ[MESH_ITERATOR++] = 0;

    MESH_RECT_XYZ[MESH_ITERATOR++] = v2.x;
    MESH_RECT_XYZ[MESH_ITERATOR++] = v2.y;
    MESH_RECT_XYZ[MESH_ITERATOR++] = 0;

    MESH_RECT_XYZ[MESH_ITERATOR++] = v1.x;
    MESH_RECT_XYZ[MESH_ITERATOR++] = v1.y;
    MESH_RECT_XYZ[MESH_ITERATOR++] = 0;

    MESH_RECT_XYZ[MESH_ITERATOR++] = v0.x;
    MESH_RECT_XYZ[MESH_ITERATOR++] = v0.y;
    MESH_RECT_XYZ[MESH_ITERATOR++] = 0;

    // Start draw us shape.
    draw::mesh2d::batch(GL_TRIANGLES);

    if (material_data.texture.id != 0) {
        draw::mesh2d::material(material_data.texture);
    } else {
        draw::shape::add_color_to_mesh_material_rgba(material_data.color);
    }

    math::vec2 center = v1 + (v1 - v2);

    if (!draw::mesh2d::flag_fx) {
        draw::mesh2d::get_fx().use();
    }

    draw::mesh2d::get_fx().set_float("u_center_x", center.x);
    draw::mesh2d::get_fx().set_float("u_center_y", center.y);
    draw::mesh2d::draw();
}

void draw::mesh2d::init() {
    glGenBuffers(1, &buffer_vertex);
    glGenBuffers(1, &buffer_material);
    glGenBuffers(1, &buffer_texture);

    glBindBuffer(GL_ARRAY_BUFFER, buffer_vertex);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, MESH_RECT_XYZ, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, buffer_material);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, MESH_MATERIAL_COLOR_RGBA, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, buffer_texture);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, MESH_MATERIAL_TEXTURE_UV, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Set the default shader.
    set_fx(shader::fx_default);

    // Setup sizes.
    iterator_vertex = 18;
    size_of_draw = 6;
}

void draw::mesh2d::batch(GLuint mode) {
    draw_mode = mode;
    flag_texture = false;
    iterator_material = 24;
}

void draw::mesh2d::material(util::texture &texture) {
    flag_texture = true;
    bind_texture = texture.id;
    iterator_material = 12;
}

void draw::mesh2d::material(util::color &color) {
    material_color = color;
}

void draw::mesh2d::set_fx(fx &shader_fx) {
    concurrent_fx = shader_fx;
}

fx &draw::mesh2d::get_fx() {
    return concurrent_fx;
}

void draw::mesh2d::draw() {
    if (!flag_fx) {
        concurrent_fx.use();
    }

    attribute_vertex = glGetAttribLocation(concurrent_fx.program, "attribute_pos");
    attribute_material = glGetAttribLocation(concurrent_fx.program, "attribute_fragcolor");

    concurrent_fx.set_bool("u_set_texture", flag_texture);
    concurrent_fx.set_int("u_active_texture", 0);

    concurrent_fx.set_mat4x4("u_matrix", shader::mat4x4_ortho2d);
    concurrent_fx.set_float("u_viewport_height", shader::mat2x2_viewport[3]);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (flag_texture != 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, bind_texture);
    }

    glEnableVertexAttribArray(attribute_vertex);
    glEnableVertexAttribArray(attribute_material);

    glBindBuffer(GL_ARRAY_BUFFER, buffer_vertex);
    glVertexAttribPointer(attribute_vertex, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * iterator_vertex, MESH_RECT_XYZ);

    glBindBuffer(GL_ARRAY_BUFFER, flag_texture ? buffer_texture : buffer_material);
    glVertexAttribPointer(attribute_material, flag_texture ? 2 : 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * iterator_material, flag_texture ? MESH_MATERIAL_TEXTURE_UV : MESH_MATERIAL_COLOR_RGBA);

    glDrawArrays(draw_mode, 0, (int) size_of_draw);

    concurrent_fx.set_bool("u_set_circle", false);
    concurrent_fx.end();

    flag_fx = false;
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (flag_texture) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void draw::mesh2d::active_fx() {
    concurrent_fx.use();
    flag_fx = true;
}

void draw::mesh3d_instanced::set_fx(fx &shader_fx) {
    if (this->concurrent_shader.program != shader_fx.program) {
        this->concurrent_shader = shader_fx;
        this->attribute_vertex = glGetAttribLocation(this->concurrent_shader.program, "attribute_pos");
    }
}

fx &draw::mesh3d_instanced::get_fx() {
    return this->concurrent_shader;
}

void draw::mesh3d_instanced::init() {
    glGenVertexArrays(1, &this->vao_buffer_list);

    glGenBuffers(1, &this->buffer_material);
    glGenBuffers(1, &this->buffer_shader);
    glBindVertexArray(this->vao_buffer_list);
    glGenBuffers(1, &this->buffer_position);
    glGenBuffers(1, &this->buffer_total);
}

void draw::mesh3d_instanced::draw() {
    this->concurrent_shader.use();
    bicudo::camera()->push(this->concurrent_shader);

    glm::mat4 i = glm::mat4(1.0f);
    i = glm::translate(i, glm::vec3(1.0f, 1.0f, 1.0f));
    this->concurrent_shader.set_mat4x4("u_mat_model", &i[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, this->buffer_position);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void draw::mesh3d_instanced::refresh() {
    glBindVertexArray(this->vao_buffer_list);

    glBindBuffer(GL_ARRAY_BUFFER, this->buffer_position);
    glEnableVertexAttribArray(this->attribute_vertex);
    glVertexAttribPointer(this->attribute_vertex, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->sizeof_vertex, this->linked_vertex_position, GL_STATIC_DRAW);

   // glEnableVertexAttribArray(1);
    //glBindBuffer(GL_ARRAY_BUFFER, this->buffer_material);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->sizeof_material, this->linked_material, GL_STATIC_DRAW);

//    glEnableVertexAttribArray(2);
//    glBindBuffer(GL_ARRAY_BUFFER, this->buffer_shader);
//    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, (void*) 0);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->sizeof_shader, this->linked_shader, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffer_total);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * this->sizeof_mesh, this->linked_buffer, GL_STATIC_DRAW);
}

void draw::mesh3d_instanced::batch() {

}

void draw::mesh3d_instanced::vertex(float *mesh, uint32_t size) {
    this->linked_vertex_position = mesh;
    this->sizeof_vertex = size;
}

void draw::mesh3d_instanced::mesh(float *mesh, uint32_t size) {
    this->linked_buffer = mesh;
    this->sizeof_mesh = size;
}

void draw::mesh3d_instanced::material(float *mesh, uint32_t size) {
    this->linked_material = mesh;
    this->sizeof_material = size;
}

void draw::mesh3d_instanced::shader(float *mesh, uint32_t size) {
    this->linked_shader = mesh;
    this->sizeof_shader = size;
}
