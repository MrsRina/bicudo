#include "starter.hpp"
#include <bicudo/platform/openglcontextoverview.hpp>

void scenestarter::on_create() {
    scene::on_create();

    bicudo::resource *p_overlay_resources[] {
        new bicudo::shadergroupresource({{
            .p_path = "./data/fx/overlay.vsh.glsl",
            .stage = GL_VERTEX_SHADER
        }, {
            .p_path = "./data/fx/overlay.fsh.glsl",
            .stage = GL_FRAGMENT_SHADER
        }})
    };

    bicudo::assetdescriptor overlay_descriptor {
        .p_tag = "overlay",
        .resource_count = 1,
        .pp_resources = p_overlay_resources
    };

    bicudo::createasset(overlay_descriptor, &this->overlay_asset);
    return;

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
    mesh_descriptor.p_resources = resources;

    mesh_descriptor.indice_size = sizeof(indices);
    mesh_descriptor.indice_type = GL_UNSIGNED_BYTE;
    mesh_descriptor.p_indices = indices;

    mesh_descriptor.attrib_pos = {
        .location = 0,
        .size     = 2,
        .type     = GL_FLOAT,
        .stride   = sizeof(float)*4,
        .offset   = 0
    };

    mesh_descriptor.attrib_texcoord = {
        .location = 1,
        .size     = 2,
        .type     = GL_FLOAT, 
        .stride   = sizeof(float)*4, 
        .offset   = sizeof(float)*2
    };

    bicudo::gpufeature *p_triangle = this->loaded_gpu_renderable_list.emplace_back(new bicudo::gpurenderable());
    p_triangle->set_mesh_descriptor(mesh_descriptor);
    p_triangle->set_primitive(GL_TRIANGLES);
    p_triangle->set_draw_stride(6, 0);

    uint32_t overlay_programs[] {
        bicudo::getasset("overlay")->resources.at(0)->get_program()
    };

    bicudo::pipelineproperty gpu_pipeline_property {};
    gpu_pipeline_property.viewport_count = 1;
    gpu_pipeline_property.render_layer_count = 1;
    gpu_pipeline_property.p_render_layers = overlay_programs;

    auto &display_size {bicudo::kernel::p_core->p_display_service->get(bicudo::stack::toplevel)->size};
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
    return;
    scene::on_render();

    glViewport(this->viewport.x, this->viewport.y, this->viewport.z, this->viewport.w);
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
    bicudo::displayservice display_service {};
    bicudo::sceneservice scene_service {};
    bicudo::assetservice asset_service {};

    bicudo::coreproperty core_property {
        .p_display_service = &display_service,
        .p_scene_service = &scene_service,
        .p_asset_service = &asset_service
    };

    bicudo::core core {};
    bicudo::createcore(core_property, &core);

    bicudo::contextoverview *p_context_overview {new bicudo::openglcontextoverview()};
    p_context_overview->set_opengl_property(3, 4, "#version 450");

    bicudo::displayproperty display_property {};
    display_property.p_title = "hello-bucyd";
    display_property.size = {1280, 800};
    display_property.position = {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED};
    display_property.p_api_context_overview = p_context_overview;

    bicudo::display display {};
    bicudo::createdisplay(display_property, &display);

    bicudo::scene *p_scene_starter {new scenestarter()};
    bicudo::createscene(p_scene_starter);
    bicudo::startscene(p_scene_starter, true);

    /* Run bicudo core. */
    return core.mainloop();
}