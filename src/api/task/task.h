#pragma once
#include "includes/includes.h"
#include "api/feature/feature.h"

#ifndef TASK_H
#define TASK_H

/**
 * Thread talking and object multi-threading safe.
 **/
class task : private ifeature {
protected:
    /* Task name. */
    std::string name;

    /* An id of task, used in communication. */
    uint32_t id;

    /* If task is done, so we can pass boolean data into threads. */
    std::atomic<bool> atomic_boolean_end;
    std::atomic<bool> atomic_boolean;
public:
    task(const std::string &task_name, uint32_t next_task_id);
    ~task();

    /* Start of setters and getters. */
    void set_name(const std::string &task_name);
    std::string get_name();

    void set_atomic_boolean_state(bool state);
    bool get_atomic_boolean_state();

    void set_atomic_boolean_end_state(bool state);
    boll get_atomic_boolean_end_state();
    /* End of setters and getters. */

    /* Start of main methods. */
    void end();
    /* End of main methods. */
};

#endif