#include "impl/instance/bicudo.h"

int main(int argv, char** argc) {
    game_core::edit_client_details("Bicudo", "1.0.0");

    BICUDO->init();
    BICUDO->mainloop();
    BICUDO->quit();

    return 1;
}
