#pragma once
#include "includes/includes.h"

/**
 * Timer stamp to help in game.
 **/
struct timer_stamp {
    uint32_t previous_ticks;

    void start();
    bool end_if(uint32_t ms);
};

/**
 * File struct to manipule in game.
 **/
struct game_file {
    std::string tag, filename, filedir;
    bool loaded;

    void* data1;
    void* data2;

    game_file(const std::string &_filename, const std::string &_filedir) {
        this->filename = _filename;
        this->filedir = _filedir;
    }

    game_file() {}
};

/**
 * Util to make easy some actions/events and reduce code writing.
 **/
struct util {
    static timer_stamp* timing;

    static bool debug_scene;
    static bool debug_module;

    static void log(std::string string);

    /**
     * Simple load and exists.
     **/
    struct file {
        bool exists(const std::string &path);

        void load(game_file &_game_file);
        void close(game_file &_game_file);
    };

    struct color {
        uint8_t r, g, b, a;

        color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) {
            this->r = red;
            this->g = green;
            this->b = blue;
            this->a = alpha;
        }
    };

    /**
     * Enum to visibility of something.
     **/
    enum visibility {
        LOW_PRIORITY, VISIBLE
    };
};