function (volt_set_build_type)
  if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
  endif()
  message(STATUS "The requested build type is ${CMAKE_BUILD_TYPE}")
endfunction()
