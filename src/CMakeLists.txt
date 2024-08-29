file(GLOB_RECURSE VOLT_SRCS CONFIGURE_DEPENDS "*.cc")

add_library(${CMAKE_PROJECT_NAME} STATIC
  $<TARGET_OBJECTS:imgui>
  $<TARGET_OBJECTS:raylib>
  $<TARGET_OBJECTS:imguizmo>
  $<TARGET_OBJECTS:yaml_cpp>
  $<TARGET_OBJECTS:imgui_impl_raylib>
  ${VOLT_SRCS}
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE VOLT_VERSION=${CMAKE_PROJECT_VERSION})

target_include_directories(${CMAKE_PROJECT_NAME} SYSTEM PUBLIC ../vendor/imgui)
target_include_directories(${CMAKE_PROJECT_NAME} SYSTEM PUBLIC ../vendor/imguizmo)
target_include_directories(${CMAKE_PROJECT_NAME} SYSTEM PUBLIC ../vendor/entt/src)
target_include_directories(${CMAKE_PROJECT_NAME} SYSTEM PUBLIC ../vendor/raylib/src)
target_include_directories(${CMAKE_PROJECT_NAME} SYSTEM PUBLIC ../vendor/spdlog/include)
target_include_directories(${CMAKE_PROJECT_NAME} SYSTEM PUBLIC ../vendor/yaml-cpp/include)
target_include_directories(${CMAKE_PROJECT_NAME} SYSTEM PUBLIC ../vendor/imgui_impl_raylib)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE "-Wall")
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE "-Wextra")
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE "-Wpedantic")
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE "-Werror")
