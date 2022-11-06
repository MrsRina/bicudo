#include <iostream>
#include <bicudo/bicudo.hpp>

int32_t main(int32_t, char**) {
    /* Init Bicudo framework. */
    bicudo::init();

    /* Create the window native surface. */
    bicudo::surface_native window {};
    bicudo::create(&window);

    window.rect = {bicudo::centered, bicudo::centered, 1280, 800};

    return true;
}