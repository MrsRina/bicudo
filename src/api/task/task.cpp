#include "task.h"

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

void task::set_id(uint32_t task_id) {
    this->id = task_id;
}

uint32_t task::get_id() {
    return this->id;
}

void task::set_atomic_boolean_state(bool state) {
    this->atomic_boolean = state;
}

bool task::get_atomic_boolean_state() {
    return this->atomic_boolean;
}

void task::end() {
    if (!this->atomic_boolean) {
        this->atomic_boolean = true;
    }
}