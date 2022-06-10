#include "loader.h"

void loader::init() {
	module_camera* script_module_camera;
	physic_scene* scene_physic;

	this->load_scene("ScenePhysic", "Scene to physic.", scene_physic);
	this->load_module("ModuleCamera", "Script to handler camera.", script_module_camera);
}

void loader::load_module(const std::string &name, const std::string &description, module *feature) {
	feature = new module();
	feature.registry(name, description);

	BICUDO->get_module_manager().registry(feature);
}

void loader::load_scene(const std::string &name, const std::string &description, scene *feature) {
	feature = new scene();
	feature.registry(name, description);

	BICUDO->get_scene_manager().registry(feature);
}