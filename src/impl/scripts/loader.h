#pragma once

#include "api/module/module.h"
#include "api/scene/scene.h"

#ifndef LOADER_H
#define LOADER_H

struct loader {
	void init();

	void load_scene(const std::string &name, const std::string &description, scene *feature);
	void load_module(const std::string &name, const std::string &description, module *feature);
};

#endif