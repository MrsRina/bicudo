#include "tessellator.h"

GLuint draw::immediate::attribute_material = 0;
GLuint draw::immediate::attribute_vertex = 0;
GLuint draw::immediate::draw_mode        = 0;

GLuint draw::immediate::buffer_vertex   = 0;
GLuint draw::immediate::buffer_material = 0;
GLuint draw::immediate::buffer_texture  = 0;

GLfloat* draw::immediate::linked_vertex_data   = (GLfloat*) 0;
GLfloat* draw::immediate::linked_material_data = (GLfloat*) 0;

util::color draw::immediate::material_color = util::color(0, 0, 0);
uint32_t draw::immediate::iterator_vertex   = 0;
uint32_t draw::immediate::iterator_material = 0;
uint32_t draw::immediate::size_of_draw      = 0;

bool draw::immediate::flag_ptr = false;
bool draw::immediate::flag_texture = false;
fx draw::immediate::concurrent_fx;

void draw::immediate::init() {
    glGenBuffers(1, &buffer_vertex);
    glGenBuffers(1, &buffer_material);
}

void draw::immediate::batch(GLuint mode, uint32_t size, bool mesh) {
    if (!mesh) {
        linked_vertex_data = new GLfloat[size * 2];
    }

    size_of_draw = size;
    flag_ptr = mesh;
    flag_texture = true;
}

void draw::immediate::vertex(GLfloat* vertex, uint32_t size) {
    linked_vertex_data = vertex;
    iterator_vertex = size;
}

void draw::immediate::material(GLfloat* material, uint32_t size) {
    linked_material_data = material;
    iterator_material = size;
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

void draw::immediate::color(util::color color) {
    linked_material_data[iterator_material++] = color.redf();
    linked_material_data[iterator_material++] = color.greenf();
    linked_material_data[iterator_material++] = color.bluef();
    linked_material_data[iterator_material++] = color.alphaf();
}

void draw::immediate::set_fx(fx &shader_fx) {
    concurrent_fx = shader_fx;
}

void draw::immediate::draw() {
    concurrent_fx.use();

    attribute_vertex = glGetAttribLocation(concurrent_fx.program, "attribute_pos");
    attribute_material = glGetAttribLocation(concurrent_fx.program, "attribute_fragcolor");

    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);

    // Set proj.
    concurrent_fx.set_mat4x4("u_matrix", shader::mat4x4_ortho2d);
    concurrent_fx.set_bool("u_set_texture", flag_texture);

    if (flag_texture) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, buffer_texture);
    }
    
    glEnableVertexAttribArray(attribute_vertex);
    glEnableVertexAttribArray(attribute_material);

    glBindBuffer(GL_ARRAY_BUFFER, buffer_vertex);
    glVertexAttribPointer(GL_ARRAY_BUFFER, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iterator_vertex, linked_vertex_data, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffer_material);
    glVertexAttribPointer(GL_ARRAY_BUFFER, flag_texture ? 2 : 4, GL_FLOAT, GL_FALSE, 0, (void*) 0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * iterator_material, linked_material_data, GL_DYNAMIC_DRAW);

    glDrawArrays(draw_mode, 0, size_of_draw);
    
    if (flag_texture) {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    if (!flag_ptr) {
        delete linked_vertex_data;
        delete linked_material_data;
    }
}