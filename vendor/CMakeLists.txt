file(GLOB RAYLIB_SRCS CONFIGURE_DEPENDS "raylib/src/*.c")
file(GLOB IMGUI_SRCS CONFIGURE_DEPENDS "imgui/*.cpp")
file(GLOB IMGUI_IMPL_RAYLIB_SRCS CONFIGURE_DEPENDS "imgui_impl_raylib/*.cpp")

add_library(raylib OBJECT ${RAYLIB_SRCS})
add_library(imgui OBJECT ${IMGUI_SRCS})
add_library(imgui_impl_raylib OBJECT ${IMGUI_IMPL_RAYLIB_SRCS})

target_compile_definitions(raylib PRIVATE PLATFORM_DESKTOP)

target_include_directories(raylib SYSTEM PUBLIC raylib/src/external/glfw/include)
target_include_directories(imgui_impl_raylib SYSTEM PUBLIC raylib/src)
target_include_directories(imgui_impl_raylib SYSTEM PUBLIC imgui)

target_compile_options(raylib PRIVATE "-w")
target_compile_options(raylib PRIVATE "-Wno-implicit-function-declaration")
target_compile_options(raylib PRIVATE "-pipe")
target_compile_options(imgui PRIVATE "-pipe")
target_compile_options(imgui_impl_raylib PRIVATE "-pipe")
target_compile_options(raylib PRIVATE "-O3")
target_compile_options(imgui PRIVATE "-O3")
target_compile_options(imgui_impl_raylib PRIVATE "-O3")
