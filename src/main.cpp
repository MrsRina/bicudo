#include "api/client/instance.h"
#include "impl/context/game_context.h"

int main(int argv, char** argc) {
    std::srand(time(0));

    // Just to update.
    game_core::edit_client_details("Bicudo", "2.0");

    // Init the game context.
    game_context* game_cont = new game_context();
    BICUDO->set_game_context((context*) game_cont);
    
    // init, run loop and at end shutdown.
    BICUDO->init();
    BICUDO->mainloop();
    BICUDO->quit();

    // If something not cool happened we can just flag it.
    return game_core::internal_flag;
}