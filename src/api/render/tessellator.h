#pragma once

#include "shader.h"
#include "api/util/util.h"

#ifndef TESSELLATOR_H
#define TESSELLATOR_H

static float MESH_RECT_XYZ[18];
static float MESH_MATERIAL_COLOR_RGBA[24];
static float MESH_MATERIAL_TEXTURE_UV[12];

static uint8_t MESH_ITERATOR;

/**
 * Material to stuff.
 **/
struct material {
	util::color color = util::color(255, 0, 255, 255);
	util::texture texture;

	float* uv_coordinates;
};

/**
 * Draw shapes, circles or something you want using the tools.
 **/
namespace draw {
    void init();

    /**
     * Draw shapes using mesh mode.
     **/
    namespace shape {
        void rect(float x, float y, float w, float h, material &material_data);
        void circle(float x, float y, float radius, material &material_data);
        void add_color_to_mesh_material_rgba(util::color &color);
    }

    /**
     * 2D tessellator.
     **/
    class mesh {
    protected:
        static GLuint attribute_vertex, attribute_material, attribute_material_color;
        static GLuint draw_mode;

        static GLuint buffer_vertex, buffer_material, buffer_texture, bind_texture;
        static GLfloat *linked_vertex_data, *linked_material_data;

        static util::color material_color;
        static uint32_t iterator_vertex, iterator_material, size_of_draw;

        static float outline_line_thickness;
        static bool flag_ptr, flag_texture;
        static fx concurrent_fx;
    public:
        /* Start of main static methods. */
        static void init();
        static void outline(float line_thickness);
        static void batch(GLuint mode, uint32_t size, bool mesh = false);

        static void vertex(GLfloat* vertex, uint32_t size);
        static void material(GLfloat* material, uint32_t size);

        static void vertex(float x, float y);
        static void material(float u, float v);
        static void material(util::texture &texture);

        static void color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
        static void color(util::color &color);

        static void set_fx(fx &shader_fx);
        static fx &get_fx();
        static void draw();
        /* End of main static methods. */
    };
}

#endif