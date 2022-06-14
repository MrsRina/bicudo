#pragma once

#include "api/client/context.h"

#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

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