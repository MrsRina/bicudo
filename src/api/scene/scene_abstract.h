#pragma once
#include "includes/includes.h"

#ifndef SCENE_ABSTRACT_H
#define SCENE_ABSTRACT_H

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
    scene_abstract() {}
    ~scene_abstract() {}

    /* Start of main methods. */
    void add(uint32_t feature_id);
    void remove(uint32_t feature_id);
    bool contains(uint32_t feature_id);
    void registry(const std::string &scene_name, const std::string &scene_description);
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