#include "game_context.h"
#include "api/client/instance.h"
#include "impl/scripts/module_camera.h"
#include "impl/scenes/scene_physic.h"

void game_context::on_start() {
	this->add_module("module-camera", "Controls camera in game.", (module*) new module_camera());	
}

void game_context::on_update() {
	if (game_core::get_display_scene() == nullptr || game_core::get_display_scene()->get_name() != "scene-physic") {
		game_core::display_scene(new scene_physic());
	}
}