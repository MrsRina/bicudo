#include <iostream>
#include <bicudo/bicudo.hpp>

int32_t main(int32_t, char**) {
    /* Init Bicudo framework. */
    bicudo::init();

    /* Create the window native surface. */
    bicudo::surface window {};
    bicudo::create(&window);

    window.rect = {bicudo::centered, bicudo::centered, 1280, 800};
    window.tag = "starter - bicudo tests";

    /* Create shader program and link shaders. */
    bicudo::shader shader {};
    bicudo::create(&shader, {
        {"./v.vsh", bicudo::shaderstages::vertex},
        {"./v.gsh", bicudo::shaderstages::geometry},
        {"./v.fsh", bicudo::shaderstages::fragment},
        {"./v.csh", bicudo::shaderstages::computed}
    });

    bicudo::mainloop();
    return true;
}