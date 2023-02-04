#include "bicudo/service/service_physic_engine.hpp"
#include "bicudo/physic/physic_sat.hpp"
#include "bicudo/opengl/opengl_context_overview.hpp"
#include "bicudo/bicudo.hpp"
#include "bicudo/util/priority.hpp"

void bicudo::service_physic_engine::update_mass(bicudo::rigid *p_rigid, float delta) {
    float mm {};
    if (p_rigid->mass != 0) {
        mm = 1.0f / p_rigid->mass;
    }

    mm += delta;
    if (mm <= 0.0f) {
        p_rigid->mass = 0.0f;
        p_rigid->velocity = bicudo::vec2zero;
        p_rigid->acceleration = bicudo::vec2zero;
        p_rigid->angular_acceleration = bicudo::zero;
    } else {
        p_rigid->mass = 1.0f / mm;
        p_rigid->acceleration = this->gravity;
    }

    p_rigid->update_inertia();
}

void bicudo::service_physic_engine::set_gravity(float x, float y) {
    this->gravity.x = 0;
    this->gravity.y = 0;
}

bicudo::vec2 bicudo::service_physic_engine::get_current_gravity() {
    return this->gravity;
}

void bicudo::service_physic_engine::on_native_update() {
    for (bicudo::feature<rigid> *&p_feature_rigid : this->features) {
        if (p_feature_rigid != nullptr) {
            p_feature_rigid->content.on_update();
        }
    }

    /**
     * IMPORTANT NOTES!!
     *
     * 1- The iterations are currently temp. and are not the final result of Bicudo physics engine.
     * 2- GPU parallelism computation will be in main thread, GL context does not allow GL calls
     * inside others place of CPU (except at current context thread).
     * 3- The multi-threading solution will be not the focus, but perhaps I will implement a custom
     * physics loop using multi-threading chunks.
     * 4- Chunks or "iterations groups" are good techniques to improve real time physics simulation,
     * but increase O^2 complexity with good amount of chunks running, not the property solution.
     *
     * Att, Rina.
     **/

    for (int32_t accurate_iterations {}; accurate_iterations < 3; accurate_iterations++) {
        for (bicudo::feature<bicudo::rigid> *&p_feature_rigid_l : this->features) {
            p_feature_rigid_l->content.collided = false;
            for (bicudo::feature<bicudo::rigid> *&p_feature_rigid_r : this->features) {
                if (p_feature_rigid_l != p_feature_rigid_r && bicudo::checkcollision(p_feature_rigid_l->content, p_feature_rigid_r->content, this->collide_info)) {
                    this->process_displacement_resolution(p_feature_rigid_l->content, p_feature_rigid_r->content);
                }
            }
        }
    }
}

void bicudo::service_physic_engine::on_native_render() {
    auto &display {bicudo::kernel::p_core->service_display.get_display(bicudo::stack::toplevel)};
    bicudo::vec4 rect {};
    bicudo::vec4 color {};
    bicudo::mat4 perspective {bicudo::orthographic(0.0f, display.rect[2], display.rect[3], 0.0f)};
    bicudo::mat4 model {};

    this->p_shader_debug->invoke();
    this->buffer.invoke();

    bicudo::vec3 center {};

    for (bicudo::feature<bicudo::rigid> *&p_feature : this->features) {
        center.x = p_feature->content.position.x + p_feature->content.size.x / 2;
        center.y = p_feature->content.position.y + p_feature->content.size.y / 2;

        model = bicudo::mat4(1.0f);
        model = bicudo::translate(model, {0, -1.0f, 0});
        //model = bicudo::rotate(model, p_feature->content.angular_angle, {0, 0, 1});
        //model = bicudo::translate(model, -center);
        model = perspective * model;

        rect.z = p_feature->content.size.x;
        rect.w = p_feature->content.size.y;
        rect.x = p_feature->content.position.x - (rect.z / 2);
        rect.y = p_feature->content.position.y - (rect.w / 2);

        this->p_shader_debug->set_uniform_vec4("u_Rectangle", &rect[0]);
        this->p_shader_debug->set_uniform_mat4("u_PerspectiveModel", &model[0][0]);

        color.x = 1.0f * p_feature->content.collided;
        color.y = 0.0f;
        color.z = 1.0f * !p_feature->content.collided;
        color.w = 1.0f;

        this->p_shader_debug->set_uniform_vec4("u_Color", &color[0]);
        this->buffer.draw();
    }

    this->p_shader_debug->revoke();
    this->buffer.revoke();
}

