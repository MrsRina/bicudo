#include "task_manager.h"

void task_manager::start(const std::string &task_name) {
    task* raw_task = new task(task_name, this->previous_id_task++);
    this->add(raw_task);
}

void task_manager::end(task* raw_task) {
    this->remove(raw_task);
    delete raw_task;
    raw_task = nullptr;
}

bool task_manager::is_task_done(const std::string &task_name) {
    task* raw_task = nullptr;
    bool flag = false;

    for (uint32_t i = 0; i < this->element_list.size(); i++) {
        task* tasks = this->element_list.at(i);

        if (tasks != nullptr && tasks->get_name() == task_name && tasks->get_atomic_boolean_state()) {
            raw_task = tasks;
            flag = true;
            break;
        }
    }

    if (flag) {
        this->end(raw_task);
    }

    return flag;
}

bool task_manager::is_task_done(uint32_t id) {
    task* raw_task = nullptr;
    bool flag = false;

    for (uint32_t i = 0; i < this->element_list.size(); i++) {
        task* tasks = this->element_list.at(i);

        if (tasks != nullptr && tasks->get_id() == id && tasks->get_atomic_boolean_state()) {
            raw_task = tasks;
            flag = true;
            break;
        }
    }

    if (flag) {
        this->end(raw_task);
    }

    return flag;
}

bool task_manager::is_task_done(task* raw_task) {
    bool flag = this->contains(raw_task);

    if (flag) {
        this->end(raw_task); // remove the task from here.
    }

    return flag;
}