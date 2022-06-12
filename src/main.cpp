#include "api/client/instance.h"
#include "impl/context/game_context.h"

int main(int argc, char** argv) {
    // Just to update.
    game_core::edit_client_details("Bicudo", "2.0");

    // Init the game context.
    BICUDO->set_game_context((context*) new game_context());
    
    // init, run loop and at end shutdown.
    BICUDO->init();
    BICUDO->mainloop();
    BICUDO->quit();

    // If something not cool happened we can just flag it.
    return game_core::internal_flag;
}