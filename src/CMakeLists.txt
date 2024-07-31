file(GLOB_RECURSE VOLT_SRCS CONFIGURE_DEPENDS "*.cc")

add_library(${CMAKE_PROJECT_NAME} STATIC $<TARGET_OBJECTS:raylib> ${VOLT_SRCS})

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE VOLT_VERSION=${CMAKE_PROJECT_VERSION})

target_include_directories(${CMAKE_PROJECT_NAME} SYSTEM PUBLIC ../vendor/entt/src)
target_include_directories(${CMAKE_PROJECT_NAME} SYSTEM PUBLIC ../vendor/raylib/src)
target_include_directories(${CMAKE_PROJECT_NAME} SYSTEM PUBLIC ../vendor/spdlog/include)
