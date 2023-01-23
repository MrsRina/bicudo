#ifndef STARTER_H
#define STARTER_H

#include <bicudo/bicudo.hpp>

class scene_starter : public bicudo::scene {
public:
    void on_create() override {
        scene::on_create();
    }

    void on_destroy() override {
        scene::on_destroy();
    }

    void on_update() override {
        scene::on_update();
    }

    void on_render() override {
        scene::on_render();
    }
};

#endif