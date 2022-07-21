#pragma once

#ifndef MODULE_ABSTRACT_H
#define MODULE_ABSTRACT_H

#include "includes/includes.h"

/**
 * Nameable module to states and settings in.
 **/
class module_abstract {
protected:
    /* Nameable. */
    std::string name, description;

    /* State to alive context. */
    bool enabled;
public:
    module_abstract() {}
    ~module_abstract() {}

    /* Start of setters and getters. */
    void set_name(const std::string &module_name);
    std::string get_name();

    void set_description(const std::string &module_description);
    std::string get_description();

    void set_enable_state(bool state);
    bool is_enabled();
    /* End of setters and getters. */

    /* Start of main methods. */
    void registry(const std::string &module_name, const std::string &module_description);
    /* End of main methods. */

    /* Start of abstract methods. */
    virtual void on_start() {}
    virtual void on_end() {}
    /* End of abstract methods. */
};

#endif