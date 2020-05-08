set(IMGUI_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/third_party/imgui)
file(GLOB IMGUI_SOURCES ${IMGUI_INCLUDE_DIR}/*.cpp)
file(GLOB IMGUI_HEADERS ${IMGUI_INCLUDE_DIR}/*.h)

set(IMGUI_IMPL_SRC
    ${IMGUI_INCLUDE_DIR}/examples/imgui_impl_glfw.cpp
    ${IMGUI_INCLUDE_DIR}/examples/imgui_impl_glfw.h
    ${IMGUI_INCLUDE_DIR}/examples/imgui_impl_opengl3.cpp
    ${IMGUI_INCLUDE_DIR}/examples/imgui_impl_opengl3.h
)

add_library(imgui STATIC ${IMGUI_SOURCES})
add_library(imgui_impl OBJECT ${IMGUI_IMPL_SRC})

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

include_directories(
    ${IMGUI_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${GLAD_INCLUDE_DIR}
)

target_link_libraries(imgui
    ${OPENGL_LIBRARIES}
    ${GLFW_LIBRARIES}
    ${GLAD_LIBRARIES}
)

set_target_properties(imgui PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(imgui PROPERTIES FOLDER third_party)

set(IMGUI_LIBRARIES imgui imgui_impl)
