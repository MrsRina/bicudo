#include "api/client/instance.h"

int main(int argc, char** argv) {
    game_core::edit_client_details("Bicudo", "1.0");

    BICUDO->init();
    BICUDO->mainloop();
    BICUDO->quit();

    return game_core::internal_flag;
}