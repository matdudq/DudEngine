cmake_minimum_required(VERSION 3.23)
project(DudEngine VERSION 1.0.0)

find_package(Vulkan REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_executable(${PROJECT_NAME}
        main.cpp
        window.hpp
        window.cpp
        app.cpp
        app.hpp
        pipeline.cpp
        pipeline.hpp
        device.cpp
        device.hpp
        swap_chain.cpp
        swap_chain.hpp
        macros.cpp
        macros.hpp
        mesh.cpp
        mesh.hpp scene.cpp scene.hpp components/transform_component.cpp components/transform_component.hpp core.hpp components/mesh_component.cpp components/mesh_component.hpp renderer.cpp renderer.hpp render_system.cpp render_system.hpp systems/single_thread_system.hpp systems/systems_container.hpp systems/rotation_system.cpp systems/rotation_system.hpp components/camera_component.cpp components/camera_component.hpp core.cpp)

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

