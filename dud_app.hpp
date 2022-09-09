#pragma once

#include "dud_window.hpp"

namespace dud {
    class DudApp {

    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 800;

        void Run();

    private:
        DudWindow window{WIDTH, HEIGHT, "Main Window"};
    };
}
