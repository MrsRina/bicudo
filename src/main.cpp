#include "api/client/instance.h"
#include "impl/context/game_context.h"
#include <ekg/ekg.hpp>

int main(int argv, char** argc) {
    std::srand(time(nullptr));

    // Just to update.
    game_core::edit_client_details("Bicudo", "3.0.0");

    // Init the game context.
    auto* game_cont = new game_context();
    BICUDO->set_game_context((context*) game_cont);
    
    // init, run loop and at end shutdown.
    BICUDO->init();
    BICUDO->mainloop();
    BICUDO->quit();

    // If something not cool happened we can just flag it.
    return game_core::internal_flag;
}