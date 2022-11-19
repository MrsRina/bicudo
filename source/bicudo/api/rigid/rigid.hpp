#ifndef BICUDO_API_RIGID_H
#define BICUDO_API_RIGID_H

#include "bicudo/api/feature/feature.hpp"
#include "bicudo/api/util/math.hpp"

namespace bicudo {
    class rigid : public bicudo::feature {
    protected:
        bicudo::vec2 vertexes[4] {}, normals[4] {};

        void update_normals();
        void update_inertia();
    public:
        bicudo::vec2 pos {}, size {}, acceleration {}, velocity {}, min {}, max {};
        float angle {}, angular_velocity {}, angular_acceleration {};
        float friction {}, mass {}, inertia {}, restitution {};
        bool collided {};

        rigid(const bicudo::vec2&, const bicudo::vec2&, float, float, float);
        ~rigid();

        void set_size(float, float);
        void set_rotation(float);
        void update_mass(float);

        void on_create() override;
        void on_destroy() override;
        void on_update();

        /*
         * Get rigid vertices data.
         */
        bicudo::vec2 *vdata();

        /*
         * Get rigid normals data.
         */
        bicudo::vec2 *ndata();
    };
}

#endif