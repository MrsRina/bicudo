#ifndef BICUDO_IMPL_INPUT_H
#define BICUDO_IMPL_INPUT_H

#include <vector>
#include <map>
#include "bicudo/api/event/event.hpp"
#include "bicudo/api/util/math.hpp"
#include <iostream>

namespace bicudo {
    class input {
    protected:
        std::map<std::string, bool> input_map {};
        std::vector<std::string> loaded_input_list {};
        bicudo::vec2 mouse_pos {}, finger_pos {};
    public:
        bicudo::vec2 &get_mouse_pos();
        bicudo::vec2 &get_finger_pos();

        bool listen(std::string_view);
        void on_native_event(bicudo::event&);
        void on_native_update();
    };
}

#endif