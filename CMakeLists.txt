cmake_minimum_required(VERSION 3.14)
enable_language(C CXX)
project(opengl_engine CXX)

include(cmake/third_party.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_COMPILER clang++)
add_compile_options(-std=c++17 -Wall -Wextra -pedantic -g3)
add_definitions(${GLFW_DEFINITIONS})

add_executable(main
    src/main.cc
    src/shader.cc
    src/camera.cc
    src/stb_image.cc
    src/time.cc
    src/input.cc
    src/window.cc
    src/renderer.cc
    src/texture.cc
    src/mesh.cc
    src/model.cc
    src/cube_map.cc

    src/gl_buffers/vertex_buffer.cc
    src/gl_buffers/vertex_buffer_layout.cc
    src/gl_buffers/vertex_array.cc
    src/gl_buffers/index_buffer.cc
    src/gl_buffers/frame_buffer.cc

    src/imgui_windows.cc
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GLM_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${GLAD_INCLUDE_DIR}
    ${IMGUI_INCLUDE_DIR}
    ${ASSIMP_INCLUDE_DIR}
)

target_link_libraries(main
    ${OPENGL_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${GLAD_LIBRARIES}
    ${IMGUI_LIBRARIES}
    ${ASSIMP_LIBRARIES}
)
