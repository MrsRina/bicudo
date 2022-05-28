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
    /* Start of main methods. */
    template<typename callback, typename... args>
    task* start(const std::string &task_name, callback&& __f, args&&... __args) {
        if (this->get_task_by_name(task_name) != NULL) {
            return NULL;
        } 
    
        task* raw_task = new task(task_name, this->previous_id_task++);
        this->add(raw_task);
        std::thread thread_release(__f, raw_task);
        
        return raw_task;
    }

    void end(task* raw_task);

    bool is_task_done(const std::string &task_name);
    bool is_task_done(uint32_t task_id);
    bool is_task_done(task* raw_task);
    /* End of main methods. */

    /* Start of setters and getters. */
    task* get_task_by_name(const std::string &task_name);
    task* get_task_by_id(uint32_t task_id);
    /* End of setters and getters. */

    /* Start of override methods. */
    void on_start();
    void on_end();
    /* End of override methods. */
};

#endif