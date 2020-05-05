find_package(OpenGL REQUIRED)

find_package(X11 REQUIRED)

if (NOT X11_Xi_FOUND)
    message(FATAL_ERROR "X11 Xi library is required")
endif ()

include(cmake/glad.cmake)
include(cmake/glfw.cmake)
include(cmake/imgui.cmake)
