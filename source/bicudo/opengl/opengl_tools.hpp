#ifndef BICUDO_OPENGL_TOOLS_H
#define BICUDO_OPENGL_TOOLS_H

#include "GL/glew.h"
#include "bicudo/util/math.hpp"
#include "shader.hpp"
#include <iostream>
#include <vector>
#include <map>

namespace bicudo {
    typedef struct gpudata {
        union {
            struct {
                uint32_t primitive;
                uint32_t w;
                uint32_t h;
                uint32_t z;
                uint32_t format;
                uint32_t channel;
                uint32_t buffer;
                uint32_t type;
            };

            uint32_t data[8];
        };

        inline explicit gpudata() = default;
    } gpudata;

    class buffering {
    public:
        uint32_t buffer_vao {};
        uint32_t buffer_ebo {};
        uint32_t bind_buffer_info[2] {};

        std::map<uint32_t, uint32_t> buffer_map {};
    public:
        uint32_t primitive[2] {GL_TRIANGLES, GL_UNSIGNED_BYTE};
        int32_t stride[3] {};

        uint32_t &operator[](uint32_t key) {
            return this->buffer_map[key];
        }

        void bind(uint32_t key, const bicudo::ivec2 &buffer_info) {
            uint32_t &buffer {this->buffer_map[0]};
            if (buffer == 0) {
                glGenBuffers(1, &buffer);
            }

            glBindBuffer(buffer_info.x, buffer);
            this->bind_buffer_info[0] = buffer_info.x;
            this->bind_buffer_info[1] = buffer_info.y;

            switch (buffer_info.x) {
                case GL_ELEMENT_ARRAY_BUFFER: {
                    this->buffer_ebo = buffer;
                    this->primitive[1] = buffer_info.y;
                    break;
                }

                default: {
                    break;
                }
            }
        }

        template<typename T>
        void send(uint32_t size, const T *p_data, uint32_t mode) const {
            glBufferData(this->bind_buffer_info[0], sizeof(T) * size, p_data, mode);
        }

        void attach(uint32_t shader_slot, int32_t vec_size, const bicudo::ivec2 &bind_stride = {0, 0}) const {
            const void *hack {(void*) (size_t) bind_stride.y};
            glEnableVertexAttribArray(shader_slot);
            glVertexAttribPointer(shader_slot, vec_size, this->bind_buffer_info[1], GL_FALSE, bind_stride.x, hack);
        }

        void invoke() {
            if (this->buffer_vao == 0) {
                glGenVertexArrays(1, &this->buffer_vao);
            }

            glBindVertexArray(this->buffer_vao);

            if (this->buffer_ebo != 0) {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->buffer_ebo);
            }
        }

        void revoke() const {
            glBindVertexArray(0);
        }

        void draw() const {
            if (this->buffer_ebo != 0) {
                const void *hack {(void*) (size_t) this->stride[1]};
                glDrawElements(this->primitive[0], this->stride[0], this->primitive[1], hack);
            } else {
                glDrawArrays(this->primitive[0], this->stride[0], this->stride[1]);
            }
        }

        void delete_buffers() {
            for (auto &[key, value] : this->buffer_map) {
                if (value != 0) {
                    glDeleteBuffers(1, &key);
                }
            }

            this->buffer_map.clear();
        }

