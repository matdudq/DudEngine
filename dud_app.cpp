#include "dud_app.hpp"

namespace dud {
    void DudApp::Run() {
        while(!window.ShouldClose()){
            glfwPollEvents();
        }
    }
}