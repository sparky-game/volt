cmake_minimum_required(VERSION 3.20)
include(cmake/build_type.cmake)
include(cmake/c_compiler.cmake)
include(cmake/cxx_compiler.cmake)

volt_set_build_type()
volt_set_c_compiler()
volt_set_cxx_compiler()

project(
  volt
  DESCRIPTION  "A multithreaded, high performance, fully functional game engine written in C++."
  HOMEPAGE_URL "https://github.com/sparky-game/volt"
  LANGUAGES    C CXX
)
set(CMAKE_PROJECT_VERSION 0.1-alpha)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address,undefined -g -Og")
set(CMAKE_CXX_FLAGS_RELEASE "-pipe -O3")

message(STATUS "The configured build type is ${CMAKE_BUILD_TYPE}")

add_subdirectory(vendor)
add_subdirectory(editor)
add_subdirectory(src)
