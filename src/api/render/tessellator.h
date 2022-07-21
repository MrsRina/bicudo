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
 * GPU data.
 **/
struct gpu_data {
    uint32_t id;

    float pos[2];
    float color[4];

    GLint index_start;
    GLint index_end;
};

/**
 * Draw shapes, circles or something you want using the tools.
 **/
namespace draw {
    void init();

    class batch2d {
    protected:
        gpu_data allocated_data[2048];

        std::vector<GLfloat> vertices;
        std::vector<GLfloat> coordinates;

        GLuint vertex_arr_object;
        GLuint vertex_buf_object;
    public:
        void add();
        void alloc();
        void draw();
    };
}

#endif