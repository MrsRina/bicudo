#pragma once
#include "module.h"
#include "api/service/service.h"

/**
 * Managament for scripts in game.
 **/
class module_manager : public service<module*>, public ifeature {
public:
    /* Start of main methods. */
    module* get_module_by_name(const std::string &module_name);
    module* get_module_by_feature_id(uint32_t feature_id);
    /* End of main methods. */    

    /* Start of override methods. */
    void on_start();
    void on_end();
    void on_event(SDL_Event sdl_event);
    void on_locked_update(uint64_t delta);
    void on_update(uint64_t delta);
    void on_render(float render_time);
    /* End of override methods. */
};