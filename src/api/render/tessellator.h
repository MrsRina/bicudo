#pragma once

#include "shader.h"
#include "api/util/util.h"

#ifndef TESSELLATOR_H
#define TESSELLATOR_H

/**
 * GPU data.
 **/
struct gpu_data {
    uint32_t id = 0;

    bool skip = false;
    int32_t factor = 0;

    float rect[4];
    float color[4];
    float z_depth = 1.0f;
    float angle = 0.0f;

    GLint begin = 0;
    GLint end = 0;
};

/**
 * Draw shapes, circles or something you want using the tools.
 **/
namespace draw {
    void init();

    enum shape {
        RECT, CIRCLE
    };

    class batch3d {
    protected:
        static fx fx_shape3d;

        GLuint vbo_mesh_vertices;
        GLuint vbo_mesh_materials_uv;
        GLuint vao;

        std::vector<float> allocated_vertices;
        std::vector<float> allocated_materials_uv;
    public:
        void invoke();
        void coords(float u, float v);
        void vertex(float x, float y, float z);
        void mode(const glm::vec4 &model);
        void draw();
        void revoke();
    };

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

    class shape2d_builder {
    protected:
        static fx fx_shape_builder;
        static GLuint vbo_mesh;
        static GLuint vao;

        gpu_data concurrent_gpu_data;
        int32_t outline_line_thickness;
        float default_depth_dist = 0.0f;

        glm::mat4 matrix_rotate;
        draw::shape enum_flag_shape_mode;
    public:
        static void init();

        void set_default_depth_dist(float depth_dist);
        float get_default_depth_dist();
        gpu_data &get_gpu_data();

        void invoke();
        void build(const draw::shape &mode, const math::vec4 &color, GLuint texture_id = 0);
        void modal(float tx, float ty, float tw, float th);
        void rotate(float angle);
        void outline(int32_t line_thickness);
        void draw(float x, float y, float w, float h);
        void revoke();
    };
}

#endif