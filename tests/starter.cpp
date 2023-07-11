#include <iostream>
#include <bicudo/bicudo.hpp>
#include <ctime>
#include "starter.hpp"
#include "bicudo/opengl/openglcontextoverview.hpp"

void scene_starter::on_create() {
    scene::on_create();

    bicudo::feature<bicudo::rigid> *p_solid_rigid {new bicudo::feature<bicudo::rigid>()};
    bicudo::createrigid(p_solid_rigid);

    /* The ground rigid. */
    p_solid_rigid->content.resize(600, 100);
    p_solid_rigid->content.move(400, 700);
    p_solid_rigid->content.acceleration.y = 0.0f; // Remove gravity from rigid.
    p_solid_rigid->content.mass = 0.0f;
    bicudo::kernel::p_core->service_physic_engine.update_mass(&p_solid_rigid->content, 0.0f);

    /* Use current time as seed for random generator. */
    std::srand(std::time(nullptr));
    float randomic_number {};

    /* generate some rigids to do physics testing. */
    for (int32_t it {}; it < 0; it++) {
        auto *p_feature_rigid {new bicudo::feature<bicudo::rigid>()};
        auto &rigid {p_feature_rigid->content};
        bicudo::createrigid(p_feature_rigid);

        randomic_number = std::rand() % 600;
        rigid.resize(randomic_number, randomic_number);

        randomic_number = std::rand() % 600;
        rigid.move(randomic_number, randomic_number);
    }

    bicudo::gpufeature *p_triangle = this->loaded_gpu_renderable_list.emplace_back(new bicudo::gpurenderable());
    bicudo::mesh mesh {};

    mesh.begin(0);
    mesh.append_float(bicudo::layout::position, {0.0f, 0.0f});
    mesh.append_float(bicudo::layout::position, {0.0f, 1.0f});
    mesh.append_float(bicudo::layout::position, {1.0f, 1.0f});

    p_triangle->set_mesh(mesh);
    p_triangle->set_primitive(bicudo::primitive::triangles);
    p_triangle->set_draw_stride(6, 0);

    bicudo::gpufeature *p_overlay = this->loaded_gpu_pipeline_list.emplace_back(new bicudo::gpupipeline());
    bicudo::pipelineproperty gpu_pipepiline_property {};

    gpu_pipepiline_property.viewport_count = 1;
    gpu_pipepiline_property.p_viewports = &bicudo::kernel::p_core->service_display.get_display(0).rect;
    p_overlay->set_pipeline_property(gpu_pipepiline_property);
}

void scene_starter::on_destroy() {
    scene::on_destroy();
}

void scene_starter::on_event(SDL_Event &sdl_event) {
    scene::on_event(sdl_event);
}

void scene_starter::on_update() {
    scene::on_update();
}

void scene_starter::on_render() {
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
    /* Specify vendor GL context. */
    bicudo::gl_minor_version = 4;
    bicudo::gl_major_version = 4;
    bicudo::gl_shading_version = "#version 450";

    /* Init the bicudo core. */
    bicudo::core *p_core {new bicudo::core()};
    bicudo::createcore(p_core);

    /* Create a display. */
    bicudo::feature<bicudo::display> *p_display {new bicudo::feature<bicudo::display>()};
    p_display->content.rect[2] = 1280;
    p_display->content.rect[3] = 800;
    p_display->content.title = "Hello this is Bicudo 3";
    p_display->content.flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    p_display->content.opacity = 1.0f;
    bicudo::createdisplay(p_display);

    /* Insert a scene. */
    bicudo::feature<bicudo::scene*> *p_scene {new bicudo::feature<bicudo::scene*>(new scene_starter())};
    bicudo::createscene(p_scene);

    /* Run bicudo core. */
    return p_core->mainloop();
}