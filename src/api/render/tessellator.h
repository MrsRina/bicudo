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
 * GPU data.
 **/
struct gpu_data {
    uint32_t id = 0;

    bool skip = false;
    int32_t factor = 0;

    float pos[4];
    float color[4];
    float z_depth;
    float angle;

    GLint begin = 0;
    GLint end = 0;
};

/**
 * Draw shapes, circles or something you want using the tools.
 **/
namespace draw {
    void init();

    class batch2d {
    protected:
        gpu_data allocated_gpu_data[2048];
        uint32_t sizeof_allocated_gpu_data;
        uint32_t sizeof_previous_allocated_gpu_data;

        std::vector<float> allocated_vertices;
        std::vector<float> allocated_coordinates;

        GLint sizeof_instanced_allocated_vertexes;
        GLint sizeof_allocated_vertexes;

        GLuint vertex_arr_object;
        GLuint vbo_vertices;
        GLuint vbo_texture_coordinates;

        static fx fx_shape2d;

        int32_t previous_allocated_gpu_data_factor;
        bool should_alloc_new_gpu_data;
        bool should_create_buffers = true;
        bool should_skip_data = false;
    public:
        static void init();

        void start_instance();
        void pos(float x, float y, bool skip = false);
        void color(float r, float g, float b, float a);
        void rect(float x, float y, float w, float h);
        void modal(float x, float y, float w, float h);
        void rotate(float angle, math::vec2 center);
        void end_instance();
        void xy(float x, float y);
        void uv(float u, float v);
        void invoke();
        void revoke();
        void draw();
    };
}

#endif