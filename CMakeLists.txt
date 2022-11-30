cmake_minimum_required(VERSION 3.23)
project(DudEngine VERSION 1.0.0)

find_package(Vulkan REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME}
        main.cpp
        dud_window.hpp
        dud_window.cpp
        dud_app.cpp
        dud_app.hpp
        dud_pipeline.cpp
        dud_pipeline.hpp
        dud_device.cpp
        dud_device.hpp
        dud_swap_chain.cpp
        dud_swap_chain.hpp
        macros.cpp
        macros.hpp
        dud_model.cpp
        dud_model.hpp scene/scene.cpp scene/scene.hpp)

add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/entt)

target_include_directories(${PROJECT_NAME}
        PUBLIC external/glfw/include/GLFW
        PUBLIC external/entt/single_include/entt)

target_link_directories(${PROJECT_NAME}
        PRIVATE external/glfw/src)

target_link_libraries(${PROJECT_NAME}
        Vulkan::Vulkan
        glfw
        glm::glm)

