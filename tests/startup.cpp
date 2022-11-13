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

int32_t main(int32_t, char**) {
    /* Init Bicudo framework. */
    bicudo::init();

    /* Create the window native surface. */
    bicudo::surface window {};
    bicudo::create(&window);

    window.rect = {bicudo::centered, bicudo::centered, 1280, 800};
    window.tag = "starter - bicudo tests";

    /* Load the default scene. */
    starter *scene {};
    bicudo::makecurrent(scene);
    bicudo::mainloop();

    return 0;
}