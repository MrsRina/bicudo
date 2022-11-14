#ifndef BICUDO_GPU_GLIMPL_H
#define BICUDO_GPU_GLIMPL_H

#include <iostream>

namespace bicudo {
	class glimpl {
	protected:
        const int32_t minor_opengl_version {3}, major_opengl_version {4};
		int32_t viewport_width {}, viewport_height {};
		float absolute_surface_color[3] {0.0f, 0.0f, 0.0f};
	public:
		void prepare_opengl_attributes();
		void create_opengl_context();

		void update_absolute_surface_color(float, float, float);
		void update_viewport_size(int32_t, int32_t);
		void clear_buffers();
	};
}

#endif