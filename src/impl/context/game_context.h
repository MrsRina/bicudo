#pragma once

#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include "api/client/context.h"

/**
 * Where everything is going on.
 **/
class game_context : public context {
public:
	game_context() : context() {}

	/* Start of override methods. */
	void on_start();
	void on_update();
	/* End of override methods. */
};

#endif