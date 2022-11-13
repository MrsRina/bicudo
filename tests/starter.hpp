#ifndef STARTER_H
#define STARTER_H

#include <bicudo/bicudo.hpp>

class starter : public bicudo::scene {
public:
    void on_create() override;
    void on_destroy() override;
};

#endif