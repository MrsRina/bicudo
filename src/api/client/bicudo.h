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
#include "api/feature/feature.h"
#include "api/gui/gui.h"

#include "api/module/module_service.h"
#include "api/scene/scene_service.h"
#include "api/task/task_service.h"

static const uint32_t FEATURE_BUFFER_LIMIT = 256;

/* The update task. */
void update_task(task* raw_task);

#ifndef GAME_CORE_H
#define GAME_CORE_H

/**
 * Main class of game where everything is processed.
 **/
class game_core {
protected:
    /* Main SDL variables. */
    SDL_Window* sdl_window;
    SDL_GLContext sdl_gl_context;

    /* Info variables. */
    static std::string client_name;
    static std::string client_version_str;

    /* The context of all. */
    bool is_running;
    bool should_refresh_features;
    
    uint64_t interval, fps;
    uint64_t previous_ticks, current_ticks, elapsed_ticks, elapsed_frames;

    /* Services. */
    module_service service_module_manager = module_service("Module");
    scene_service service_scene_manager = scene_service("Scene");
    task_service service_task_manager = task_service("Task");

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
    
    // To make new ids.
    uint32_t previous_feature_id_used;
    
    // Gui context in game for inventory or something.
    gui* concurrent_display_gui;
public:
    /* The static variables used in many parts of game. */
    static uint16_t screen_width, screen_height;
    static int16_t internal_flag;

    /* Start of static methods. */
    static void edit_client_details(const std::string &name, const std::string &version_str);
    static void exception();
    static void display(gui* new_gui);
    /* End of static methods. */

    /* Start of setters and getters. */
    void set_concurrent_display_gui(gui* new_gui);
    gui* get_concurrent_gui();

    uint64_t get_fps();

    module_service &get_module_manager();
    scene_service &get_scene_manager();
    task_service &get_task_manager();
    /* End of setters and getters. */

    /* Start of main methods. */
    void refresh();
    void init();
    void quit();
    void mainloop();
    void mainloop_locked_update();
    /* End of main methods. */
};

#endif