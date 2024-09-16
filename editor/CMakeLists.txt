file(GLOB_RECURSE VOLT_EDITOR_SRCS CONFIGURE_DEPENDS "*.cc")

add_executable(${CMAKE_PROJECT_NAME}-editor ${VOLT_EDITOR_SRCS})
set_property(TARGET ${CMAKE_PROJECT_NAME}-editor PROPERTY OUTPUT_NAME ${CMAKE_PROJECT_NAME})

target_compile_definitions(${CMAKE_PROJECT_NAME}-editor PRIVATE VOLT_VERSION=${CMAKE_PROJECT_VERSION})

target_include_directories(${CMAKE_PROJECT_NAME}-editor PUBLIC ..)

target_compile_options(${CMAKE_PROJECT_NAME}-editor PRIVATE "-Wall")
target_compile_options(${CMAKE_PROJECT_NAME}-editor PRIVATE "-Wextra")
target_compile_options(${CMAKE_PROJECT_NAME}-editor PRIVATE "-Wpedantic")
target_compile_options(${CMAKE_PROJECT_NAME}-editor PRIVATE "-Werror")

target_link_options(${CMAKE_PROJECT_NAME}-editor PRIVATE "-static-libgcc")
target_link_options(${CMAKE_PROJECT_NAME}-editor PRIVATE "-static-libstdc++")
if (CMAKE_BUILD_TYPE STREQUAL "Release")
  target_link_options(${CMAKE_PROJECT_NAME}-editor PRIVATE "-pipe")
  target_link_options(${CMAKE_PROJECT_NAME}-editor PRIVATE "-O3")
  target_link_options(${CMAKE_PROJECT_NAME}-editor PRIVATE "-flto")
endif()
target_link_libraries(${CMAKE_PROJECT_NAME}-editor ${CMAKE_PROJECT_NAME})
