#pragma once
#include "api/util/util.h"

#ifndef FONT_RENDERER_H
#define FONT_RENDERER_H

class font_renderer {
private:
    game_file font_file;
public:
    /* Start of main methods. */
    void init(const std::string &font_name_or_path);
    void quit();
    /* End of of main methods. */
};

#endif