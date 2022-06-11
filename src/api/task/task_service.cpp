#include "task_service.h"
#include "api/client/instance.h"

task* task_service::run(const std::string &task_name) {
    return BICUDO->get_task_manager().start(task_name);
}

void task_service::stop(const std::string &task_name) {
    task* raw_task = BICUDO->get_task_manager().get_task_by_name(task_name);

    if (raw_task == nullptr) {
        return;
    }

    BICUDO->get_task_manager().end(raw_task);
}

task* task_service::start(const std::string &task_name) {
    if (this->get_task_by_name(task_name) != nullptr) {
        return nullptr;
    }

    task* raw_task = new task(task_name, this->previous_id_task++);
    this->add((ifeature*) raw_task);
    
    return raw_task;
}

void task_service::end(task* raw_task) {
    raw_task->set_atomic_boolean_state(true);
    this->remove((ifeature*) raw_task);
    delete raw_task;
    raw_task = nullptr;
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

bool task_service::is_task_done(const std::string &task_name) {
    task* raw_task = this->get_task_by_name(task_name);
    bool flag = raw_task != NULL && raw_task->get_atomic_boolean_state();

    if (flag) {
        this->end(raw_task);
    }

    return flag;
}

bool task_service::is_task_done(uint32_t id) {
    task* raw_task = this->get_task_by_feature_id(id);
    bool flag = raw_task != nullptr && raw_task->get_atomic_boolean_state();

    if (flag) {
        this->end(raw_task);
    }

    return flag;
}

bool task_service::is_task_done(task* raw_task) {
    bool flag = this->contains((ifeature*) raw_task);

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

    for (ifeature* &features : this->update_list) {
        task* tasks = (task*) features;
        tasks->set_atomic_boolean_state(true);
    }
}