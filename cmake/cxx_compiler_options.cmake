function (volt_set_cxx_compiler_options)
  set(CMAKE_CXX_STANDARD 20 CACHE STRING "CXX standard" FORCE)
  set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE STRING "CXX standard required" FORCE)
  message(STATUS "Configured CXX standard: ${CMAKE_CXX_STANDARD}")
  set(CMAKE_CXX_EXTENSIONS OFF CACHE STRING "CXX extensions" FORCE)
  message(STATUS "Configured CXX extensions: ${CMAKE_CXX_EXTENSIONS}")
  set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address,undefined -g -Og" CACHE STRING "CXX flags (Debug)" FORCE)
  set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -pipe -O3 -flto" CACHE STRING "CXX flags (Release)" FORCE)
  if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configured CXX flags: ${CMAKE_CXX_FLAGS_DEBUG}")
  elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Configured CXX flags: ${CMAKE_CXX_FLAGS_RELEASE}")
  endif()
endfunction()
