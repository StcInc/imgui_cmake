cmake_minimum_required(VERSION 3.8.0)

project(imgui_tryout VERSION 1.0)

add_subdirectory(glfw)

add_executable(imgui_tryout main.cpp)

set_property(TARGET imgui_tryout PROPERTY CXX_STANDARD 14)


# Imgui lib as static dep
# ========================================================

add_library(imgui STATIC)

set_property(TARGET imgui PROPERTY CXX_STANDARD 14)

target_sources(imgui
    PRIVATE
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui.cpp
    PRIVATE
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/backends/imgui_impl_glfw.cpp
)
find_package(OpenGL REQUIRED)
target_link_libraries(imgui PUBLIC glfw ${OPENGL_LIBRARIES})


target_include_directories(imgui                       
     PUBLIC imgui
     PUBLIC imgui/backends
)

# Link target executable imgui_tryout against imgui lib
# ========================================================

target_link_libraries(imgui_tryout PUBLIC imgui glfw)
