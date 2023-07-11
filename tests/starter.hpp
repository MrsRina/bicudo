#ifndef STARTER_H
#define STARTER_H

#include <bicudo/bicudo.hpp>

class scene_starter : public bicudo::scene {
public:
    std::vector<bicudo::gpufeature*> loaded_gpu_pipeline_list {};
    std::vector<bicudo::gpufeature*> loaded_gpu_renderable_list {};
public:
    void on_create() override;
    void on_destroy() override;
    void on_event(SDL_Event &sdl_event) override;
    void on_update() override;
    void on_render() override;
};

#endif