#include "tessellator.h"

GLuint draw::immediate::attribute_material = 0;
GLuint draw::immediate::attribute_vertex   = 0;
GLuint draw::immediate::draw_mode          = 0;

GLuint draw::immediate::buffer_vertex   = 0;
GLuint draw::immediate::buffer_material = 0;
GLuint draw::immediate::buffer_texture  = 0;

GLfloat* draw::immediate::linked_vertex_data   = (GLfloat*) 0;
GLfloat* draw::immediate::linked_material_data = (GLfloat*) 0;

util::color draw::immediate::material_color = util::color(0, 0, 0);
uint32_t draw::immediate::iterator_vertex   = 0;
uint32_t draw::immediate::iterator_material = 0;
uint32_t draw::immediate::size_of_draw      = 0;

float draw::immediate::outline_line_thickness = 0.0f;
bool draw::immediate::flag_ptr = false;
bool draw::immediate::flag_texture = false;

fx draw::immediate::concurrent_fx;

void draw::init() {
    draw::immediate::init();
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
    draw::immediate::batch(GL_TRIANGLES, 6, true);

    if (material_data.texture.id != 0) {
        draw::immediate::material(material_data.texture);
        draw::immediate::material(material_data.uv_coordinates, 12);
    } else {
        draw::shape::add_color_to_mesh_material_rgba(material_data.color);
        draw::immediate::material(MESH_MATERIAL_COLOR_RGBA, 24);
    }

    draw::immediate::get_fx().use();
    draw::immediate::get_fx().set_float("u_center_x", x + (w / 2.0f));
    draw::immediate::get_fx().set_float("u_center_y", y + (h / 2.0f));

    draw::immediate::vertex(MESH_RECT_XYZ, 18);
    draw::immediate::draw();
}

void draw::shape::circle(float x, float y, float radius, material &material_data) {
    float w = radius, h = radius, r = radius / 2.0f;

    draw::immediate::get_fx().use();
    draw::immediate::get_fx().set_bool("u_set_radius", true);
    draw::immediate::get_fx().set_float("u_radius_dist", radius);
    draw::immediate::get_fx().end();

    draw::shape::rect(x, y, w, h, material_data);

    draw::immediate::get_fx().use();
    draw::immediate::get_fx().set_bool("u_radius", false);
    draw::immediate::get_fx().end();
}

void draw::immediate::init() {
    glGenBuffers(1, &buffer_vertex);
    glGenBuffers(1, &buffer_material);

    // Set the default shader.
    set_fx(shader::fx_default);
}

void draw::immediate::outline(float line_thickness) {
    outline_line_thickness = line_thickness;
}

void draw::immediate::batch(GLuint mode, uint32_t size, bool mesh) {
    if (!mesh) {
        linked_vertex_data = new GLfloat[size * 2];
    }

    draw_mode = mode;
    size_of_draw = size;
    flag_ptr = mesh;
    flag_texture = false;
}

void draw::immediate::vertex(GLfloat* vertex, uint32_t size) {
    linked_vertex_data = vertex;
    iterator_vertex = size;
}

void draw::immediate::material(GLfloat* material, uint32_t size) {
    linked_material_data = material;
    iterator_material = size;
}

void draw::immediate::material(util::texture &texture) {
    flag_texture = true;
    buffer_material = texture.id;
}

void draw::immediate::vertex(float x, float y) {
    linked_vertex_data[iterator_material++] = x;
    linked_vertex_data[iterator_material++] = y;
}

void draw::immediate::material(float u, float v) {
    linked_material_data[iterator_material++] = u;
    linked_material_data[iterator_material++] = v;
}
void draw::immediate::color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
    linked_material_data[iterator_material++] = (float) red / 255.0f;
    linked_material_data[iterator_material++] = (float) green / 255.0f;
    linked_material_data[iterator_material++] = (float) blue / 255.0f;
    linked_material_data[iterator_material++] = (float) alpha / 255.0f;
}

void draw::immediate::color(util::color &color) {
    linked_material_data[iterator_material++] = color.redf();
    linked_material_data[iterator_material++] = color.greenf();
    linked_material_data[iterator_material++] = color.bluef();
    linked_material_data[iterator_material++] = color.alphaf();
}

void draw::immediate::set_fx(fx &shader_fx) {
    concurrent_fx = shader_fx;
}


fx &draw::immediate::get_fx() {
    return concurrent_fx;
}

void draw::immediate::draw() {
    concurrent_fx.use();

    attribute_vertex = glGetAttribLocation(concurrent_fx.program, "attribute_pos");
    attribute_material = glGetAttribLocation(concurrent_fx.program, "attribute_fragcolor");

    concurrent_fx.set_bool("u_set_texture", flag_texture);
    concurrent_fx.set_int("u_active_texture", 0);

    if (outline_line_thickness != -1.0f) {
        concurrent_fx.set_bool("u_set_outline", true);
        concurrent_fx.set_float("u_outline_line_thickness", outline_line_thickness);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (flag_texture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, buffer_texture);
    }

    glEnableVertexAttribArray(attribute_vertex);
    glEnableVertexAttribArray(attribute_material);

    glBindBuffer(GL_ARRAY_BUFFER, buffer_vertex);
    glVertexAttribPointer(attribute_vertex, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iterator_vertex, linked_vertex_data, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffer_material);
    glVertexAttribPointer(attribute_material, flag_texture ? 2 : 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iterator_material, linked_material_data, GL_DYNAMIC_DRAW);

    glDrawArrays(draw_mode, 0, size_of_draw);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (flag_texture) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    if (!flag_ptr) {
        delete linked_vertex_data;
        delete linked_material_data;
    }

    outline_line_thickness = -1.0f;
    concurrent_fx.set_bool("u_set_outline", false);
    concurrent_fx.end();
}