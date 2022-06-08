#pragma once

#include "includes/includes.h"

#ifndef TESSELLATOR_H
#define TESSELLATOR_H

class tessellator {
protected:
	static GLuint buffer_vertex, buffer_material, buffer_texture;
	static GLfloat* linked_vertex_data, linked_material_data;
	
	static util::color material_color;
	static uint32_t iterator_vertex, iterator_material;
public:
	/* Start of main static methods. */
	static void init();
	static void batch(GLuint mode, uint32_t size);

	static void vertex(GLfloat* vertex, uint32_t size);
	static void material(GLfloat* material, uint32_t size);

	static void vertex(float x, float y);
	static void material(float u, float v);

	static void color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
	static void color(util::color color);

	static void draw();
	/* End of main static methods. */
};

#endif