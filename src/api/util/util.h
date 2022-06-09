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
        static const uint8_t TO_STRING = 0;
        static const uint8_t TO_BYTE = 1;

        static bool exists(const char* path);
        static void* load(const char* path, uint8_t mode = TO_STRING);
    };

    struct color {
        uint8_t r, g, b, a;

        color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) {
            this->r = red;
            this->g = green;
            this->b = blue;
            this->a = alpha;
        }

        void set(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
        void set(uint8_t red, uint8_t green, uint8_t blue);

        float redf();
        float greenf();
        float bluef();
        float alphaf();
    };

    /**
     * Enum to visibility of something.
     **/
    enum visibility {
        LOW_PRIORITY, VISIBLE
    };
};