void bicudo::service_physic_engine::add(bicudo::feature<bicudo::rigid> *p_feature) {
    service::add(p_feature);

    p_feature->content.acceleration = this->gravity;
    this->update_mass(&p_feature->content, p_feature->content.mass);
}

void bicudo::service_physic_engine::process_displacement_resolution(bicudo::rigid &l, bicudo::rigid &r) {
    l.collided = true;
    if (ASSERT_FLOAT(l.mass, 0.0f)  && ASSERT_FLOAT(r.mass, 0.0f)) {
        return;
    }

    /* The distance is divided by the sum of mass.*/
    float accuracy = this->collide_info.distance / (l.mass + r.mass);
    bicudo::vec2 force {this->collide_info.normal * accuracy};

    l.move(force.x * -l.mass, force.y * -l.mass);
    r.move(force.x * r.mass, force.y * r.mass);

    switch (l.rotatable) {
        case true: {
            bicudo::vec2 n {this->collide_info.normal};
            bicudo::vec2 start {this->collide_info.start * (r.mass / (l.mass + r.mass))};
            bicudo::vec2 end {this->collide_info.end * (l.mass / (l.mass + r.mass))};
            bicudo::vec2 p {start + end};

            /* Direction from contact point between position center. */
            bicudo::vec2 ld {p - l.position};
            bicudo::vec2 rd {p - r.position};

            bicudo::vec2 lv {l.velocity + bicudo::vec2 {-1.0f * l.angular_velocity * ld.y, l.angular_velocity * ld.x}};
            bicudo::vec2 rv {r.velocity + bicudo::vec2 {-1.0f * r.angular_velocity * rd.y, r.angular_velocity * rd.x}};

            /* V as known relative velocity between the two rigids. */
            bicudo::vec2 v {rv - lv};
            float v_dot {bicudo::dot(v, n)};
            if (v_dot > 0.0f) break;

            float restitiution {std::min(l.restitution, r.restitution)};
            float friction {std::min(l.friction, r.friction)};

            float ld_cross {bicudo::cross(ld, n)};
            float rd_cross {bicudo::cross(rd, n)};

            float jn {
                (-(1.0f + restitiution) * v_dot) / (l.mass + r.mass + ld_cross * ld_cross * l.inertia + rd_cross * rd_cross * r.inertia)
            };
            
            force = n * jn;
            l.velocity -= force * l.mass;
            r.velocity += force * r.mass;

            l.angular_velocity -= ld_cross * jn * l.inertia;
            r.angular_velocity += rd_cross * jn * r.inertia;

            bicudo::vec2 tangent {v - n * bicudo::dot(v, n)};
            tangent = bicudo::normalize(tangent) * -1.0f;

            float ld_cross_t {bicudo::cross(ld, tangent)};
            float rd_cross_t {bicudo::cross(rd, tangent)};

            float jt {
                (-(1.0f + restitiution) * bicudo::dot(v, tangent) * friction) / (l.mass + r.mass + ld_cross_t * ld_cross_t + l.mass + rd_cross_t * rd_cross_t * r.inertia)
            };

            jt = jt > jn ? jn : jt;
            tangent *= jt;

            l.velocity -= force * l.mass;
            r.velocity += force * r.mass;

            l.angular_velocity -= ld_cross_t * jt * l.inertia;
            r.angular_velocity += rd_cross_t * jt * r.inertia;
            break;
        }

        default: {
            bicudo::vec2 n {this->collide_info.normal};
            bicudo::vec2 vl {l.velocity};
            bicudo::vec2 vr {r.velocity};

            /* V as known relative velocity between the two rigids. */
            bicudo::vec2 v {vr - vl};

            float v_dot {bicudo::dot(v, n)};
            if (v_dot > 0.0f) break;

            float restitution {std::min(l.restitution, r.restitution)};
            float friction {std::min(l.friction, r.friction)};
            float jn {
                (-(1.0f + restitution) * v_dot) / (l.mass, r.mass)
            };

            force = n * jn;
            l.velocity -= force * l.mass;
            r.velocity += force * r.mass;

            bicudo::vec2 tangent {v - n * v_dot};
            tangent = bicudo::normalize(tangent) * -1.0f;
            
            float jt {
                (-(1.0f + restitution) * bicudo::dot(v, tangent) * friction) / (l.mass + r.mass)
            };
            
            jt = jt > jn ? jn : jt;
            force = tangent * jt;

            l.velocity -= force * l.mass;
            r.velocity += force * r.mass;
            break;
        }
    }
}

