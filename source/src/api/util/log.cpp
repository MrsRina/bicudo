#include "bicudo/api/util/log.hpp"
#include <SDL2/SDL.h>

bicudo::logger::logger(std::string_view new_tag) {
    this->set_tag(new_tag);
}

bicudo::logger::~logger() {
    this->file_log.clear();
}

void bicudo::print(std::string_view input) {
    std::cout << input.data() << '\n';
}

void bicudo::logger::set_file_log_path(std::string_view path) {
    this->file_log_path = path;
}

std::string_view bicudo::logger::get_file_log_path() {
    return this->file_log_path;
}

void bicudo::logger::set_debug_mode(bool debug_mode) {
    this->debug = debug_mode;
}

bool bicudo::logger::is_debug_mode() {
    return this->debug;
}

void bicudo::logger::set_log_save_file(bool save_file) {
    this->gen_file_log = save_file;
}

bool bicudo::logger::is_log_save_file_enabled() {
    return this->gen_file_log;
}

void bicudo::logger::send_info(std::string_view message) {
    const std::string m_factor {this->tag_processed + message.data()};
    this->file_log.push_back(m_factor.data());
    bicudo::print(m_factor);
}

void bicudo::logger::send_warning(std::string_view message) {
    const std::string m_factor {(this->tag_processed + "Warning: ") + message.data()};
    this->file_log.push_back(m_factor.data());
    bicudo::print(m_factor);
}

void bicudo::logger::set_tag(std::string_view new_tag) {
    this->tag = new_tag;
    this->tag_processed = "[";
    this->tag_processed += this->tag;
    this->tag_processed += "] ";
}

std::string_view bicudo::logger::get_tag() {
    return this->tag;
}

void bicudo::logger::on_create() {
    feature::on_create();
}

void bicudo::logger::on_destroy() {
    feature::on_destroy();

    // todo: save file if gen save file mode is on (true)
}

bool bicudo::reach(bicudo::timing &timing, uint64_t ms) {
    timing.checked = true;
    timing.running_ticks = SDL_GetTicks64();

    return timing.running_ticks - timing.elapsed_ticks > ms;
}

bool bicudo::reset(bicudo::timing &timing) {
    if (timing.checked) {
        timing.elapsed_ticks = timing.running_ticks;
        timing.checked = false;
    } else {
        timing.elapsed_ticks = SDL_GetTicks64();
    }

    return true;
}
