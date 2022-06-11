#include "gui.h"

void gui::set(const std::string &gui_name, const std::string &gui_description) {
    this->name = gui_name;
    this->description = gui_description;
}

std::string gui::get_name() {
    return this->name;
}

std::string gui::get_description() {
    return this->description;
}

void gui::on_registry() {

}

void gui::on_start() {

}

void gui::on_end() {

}

void gui::on_event(SDL_Event &sdl_event) {

}

void gui::on_locked_update() {

}

void gui::on_update() {

}

void gui::on_render() {

}