#include "game_context.h"
#include "api/client/instance.h"
#include "impl/scripts/module_camera.h"
#include "impl/scenes/scene_physic.h"

void game_context::on_start() {
	module_camera* mod_camera = new module_camera();
	this->add_module("module-camera", "Controls camera in game.", (module*) mod_camera);	
}

void game_context::on_update() {
    if (bicudo::current_scene() == nullptr || bicudo::current_scene()->get_name() != "scene-physic") {
        bicudo::set_scene(new scene_physic());
    }
}