# Bicudo

Bicudo is one framework to create 2D games, the first version has no GPU accelerated physics system.    
The purpose of creating this framework is not only to make games but learn physics, multi-threading & parallel tasks.

Physics use the concept of SAT (separation axis theorem) to compute displacement of collisions.
Renderer engine of Bicudo is made in API OpenGL 4 and use SDL to handle native window & physcal devices input.

There is bicudo-1 version, but that version is deprecated, but I recommend you take a look in that branch.  
There is many Bicudo's rewrite, this third version is better and use OFP (oriented feature programming).  
Do not know what is OFP? Me no too, I created this coding style as you can see, I hope you like it. ;)

Mainly features:
* Multi-threading. (?).
* GPU accelerated (rendering).
* GPU tools to work easy with OpenGL.
* Mathematical API library.
* Built on SDL.

---

# Building

If you are on Windows, please replace `"Unix Makefiles"` with `"MinGW Makefiles"`, run the command:  
`cmake -S . -B ./cmake-build-debug/ -G "Unix Makefiles" && cmake --build ./cmake-build-debug/"`

Native "library" location:  
Linux: `build/libs/linux/libbicudo.a`  
Windows: `build/libs/win32/libbicudo.a (win32 but bicudo native library is actually 64)`

note: remember to add `include/` headers too.

# Get started

After you setup correct native library you can now include into your code. Here is the basic code hello-word physics.
```c++
#include <bicudo/bicudo.hpp>

void scene_starter::on_create() {
    scene::on_create();

    bicudo::feature<bicudo::rigid> *p_solid_rigid {new bicudo::feature<bicudo::rigid>()};
    bicudo::kernel::p_core->service_physic_engine.add(p_solid_rigid);

    /* The ground rigid. */
    p_solid_rigid->content.resize(600, 100);
    p_solid_rigid->content.move(400, 700);
    p_solid_rigid->content.acceleration.y = 0.0f; // Remove gravity from rigid.
    p_solid_rigid->content.mass = 0.0f;

    /* Use current time as seed for random generator. */
    std::srand(std::time(nullptr));
    float randomic_number {};

    /* generate some rigids to do physics testing. */
    for (int32_t it {}; it < 500; it++) {
        auto *p_feature_rigid {new bicudo::feature<bicudo::rigid>()};
        auto &rigid {p_feature_rigid->content};
        bicudo::createrigid(p_feature_rigid);

        randomic_number = std::rand() % 100;
        rigid.resize(randomic_number, randomic_number);

        randomic_number = std::rand() % 600;
        rigid.move(randomic_number, randomic_number);
    }
}

void scene_starter::on_destroy() {
    scene::on_destroy();
}

void scene_starter::on_event(SDL_Event &sdl_event) {
    scene::on_event(sdl_event);
}

void scene_starter::on_update() {
    scene::on_update();
}

void scene_starter::on_render() {
    scene::on_render();
}

int32_t main(int32_t, char**) {
    /* Specify vendor GL context. */
    bicudo::gl_minor_version = 4;
    bicudo::gl_major_version = 4;
    bicudo::gl_shading_version = "#version 450";

    /* Init the bicudo core. */
    bicudo::core *p_core {new bicudo::core()};
    bicudo::createcore(p_core);

    /* Create a display. */
    bicudo::feature<bicudo::display> *p_display {new bicudo::feature<bicudo::display>()};
    p_display->content.rect[2] = 1280;
    p_display->content.rect[3] = 800;
    p_display->content.title = "Hello this is Bicudo-3.";
    p_display->content.flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    p_display->content.opacity = 1.0f;
    bicudo::createdisplay(p_display);

    /* Insert a scene. */
    bicudo::feature<bicudo::scene*> *p_scene {new bicudo::feature<bicudo::scene*>(new scene_starter())};
    bicudo::createscene(p_scene);

    /* Run bicudo core. */
    return p_core->mainloop();
}
```

