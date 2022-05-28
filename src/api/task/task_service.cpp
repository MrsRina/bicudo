#include "task_service.h"

void task_service::end(task* raw_task) {
    raw_task->set_atomic_boolean_state(true);
    this->remove(raw_task);
    delete raw_task;
    raw_task = nullptr;
}

task* task_service::get_task_by_name(const std::string &task_name) {
    for (task* &tasks : this->element_list) {
        if (tasks->get_name() == task_name) {
            return tasks;
        }
    }

    return NULL;
}

task* task_service::get_task_by_id(uint32_t task_id) {
    for (task* &tasks : this->element_list) {
        if (tasks->get_id() == task_id) {
            return tasks;
        }
    }

    return NULL;
}

bool task_service::is_task_done(const std::string &task_name) {
    task* raw_task = this->get_task_by_name(task_name);
    bool flag = raw_task != NULL && raw_task->get_atomic_boolean_state();

    if (flag) {
        this->end(raw_task);
    }

    return flag;
}

bool task_service::is_task_done(uint32_t id) {
    task* raw_task = this->get_task_by_id(id);
    bool flag = raw_task != NULL && raw_task->get_atomic_boolean_state();

    if (flag) {
        this->end(raw_task);
    }

    return flag;
}

bool task_service::is_task_done(task* raw_task) {
    bool flag = this->contains(raw_task);

    if (flag) {
        this->end(raw_task); // remove the task from here.
    }

    return flag;
}

void task_service::on_start() {
    service::on_start();
}

void task_service::on_end() {
    service::on_end();

    for (task* &task : this->element_list) {
        task->set_atomic_boolean_state(true);
    }
}