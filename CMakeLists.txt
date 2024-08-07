cmake_minimum_required(VERSION 3.20)
include(cmake/build_type.cmake)
include(cmake/c_compiler.cmake)
include(cmake/cxx_compiler.cmake)
include(cmake/c_compiler_options.cmake)
include(cmake/cxx_compiler_options.cmake)

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

volt_set_c_compiler_options()
volt_set_cxx_compiler_options()

add_subdirectory(vendor)
add_subdirectory(editor)
add_subdirectory(src)
