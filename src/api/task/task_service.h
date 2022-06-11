#pragma once
#include "task.h"
#include "api/service/service.h"

#ifndef TASK_SERVICE_H
#define TASK_SERVICE_H

/**
 * Task manager to create threads and acess data from.
 **/
class task_service : public service {
protected:
    /* The previous id used. */
    uint32_t previous_id_task;
public:
    task_service(const std::string &service_name) : service(service_name) {   
    }

    /* Start of main static methods. */
    static task* run(const std::string &task_name);
    static void stop(const std::string &task_name);
    /* End of main static methods. */

    /* Start of main methods. */
    task* start(const std::string &task_name);
    void end(task* raw_task);

    bool is_task_done(const std::string &task_name);
    bool is_task_done(uint32_t task_id);
    bool is_task_done(task* raw_task);
    /* End of main methods. */

    /* Start of setters and getters. */
    task* get_task_by_name(const std::string &task_name);
    task* get_task_by_feature_id(uint32_t task_id);
    /* End of setters and getters. */

    /* Start of override methods. */
    void on_start();
    void on_end();
    /* End of override methods. */
};

#endif