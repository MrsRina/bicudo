#include "task_service.h"
#include "api/client/instance.h"

task* task_service::start(const std::string &task_name) {
    if (this->get_task_by_name(task_name) != nullptr) {
        return nullptr;
    }

    task* raw_task = new task(task_name, this->previous_id_task++);
    this->add((ifeature*) raw_task);

    return raw_task;
}

void task_service::end(task* raw_task) {
    if (raw_task == nullptr) {
        return;
    }

    raw_task->set_atomic_boolean_state(true);
}

void task_service::refresh() {
    this->atomic_boolean_pass_to_queue = true;
}

task* task_service::get_task_by_name(const std::string &task_name) {
    for (ifeature* &features : this->update_list) {
        task* tasks = (task*) features;

        if (tasks->get_name() == task_name) {
            return tasks;
        }
    }

    return nullptr;
}

task* task_service::get_task_by_feature_id(uint32_t feature_id) {
    for (ifeature* &features : this->update_list) {
        if (features->get_feature_id() == feature_id) {
            return (task*) features;
        }
    }

    return nullptr;
}

bool task_service::done(const std::string &task_name) {
    bool flag = false;

    for (uint8_t i = 0; i < this->iterator_queue; i++) {
        if (this->queue[i] == task_name) {
            this->queue[i] = nullptr;

            flag = true;
            break;
        }
    }

    return flag;
}

void task_service::on_start() {
    service::on_start();
}

void task_service::on_end() {
    service::on_end();

    for (ifeature* &features : this->update_list) {
        task* tasks = (task*) features;
        tasks->set_atomic_boolean_state(true);
    }
}

void task_service::on_update() {
    if (this->atomic_boolean_pass_to_queue) {
        this->atomic_boolean_pass_to_queue = false;

        if (this->iterator_queue < 32) {            
            this->iterator_queue = 0;
            this->render_list.clear();

            for (ifeature* features : this->update_list) {
                task* tasks = (task*) features;

                if (tasks->get_atomic_boolean_end_state()) {
                    this->queue[this->iterator_queue++] = tasks->get_name();

                    delete tasks;
                    continue;
                }

                this->render_list.push_back(features);
            }

            this->update_list = this->render_list;
            this->render_list.clear();
        }
    }
}