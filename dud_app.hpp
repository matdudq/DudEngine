#pragma once

#include "dud_window.hpp"

#include "memory"
#include "dud_mesh.hpp"
#include "dud_core.hpp"
#include "dud_scene.hpp"
#include "dud_renderer.hpp"

namespace dud {
    class App {

    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 800;
    private:
        Window window{WIDTH, HEIGHT, "Main Window"};
        Device device{window};
        Renderer renderer{window, device};

        Scope<Scene> scene;


    public:
        App();
        ~App();

        App(const App &) = delete;
        App &operator=(const App &) = delete ;

        void run();
    private:
        void loadScene();
    };
}