GPU and OpenGL are pretty cool, but require some time to understand how do high-parallel-performance softwares.  
Bicudo contains tools to work with OpenGL easy, the tools replace good part of amount GL calls to compile buffers into GPU.
```c++
std::string bb {bicudo::gl_shading_version};
bb += "\n"
"layout (local_size_x = 1, local_size_y = 1) in;\n"
"layout (location = 0, rgba16f) in image2D uTexture;\n"
""
"void main() {\n"
"   ivec2 pix = ivec2(gl_GlobalInvocationID.xy);\n"
"   vec2 size = imageSize(uTexture);\n;"
""
"   imageStore(uTexture, pix, vec4(size / gl_GlobalInvocation.x));\n"
"}\n";

bicudo::shader *p_shader {new bicudo::shader("hello word shader")};
bicudo::createshader(p_shader, {
    {bb, GL_COMPUTE_SHADER, true} // last arg to specify use path as shader source.
    /*{"./data/effects/oioi.glsl.vert", GL_COMPUTE_SHADER}, */
});

bicudo::texturing t {};
/* First arg is the key name. */
t.invoke(666, {GL_TEXTURE_2D, GL_FLOAT});
t.send<float>({100, 100, 0}, nullptr, {GL_RGBA16F, GL_RGBA});
t.revoke(); /* Remember to revoke (unbind texture etc). */

bicudo::paralleling p {};
p.memory_barrier = GL_ALL_BARRIER_BITS;
p.dimension[0] = p.dimension[1] = 100;
p.p_shader = p_shader; /* Link the shader before call invoke. */
p.work_groups[0] = p.work_groups[1] = p.work_groups[2] = 1;
    
/* Remember to invoke and attach textures. */
p.invoke();
p.attach(0, t[666], GL_READ_ONLY); // the shader from t!
p.dispatch(); // run paralleling code.

t.invoke(666, {GL_TEXTURE_2D, GL_FLOAT});
std::vector<float> raw_tex_data {};
t.get<float>(raw_tex_data); // read the texture, remember to invoke the texture.
t.revoke();

/* Revoke the paralleling. */
p.revoke();

bicudo::buffering b {};
b.primitive[0] = GL_TRIANGLES;
b.primitive[1] = GL_UNSIGNED_BYTE; // used to indexing rendering technique.
/* Tiny note: set indices to stride[0] when rendering using index, the stride[1] is not necessary required so it can be zero. */
b.stride[0] = 0; b.stride[1] = 3;

b.invoke();
b.bind(22, {GL_ARRAY_BUFFER, GL_FLOAT});
std::vector<float> mesh {0.0f, 1.0f, /* */ -1.0f, -1.0f, /* */ 1.0f, 1.0f};
b.send<float>(mesh.size(), mesh.data(), GL_STATIC_DRAW);
b.attach(0, 2, {0, 0}); // attach to shader (location, vec_size, stride)
b.revoke();

/* Now you can draw!*/
/* Of course call it into a rendering statement ><. */
b.invoke();
b.draw(); // uwu
b.revoke();
```

The mathematical part is very fun!
```c++
bicudo::vec2 a = bicudo::vec2(00.0f, 0.03940492304f);
bicudo::vec2 b {2.0f, 2.0f};

/* basic arithmethic vectorial operations. */
a = a * b + a - b * a;
a += b;
a -= b;
a *= b;
b /= 2.0f;
a /= b; // yes it exists.
a *= 2.0f; // scalar.

bicudo::dot(a, b);
bicudo::cross(a, b);
bicudo::normalize(a);
bicudo::rotate(a, RAD2DEG(90.0f));
bicudo::rotate(a, 0.0920399f, b); // center

/* There is only multiplication. */
bicudo::mat4 c = bicudo::mat4(1.0f); // identity
bicudo::mat4 d {1.0f};
bicudo::mat4 e = c * d;

bicudo::scale(e, {23.0f, 23.0f, 232.0f});
bicudo::rotate(e, {0, 1, 0});
bicudo::translate(e, {1.0, 4000.0f, 9999.0f});
```

# Credits & License

Thank you Michael Tanaya, Huaming Chen, Jebediah Pavleas & Kelvin Sung. Thanks for the awesome published book by Aprees.  
Bicudo use MIT license, we do not care for what purpose you use it, just follow the MIT terms.
