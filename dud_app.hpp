#pragma once

#include "dud_window.hpp"

#include "memory"
#include "dud_mesh.hpp"
#include "dud_core.hpp"
#include "dud_scene.hpp"
#include "dud_renderer.hpp"
#include "dud_render_system.hpp"
#include "systems/dud_systems_container.hpp"

namespace dud {
    class App {

    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 800;
    private:
        Window window{WIDTH, HEIGHT, "Main Window"};
        Device device{window};
        Renderer renderer{window, device};
        SystemsContainer systemContainer{};

        Scope<Scene> scene;
    public:
        App();
        ~App();

        App(const App &) = delete;
        App &operator=(const App &) = delete ;

        void run();
    private:
        void loadScene();

        void render(const RenderSystem &renderSystem, const Camera &camera);
    };
}