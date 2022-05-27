#pragma once
#include "task.h"
#include "api/service/service.h"

#ifndef TASK_SERVICE
#define TASK_SERVICE

/**
 * Task manager to create threads and acess data from.
 **/
class task_service : public service<task*> {
protected:
    /* The previous id used. */
    uint32_t previous_id_task;
public:
    /* Start of methods. */
    void start(const std::string &task_name);
    void end(task* raw_task);

    bool is_task_done(const std::string &task_name);
    bool is_task_done(uint32_t task_id);
    bool is_task_done(task* raw_task);
    /* End of main methods. */

    /* Start of override methods. */
    void on_start();
    void on_end();
    /* End of override methods. */
};

#endif