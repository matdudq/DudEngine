#include <iostream>
#include "dud_app.hpp"

int main() {
    dud::DudApp app{};

    try {
        app.Run();
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << '\n';
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}