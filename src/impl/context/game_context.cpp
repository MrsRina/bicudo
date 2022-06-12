#include "game_context.h"
#include "api/client/instance.h"
#include "impl/scripts/module_camera.h"
#include "impl/scenes/scene_physic.h"

void game_context::on_start() {
	this->load_module("module-camera", "Controls camera in gaame.", new module_camera());	
}

void game_context::on_update() {
	if (BICUDO->get_scene_manager().get_current_scene() == nullptr || BICUDO->get_scene_manager.get_current_scene().get_name() != "physic-scene") {
		BICUDO->get_scene_manager().start_scene(new scene_physic());
	}
}