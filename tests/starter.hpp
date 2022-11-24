#ifndef STARTER_H
#define STARTER_H

#include <bicudo/bicudo.hpp>

class starter : public bicudo::scene {
public:
    bicudo::feature *rigid {};
    void on_create() override;
    void on_destroy() override;
    void on_event(bicudo::event &event) override;
    void on_update() override;
    void on_unsafe_update() override;
};

#endif