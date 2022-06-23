#include "tessellator.h"

GLuint draw::mesh2d::attribute_material = 0;
GLuint draw::mesh2d::attribute_vertex   = 0;
GLuint draw::mesh2d::draw_mode         = 0;

GLuint draw::mesh2d::buffer_vertex    = 0;
GLuint draw::mesh2d::buffer_vao       = 0;
GLuint draw::mesh2d::buffer_material  = 0;
GLuint draw::mesh2d::buffer_texture   = 0;
GLuint draw::mesh2d::bind_texture     = 0;

GLfloat* draw::mesh2d::linked_vertex_data   = (GLfloat*) 0;
GLfloat* draw::mesh2d::linked_material_data = (GLfloat*) 0;

util::color draw::mesh2d::material_color = util::color(0, 0, 0);
uint32_t draw::mesh2d::iterator_vertex   = 0;
uint32_t draw::mesh2d::iterator_material = 0;
uint32_t draw::mesh2d::size_of_draw      = 0;

float draw::mesh2d::outline_line_thickness = 0.0f;
bool draw::mesh2d::flag_ptr = false;
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
    draw::mesh2d::batch(GL_TRIANGLES, 6, true);

    if (material_data.texture.id != 0) {
        draw::mesh2d::material(material_data.texture);
        draw::mesh2d::material(material_data.uv_coordinates, 12);
    } else {
        draw::shape::add_color_to_mesh_material_rgba(material_data.color);
        draw::mesh2d::material(MESH_MATERIAL_COLOR_RGBA, 24);
    }

    if (!draw::mesh2d::flag_fx) {
        draw::mesh2d::get_fx().use();
    }

    draw::mesh2d::get_fx().set_float("u_center_x", x + (w / 2.0f));
    draw::mesh2d::get_fx().set_float("u_center_y", y + (h / 2.0f));

    draw::mesh2d::vertex(MESH_RECT_XYZ, 18);
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
    draw::mesh2d::batch(GL_TRIANGLES, 6, true);

    if (material_data.texture.id != 0) {
        draw::mesh2d::material(material_data.texture);
        draw::mesh2d::material(material_data.uv_coordinates, 12);
    } else {
        draw::shape::add_color_to_mesh_material_rgba(material_data.color);
        draw::mesh2d::material(MESH_MATERIAL_COLOR_RGBA, 24);
    }

    math::vec2 center = v1 + (v1 - v2);

    if (!draw::mesh2d::flag_fx) {
        draw::mesh2d::get_fx().use();
    }

    draw::mesh2d::get_fx().set_float("u_center_x", center.x);
    draw::mesh2d::get_fx().set_float("u_center_y", center.y);

    draw::mesh2d::vertex(MESH_RECT_XYZ, 18);
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
}

void draw::mesh2d::outline(float line_thickness) {
    outline_line_thickness = line_thickness;
}

void draw::mesh2d::batch(GLuint mode, uint32_t size, bool mesh) {
    if (!mesh) {
        linked_vertex_data = new GLfloat[size * 2];
    }

    draw_mode = mode;
    size_of_draw = size;
    flag_ptr = mesh;
    flag_texture = false;
}

void draw::mesh2d::vertex(GLfloat* vertex, uint32_t size) {
    linked_vertex_data = vertex;
    iterator_vertex = size;
}

void draw::mesh2d::material(GLfloat* material, uint32_t size) {
    linked_material_data = material;
    iterator_material = size;
}

void draw::mesh2d::material(util::texture &texture) {
    flag_texture = true;
    bind_texture = texture.id;
}

void draw::mesh2d::vertex(float x, float y) {
    linked_vertex_data[iterator_material++] = x;
    linked_vertex_data[iterator_material++] = y;
}

void draw::mesh2d::material(float u, float v) {
    linked_material_data[iterator_material++] = u;
    linked_material_data[iterator_material++] = v;
}
void draw::mesh2d::color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    linked_material_data[iterator_material++] = (float) red / 255.0f;
    linked_material_data[iterator_material++] = (float) green / 255.0f;
    linked_material_data[iterator_material++] = (float) blue / 255.0f;
    linked_material_data[iterator_material++] = (float) alpha / 255.0f;
}

void draw::mesh2d::color(util::color &color) {
    linked_material_data[iterator_material++] = color.redf();
    linked_material_data[iterator_material++] = color.greenf();
    linked_material_data[iterator_material++] = color.bluef();
    linked_material_data[iterator_material++] = color.alphaf();
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
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * iterator_vertex, linked_vertex_data);

    glBindBuffer(GL_ARRAY_BUFFER, flag_texture ? buffer_texture : buffer_material);
    glVertexAttribPointer(attribute_material, flag_texture ? 2 : 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * iterator_material, linked_material_data);

    glDrawArrays(draw_mode, 0, (int) size_of_draw);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (flag_texture) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    if (!flag_ptr) {
        delete linked_vertex_data;
        delete linked_material_data;
    }

    concurrent_fx.set_bool("u_set_circle", false);
    concurrent_fx.end();
    flag_fx = false;

    glDisableVertexAttribArray(attribute_vertex);
    glDisableVertexAttribArray(attribute_material);
}

void draw::mesh2d::flush() {
    size_of_draw = 0;
}

void draw::mesh2d::active_fx() {
    concurrent_fx.use();
    flag_fx = true;
}

void draw::mesh3d_instanced::init() {

}

void draw::mesh3d_instanced::batch() {

}

void draw::mesh3d_instanced::draw() {

}

void draw::mesh3d_instanced::vertex() {

}

void draw::mesh3d_instanced::refresh() {

}
