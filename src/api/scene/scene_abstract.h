#pragma once
#include "includes/includes.h"

#ifndef SCENE_ABSTRACT
#define SCENE_ABSTRACT

/**
 * Nameable abstract scene.
 **/
class scene_abstract {
private:
    /* Nameable. */
    std::string name, description;

    /* Ids from features. */
    std::vector<uint32_t> feature_ids;
public:
    /* Start of main methods. */
    void add(uint32_t feature_id);
    void remove(uint32_t feature_id);
    bool contains(uint32_t feature_id);
    /* End of main methods. */

    /* Start of setters and getters. */
    void set_name(const std::string &module_name);
    std::string get_name();

    void set_description(const std::string &module_description);
    std::string get_description();

    std::vector<uint32_t> &get_features_id();
    /* End of setters and getters. */

    /* Start of abstract methods. */
    virtual void on_start();
    virtual void on_end();
    /* End of abstract methods. */
};

#endif