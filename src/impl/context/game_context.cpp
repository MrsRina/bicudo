#include "game_context.h"
#include "api/client/instance.h"
#include "impl/scripts/module_camera.h"

void game_context::on_start() {
	this->load_module("module-camera", "Controls camera in gaame.", new module_camera());	
}

void game_context::on_update() {
	if (BICUDO)
}