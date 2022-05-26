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

/**
 * Main class of game where everything is processed.
 **/
class game_core {
private:
    /* Main SDL variables. */
    SDL_Window* sdl_window;
    SDL_GLContext sdl_gl_context;

    /* Info variables. */
    static std::string client_name;
    static std::string client_version_str;

    /* The context of all. */
    bool is_running;
    
    uint64_t interval, delta, fps;
    uint64_t previous_ticks, current_ticks, elapsed_ticks, elapsed_frames;

    float render_time;

    /* Start of setup methods. */
    void init_window();
    void init_context();
    void init_services();
    /* End of setup methods. */

    /* Start of main methods called every tick. */
    void on_event(SDL_Event &sdl_event);
    void on_update();
    void on_render();
    /* End of main methods. */
public:
    /* The static variables used in many parts of game. */
    static uint16_t screen_width, screen_height;
    static int16_t internal_flag;

    /* Start of static methods. */
    static void edit_client_details(const std::string &name, const std::string &version_str);
    static void exception();
    /* End of static methods. */

    /* Start of setters and getters. */
    uint64_t get_fps();
    /* End of setters and getters. */

    /* Start of main methods. */
    void refresh();
    void init();
    void quit();
    void mainloop();
    /* End of main methods. */
};