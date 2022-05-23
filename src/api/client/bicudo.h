/**
 * @author Rina
 * @since 23/05/22
 * 
 * Please I love credits <3, many of things that I do, others "devs"
 * skid and stole from me (:C this make me very sad & you do not
 * want to see a girl sad), so I only want your respect.
 **/
#pragma once
#include "includes/includes.h"
#include <SDL2/SDL.h>

/**
 * Main class of game where everything is processed.
 **/
class game_core {
protected:
    /* Main SDL variables. */
    SDL_Window* sdl_window;
    SDL_GLContext* sdl_gl_context;

    /* Info variables. */
    static std::string client_name;
    static std::string client_version_str;

    /* Start of setup methods. */
    void init_window();
    void init_context();
    void init_services();
    /* End of setup methods. */
public:
    /* Start of static methods. */
    static void edit_client_details(const std::string &name, const std::string &version_str);
    /* End of static methods. */

    /* Start of setters and getters. */
    /* End of setters and getters. */

    /* Start of main methods. */
    void init();
    void quit();

    void mainloop();
    /* End of main methods. */
};