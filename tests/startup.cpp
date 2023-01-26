#include <iostream>
#include <bicudo/bicudo.hpp>
#include "starter.hpp"
#include "bicudo/opengl/opengl_context_overview.hpp"

void scene_starter::on_create() {
    scene::on_create();

    bicudo::texturing t {};
    t.invoke(0, {GL_TEXTURE_2D, GL_FLOAT});
    t.send<float>({100, 100, 0}, nullptr, {GL_RGB32F, GL_RGB});
    t.revoke();

    t.invoke(1, {GL_TEXTURE_2D, GL_UNSIGNED_BYTE});
    t.send<uint8_t>({60, 60, 0}, nullptr, {GL_R8UI, GL_RED_INTEGER});
    t.revoke();

    t.invoke(2, {GL_TEXTURE_2D, GL_FLOAT});
    t.send<float>({50, 50, 0}, nullptr, {GL_RGBA32F, GL_RGBA});
    t.revoke();

    glBindTexture(GL_TEXTURE_2D, t[2].buffer);

    bicudo::feature<bicudo::rigid> *p_rigid {new bicudo::feature<bicudo::rigid>()};
    p_rigid->content.size = {200, 200};
    p_rigid->content.move(200, 200);
    bicudo::kernel::p_core->service_physic_engine.add(p_rigid);

    bicudo::feature<bicudo::rigid> *p_rigid_2 {new bicudo::feature<bicudo::rigid>()};
    p_rigid_2->content.size = {200, 200};
    p_rigid_2->content.move(401, 450);
    bicudo::kernel::p_core->service_physic_engine.add(p_rigid_2);
}

void scene_starter::on_destroy() {
    scene::on_destroy();
}

void scene_starter::on_update() {
    scene::on_update();
}

void scene_starter::on_render() {
    scene::on_render();
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
    p_display->content.title = "Hello this is Bicudo-3.";
    p_display->content.flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    p_display->content.opacity = 1.0f;
    bicudo::createdisplay(p_display);

    /* Insert a scene. */
    bicudo::feature<bicudo::scene*> *p_scene {new bicudo::feature<bicudo::scene*>(new scene_starter())};
    bicudo::createscene(p_scene);

    /* Run bicudo core. */
    return p_core->mainloop();
}