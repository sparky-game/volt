file(GLOB RAYLIB_SRCS CONFIGURE_DEPENDS "raylib/src/*.c")

add_library(raylib OBJECT ${RAYLIB_SRCS})

target_compile_definitions(raylib PRIVATE PLATFORM_DESKTOP)

target_include_directories(raylib SYSTEM PUBLIC raylib/src/external/glfw/include)

target_compile_options(raylib PRIVATE "-w")
target_compile_options(raylib PRIVATE "-Wno-implicit-function-declaration")
target_compile_options(raylib PRIVATE "-pipe")
target_compile_options(raylib PRIVATE "-O3")
