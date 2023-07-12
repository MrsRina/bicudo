#ifndef BICUDO_PLATFORM_H
#define BICUDO_PLATFORM_H

#include <SDL2/SDL.h>

#if defined (WIN32)
#include <gl/glew.h>
#include <cinttypes>
#elif defined (LINUX)
#include "GL/glew.h"
#include <cinttypes>
#endif

#endif