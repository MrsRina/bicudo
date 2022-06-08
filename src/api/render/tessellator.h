#pragma once

#include ""

#ifndef TESSELLATOR_H
#define TESSELLATOR_H

class tessellator {
protected:
	static GLuint buffer_vertex, buffer_material, buffer_texture;
	static std::vector<GLfloat> concurrent_vertex_data, concurrent_material_data;
public:
	/* Start of main static methods. */
	static void batch()
	/* End of main static methods. */
};

#endif