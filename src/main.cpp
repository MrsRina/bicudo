#include "api/client/instance.h"
#include "impl/scripts/loader.h"

int main(int argc, char** argv) {
    game_core::edit_client_details("Bicudo", "1.0");
    loader game_loader;

    BICUDO->init();
    game_loader.init();

    BICUDO->mainloop();
    BICUDO->quit();

    return game_core::internal_flag;
}