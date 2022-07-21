#include "api/client/instance.h"

task::task(const std::string &task_name, uint32_t next_task_id) {
    this->name = task_name;
    this->id = next_task_id;
    
    // constuctor.
}

task::~task() {
    // Destructor.
}

void task::set_name(const std::string &task_name) {
    this->name = task_name;
}

std::string task::get_name() {
    return this->name;
}

void task::set_atomic_boolean_state(bool state) {
    this->atomic_boolean = state;
}

bool task::get_atomic_boolean_state() {
    return this->atomic_boolean;
}

void task::set_atomic_boolean_end_state(bool state) {
    this->atomic_boolean_end = state;

    if (state) {
        BICUDO->get_task_manager().refresh();
        util::log("Task " + this->get_name() + " shutdown.");
    }
}

bool task::get_atomic_boolean_end_state() {
    return this->atomic_boolean_end;
}

void task::end() {
    if (!this->atomic_boolean) {
        this->atomic_boolean = true;
    }
}