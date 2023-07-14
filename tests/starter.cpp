#include "starter.hpp"
#include <bicudo/platform/openglcontextoverview.hpp>

void scenestarter::on_create() {
    scene::on_create();

    float resources[16] {
        0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };

    uint8_t indices[6] {
        0, 1, 3,
        3, 2, 0
    };

    bicudo::meshdescriptor mesh_descriptor {};
    mesh_descriptor.resource_size = sizeof(resources);
    mesh_descriptor.p_resources = static_cast<void*>(resources);

    mesh_descriptor.indice_size = sizeof(indices);
    mesh_descriptor.indice_type = GL_UNSIGNED_BYTE;
    mesh_descriptor.p_indices = static_cast<void*>(indices);

    mesh_descriptor.attrib_pos = {2, GL_FLOAT, sizeof(float)*4, 0};
    mesh_descriptor.attrib_texcoord = {2, GL_FLOAT, sizeof(float)*4, sizeof(float)*2};

    bicudo::gpufeature *p_triangle = this->loaded_gpu_renderable_list.emplace_back(new bicudo::gpurenderable());
    p_triangle->set_mesh_descriptor(mesh_descriptor);
    p_triangle->set_primitive(GL_TRIANGLES);
    p_triangle->set_draw_stride(6, 0);

    bicudo::pipelineproperty gpu_pipeline_property {};
    gpu_pipeline_property.viewport_count = 1;

    auto &display_size {bicudo::kernel::p_core->p_display_service->get(bicudo::toplevel)->size};
    this->viewport = {0.0f, 0.0f, static_cast<float>(display_size.x), static_cast<float>(display_size.y)};
    gpu_pipeline_property.p_viewports = &this->viewport;
    
    bicudo::gpufeature *p_overlay = this->loaded_gpu_pipeline_list.emplace_back(new bicudo::gpupipeline());
    p_overlay->set_pipeline_property(gpu_pipeline_property);
}

void scenestarter::on_destroy() {
    scene::on_destroy();
}

void scenestarter::on_event(SDL_Event &sdl_event) {
    scene::on_event(sdl_event);
}

void scenestarter::on_update() {
    scene::on_update();
}

void scenestarter::on_render() {
    scene::on_render();
    this->loaded_gpu_pipeline_list.at(0)->invoke();

    for (bicudo::gpufeature *&p_gpu_feature : this->loaded_gpu_renderable_list) {
        p_gpu_feature->invoke();
        p_gpu_feature->draw();
        p_gpu_feature->revoke();
    }

    this->loaded_gpu_pipeline_list.at(0)->revoke();
}

int32_t main(int32_t, char**) {
    /* Init the bicudo core. */
    bicudo::core core {};
    bicudo::createcore(&core);

    bicudo::contextoverview *p_context_overview {new bicudo::openglcontextoverview()};
    p_context_overview->set_opengl_property(3, 4, "#version 450");

    bicudo::displayproperty display_property {};
    display_property.p_title = "hello-bucyd";
    display_property.size = {1280, 800};
    display_property.position = {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED};
    display_property.p_api_context_overview = p_context_overview;

    bicudo::display display {};
    bicudo::createdisplay(&display);
    display.set_display_property(display_property);

    /* Run bicudo core. */
    return core.mainloop();
}