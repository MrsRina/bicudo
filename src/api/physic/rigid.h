#pragma once

#ifndef RIGID_H
#define RIGID_H

#include "rigid/rigid2d_rectangle.h"

bool rigid2d_rect_collide_with_rect(rigid2d_rectangle* r1, rigid2d_rectangle* r2);
void rigid2d_solve_collide(rigid2d* &r1, rigid2d* &r2);
bool rigid2d_collide_with_point(rigid2d* &r, float x, float y);

#endif