void bicudo::service_physic_engine::on_native_init() {
    float mesh[8] {
        0.0f, 0.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
    };

    uint8_t index[6] {
        0, 1, 3,
        3, 2, 0
    };

    std::string vsh {bicudo::gl_shading_version};
    vsh += "\n"
           "layout (location = 0) in vec2 a_Pos;\n"
           "layout (location = 1) in vec2 a_TexCoord;\n"
           ""
           "uniform mat4 u_PerspectiveModel;\n"
           "uniform vec4 u_Rectangle;\n"
           ""
           "out vec4 v_Rect;\n"
           "out vec2 v_TexCoord;\n"
           ""
           "void main() {\n"
           "    gl_Position = (u_PerspectiveModel * vec4(a_Pos * u_Rectangle.zw + u_Rectangle.xy, 0.0f, 1.0f));\n"
           "    v_Rect = u_Rectangle;\n"
           "    v_TexCoord = a_TexCoord;\n"
           "}\n";

    std::string fsh {bicudo::gl_shading_version};
    fsh += "\n"
           "layout (location = 0) out vec4 a_FragColor;\n"
           ""
           "in vec2 v_Rect;\n"
           "in vec2 v_TexCoords;\n"
           ""
           "uniform vec4 u_Color;\n"
           ""
           "void main() {\n"
           "    vec4 sum = u_Color;\n"
           "    a_FragColor = sum;\n"
           "}\n";

    this->p_shader_debug = new bicudo::shader("physic.debug");
    bicudo::createshader(this->p_shader_debug, {{vsh, GL_VERTEX_SHADER, true}, {fsh, GL_FRAGMENT_SHADER, true}});

    /* Vertex pos layout binding. */
    this->buffer.invoke();
    this->buffer.primitive[0] = GL_TRIANGLES;
    this->buffer.bind(0, {GL_ARRAY_BUFFER, GL_FLOAT});
    this->buffer.send<float>(sizeof(mesh) / sizeof(float), mesh, GL_STATIC_DRAW);
    this->buffer.attach(0, 2);

    /* Vertex texture coordinates layout binding. */
    this->buffer.bind(1, {GL_ARRAY_BUFFER, GL_FLOAT});
    this->buffer.send<float>(sizeof(mesh) / sizeof(float), mesh, GL_STATIC_DRAW);
    this->buffer.attach(1, 2);

    /* Indexing rendering index mesh. */
    this->buffer.bind(2, {GL_ELEMENT_ARRAY_BUFFER, GL_UNSIGNED_BYTE});
    this->buffer.send<uint8_t>(sizeof(index) / sizeof(uint8_t), index, GL_STATIC_DRAW);
    this->buffer.stride[0] = 6;
    this->buffer.revoke();
}

void bicudo::service_physic_engine::on_native_quit() {
    this->buffer.delete_buffers();
}