        /**
         * Delete a buffer from GPU based in key slot.
         * @param key
         * @return true if buffer is already deleted, else false.
         **/
        bool delete_buffer(uint32_t key) {
            uint32_t &buffer {this->buffer_map[key]};
            bool flag {buffer == 0};

            if (!flag) {
                glDeleteBuffers(1, &buffer);
            }

            this->buffer_map.erase(key);
            return flag;
        }
    };

    class paralleling {
    public:
        uint32_t dimension[3] {1, 1, 1};
        uint32_t work_groups[3] {1, 1, 1};
        uint32_t memory_barrier {GL_ALL_BARRIER_BITS};
        bicudo::shader *p_shader {};

        void attach(uint32_t shader_slot, bicudo::gpudata &texture, uint32_t mode) const {
            /* Same as shader binding slot. */
            glBindImageTexture(shader_slot, texture.buffer, 0, GL_FALSE, 0, mode, texture.format);
        }

        void dispatch() const {
            /* Dispatch & wait task to be finished using memory barrier. */
            glDispatchCompute(this->dimension[0] / this->work_groups[0], this->dimension[1] / this->work_groups[1], this->dimension[2] / this->work_groups[2]);
            glMemoryBarrier(this->memory_barrier);
        }

        void invoke() const {
            this->p_shader->invoke();
        }

        void revoke() const {
            // Same as this->p_shader->revoke()!
            glUseProgram(0);
        }
    };

    class texturing {
    protected:
        std::map<uint32_t, bicudo::gpudata> buffer_map {};
        uint32_t invoke_texture_info[2] {};
    public:
        bicudo::gpudata &operator[](uint32_t key) {
            return this->buffer_map[key];
        }

        template<typename T>
        void send(const bicudo::ivec3 &dimension, const T *p_data, const bicudo::ivec2 &format) {
            bicudo::gpudata &gpudata_texture {this->buffer_map[this->invoke_texture_info[1]]};

            gpudata_texture.w = dimension.x;
            gpudata_texture.h = dimension.y;
            gpudata_texture.z = dimension.z;
            gpudata_texture.format = format.x;
            gpudata_texture.channel = format.y;

            switch (gpudata_texture.type) {
                case GL_TEXTURE_1D: {
                    glTexImage1D(gpudata_texture.type, 0, gpudata_texture.format, gpudata_texture.w, 0, gpudata_texture.channel, gpudata_texture.primitive, p_data);
                    break;
                }

                case GL_TEXTURE_2D: {
                    glTexImage2D(gpudata_texture.type, 0, gpudata_texture.format, gpudata_texture.w, gpudata_texture.h, 0, gpudata_texture.channel, gpudata_texture.primitive, p_data);
                    break;
                }

                case GL_TEXTURE_3D: {
                    glTexImage3D(gpudata_texture.type, 0, gpudata_texture.format, gpudata_texture.w, gpudata_texture.h, gpudata_texture.z, 0, gpudata_texture.channel, gpudata_texture.primitive, p_data);
                    break;
                }
            }
        }

        void invoke(uint32_t key, const bicudo::ivec2 &texture_info) {
            bicudo::gpudata &gpudata_texture {this->buffer_map[key]};
            if (gpudata_texture.buffer == 0) {
                glGenTextures(1, &gpudata_texture.buffer);
            }

            gpudata_texture.type = texture_info.x;
            gpudata_texture.primitive = texture_info.y;

            glBindTexture(texture_info.x, gpudata_texture.buffer);
            this->invoke_texture_info[0] = texture_info.x;
            this->invoke_texture_info[1] = key;
        }

        void revoke() {
            glBindBuffer(this->invoke_texture_info[0], 0);
            this->invoke_texture_info[0] = 0;
            this->invoke_texture_info[1] = 0;
        }

        template<typename T>
        std::vector<T> &get(std::vector<T> &data) {
            bicudo::gpudata &gpudata_texture {this->buffer_map[this->invoke_texture_info[1]]};
            uint32_t channel_size {1};

            switch (gpudata_texture.channel) {
                case GL_RG: {
                    channel_size = 2;
                    break;
                }

                case GL_RGB: {
                    channel_size = 3;
                    break;
                }

                case GL_RGBA: {
                    channel_size = 4;
                    break;
                }
            }

            /* Get array data from texture. */
            data.resize(gpudata_texture.w * gpudata_texture.h * channel_size);
            glGetTexImage(gpudata_texture.type, 0, gpudata_texture.channel, data.data());
        }
    };

    class uniforming {
    public:
        std::map<uint32_t, uint32_t> buffer_map {};
        uint32_t buffer_context_info[2] {};
    public:
        template<typename T>
        void send(int32_t size, const T *p_data, uint32_t flags) {
            glBufferStorage(this->buffer_context_info[0], size * sizeof(T), p_data, flags);
        }

        void invoke(uint32_t key, const bicudo::ivec2 &buffer_type) {
            uint32_t &buffer {this->buffer_map[key]};
            if (buffer == 0) {
                glGenBuffers(1, &buffer);
            }

            glBindBuffer(buffer_type.x, buffer);

            buffer_context_info[0] = buffer_type.x;
            buffer_context_info[1] = buffer_type.y;
        }

        template<typename T>
        T *&get(T *&p_data, int32_t size = 1) {
            return (p_data = glMapBufferRange(this->buffer_context_info[0], 0, sizeof(T) * size, this->buffer_context_info[1]));
        }

        void revoke() {
            glUnmapBuffer(this->buffer_context_info[0]);
            glBindBuffer(this->buffer_context_info[0], 0);

            this->buffer_context_info[0] = 0;
            this->buffer_context_info[1] = 0;
        }
    };
}

#endif