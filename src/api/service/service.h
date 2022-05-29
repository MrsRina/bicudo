#pragma once
#include "includes/includes.h"
#include "api/util/util.h"

#ifndef SERVICE
#define SERVICE

/**
 * Build service list.
 **/
template<typename T>
class service {
protected:
    /* List with allelements in. */
    std::vector<T> element_list;

    /* Name of this service. */
    std::string name;
public:
    /* Start of setters and getters. */
    void set_name(const std::string &service_name) {
        this->name = service_name;
    }

    std::string get_name() {
        return this->name;
    }
    /* End of setters and getters. */

    /* Start of main methods. */
    void add(T element) {
        this->element_list.push_back(element);
    }

    void remove(T element) {
        int32_t index = -1;

        for (uint32_t i = 0; i < this->element_list.size(); i++) {
            if (this->element_list.at(i) == element) {
                index = i;
                break;
            }
        }

        if (index != -1) {
            this->element_list.erase(this->element_list.begin() + index);
        }
    }

    bool contains(T element) {
        for (T elements : this->element_list) {
            if (elements == element) {
                return true;
            }
        }

        return false;
    }

    std::vector<T> &get_element_list() {
        return this->element_list;
    }
    /* End of main methods. */

    /* Start of abstract methods. */
    virtual void on_start() {
        util::log(this->get_name() + " service start.");
    }

    virtual void on_end() {
        util::log(this->get_name() + " service end.");
    }
    /* End of abstract methods. */
};

#endif