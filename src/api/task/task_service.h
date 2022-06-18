#pragma once
#include "task.h"
#include "api/service/service.h"

#ifndef TASK_SERVICE_H
#define TASK_SERVICE_H

/**
 * Task manager to create_task threads and access data from.
 **/
class task_service : public service {
protected:
    /* The previous id used. */
    uint32_t previous_id_task;
    uint8_t iterator_queue;

    /* Flag to delete objects after the thread disabled. */
    std::atomic<bool> atomic_boolean_pass_to_queue;
    std::array<std::string, 32> queue;
public:
    /* Start of main methods. */
    task* start(const std::string &task_name);
    bool done(const std::string &task_name);
    void end(task* raw_task);
    void refresh();
    /* End of main methods. */

    /* Start of setters and getters. */
    task* get_task_by_name(const std::string &task_name);
    task* get_task_by_feature_id(uint32_t task_id);
    /* End of setters and getters. */

    /* Start of override methods. */
    void on_start();
    void on_end();
    void on_update();
    /* End of override methods. */
};

#endif