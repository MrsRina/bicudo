#include "bicudo/impl/input/input.hpp"
#include "bicudo/api/util/log.hpp"

void bicudo::input::on_native_event(bicudo::event &event) {
    switch (event.native->type) {
        // todo finger position and stuff related

        case SDL_MOUSEMOTION: {
            this->mouse_pos.x = static_cast<float>(event.native->motion.x);
            this->mouse_pos.y = static_cast<float>(event.native->motion.y);

            break;
        }

        case SDL_MOUSEBUTTONUP: {
            this->input_map["mouse-up"] = true;
            this->input_map["mouse"] = false;

            this->mouse_pos.x = static_cast<float>(event.native->button.x);
            this->mouse_pos.y = static_cast<float>(event.native->button.y);

            switch (event.native->button.button) {
                case SDL_BUTTON_LEFT: {
                    this->input_map["mouse0-up"] = true;
                    this->input_map["mouse0"] = false;
                    this->loaded_input_list.push_back("mouse0-up");
                    break;
                }

                case SDL_BUTTON_RIGHT: {
                    this->input_map["mouse2-up"] = true;
                    this->input_map["mouse2"] = false;
                    this->loaded_input_list.push_back("mouse2-up");
                    break;
                }

                case SDL_BUTTON_MIDDLE: {
                    this->input_map["mouse1-up"] = true;
                    this->input_map["mouse1"] = false;
                    this->loaded_input_list.push_back("mouse1-up");
                    break;
                }

                default: {
                    int32_t button_id {event.native->button.button};
                    std::string input_tag {"mouse"};

                    input_tag += std::to_string(button_id);
                    this->input_map[input_tag] = false;

                    input_tag += "-up";
                    this->input_map[input_tag] = true;
                    this->loaded_input_list.push_back(input_tag);
                }
            }

            break;
        }

        case SDL_MOUSEBUTTONDOWN: {
            this->input_map["mouse"] = true;
            this->mouse_pos.x = static_cast<float>(event.native->button.x);
            this->mouse_pos.y = static_cast<float>(event.native->button.y);

            switch (event.native->button.button) {
                case SDL_BUTTON_LEFT: {
                    this->input_map["mouse0"] = true;
                    break;
                }

                case SDL_BUTTON_RIGHT: {
                    this->input_map["mouse2"] = true;
                    break;
                }

                case SDL_BUTTON_MIDDLE: {
                    this->input_map["mouse1"] = true;
                    break;
                }

                default: {
                    int32_t button_id {event.native->button.button};
                    std::string input_tag {"mouse"};

                    input_tag += std::to_string(button_id);
                    this->input_map[input_tag] = true;
                }
            }

            break;
        }
    }
}

bool bicudo::input::listen(std::string_view input_name) {
    return this->input_map[input_name.data()];
}

bicudo::vec2 &bicudo::input::get_mouse_pos() {
    return this->mouse_pos;
}

bicudo::vec2 &bicudo::input::get_finger_pos() {
    return this->finger_pos;
}

void bicudo::input::on_native_update() {
    if (!this->loaded_input_list.empty()) {
        this->loaded_input_list.clear();
        for (auto &input_name : this->loaded_input_list) {
            this->input_map[input_name] = false;
        }
    }
}
