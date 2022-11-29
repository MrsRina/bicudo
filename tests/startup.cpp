#include <iostream>
#include <bicudo/bicudo.hpp>
#include "starter.hpp"

void starter::on_create() {
    feature::on_create();

    bicudo::shader shader {};
    bicudo::create(&shader, {
            {"./vertex.vsh", bicudo::shaderstages::vertex},
            {"./geometry.gsh", bicudo::shaderstages::geometry},
            {"./fragment.fsh", bicudo::shaderstages::fragment}
    });
}

void starter::on_destroy() {
    feature::on_destroy();
}

void starter::on_event(bicudo::event &event) {
    scene::on_event(event);

    if ((bicudo::listen("mouse0") || bicudo::listen("mouse1")) && event.native->type == SDL_MOUSEBUTTONDOWN) {
        auto mouse_pos {bicudo::getinput()->get_mouse_pos()};
        auto boo {new bicudo::rigid {mouse_pos, {200, 200}, 1.0f * bicudo::listen("mouse1"), 1.0f, 0.2f}};
    }
}

void starter::on_update() {
    scene::on_update();
}

void starter::on_unsafe_update() {
    scene::on_unsafe_update();
}

int32_t main(int32_t, char**) {
    /* Init Bicudo framework. */
    bicudo::init();

    /* Create the window native surface. */
    bicudo::surface window {};
    bicudo::create(&window);

    window.rect = {bicudo::centered, bicudo::centered, 1280, 800};
    window.tag = "starter - bicudo tests";

    /* Load the default scene. */
    starter *scene {new starter {}};
    bicudo::makecurrent(scene);

    /*
     * Basic, if you need to initialise some external library without init into scene object,
     * you should use this to reduce object virtual method calls.
     *
     * The first ptr is paramater of lambda functional [](void *pdata) {...
     */
    bicudo::mixin post_context_created {nullptr, [](void*) {
        bicudo::print("Post SDL window GL context created!");
    }};

    bicudo::inject(bicudo::runtime::initialisation, post_context_created);
    bicudo::mainloop();

    return 0;
}