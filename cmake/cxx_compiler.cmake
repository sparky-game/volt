function (volt_set_cxx_compiler)
  if (WIN32 OR CMAKE_CXX_COMPILER)
    return()
  endif()
  find_program(VOLT_CXX_COMPILER clang++)
  if (VOLT_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER "${VOLT_CXX_COMPILER}" CACHE STRING "CXX compiler" FORCE)
  else()
    message(WARNING "clang++ not found, falling back to system's default CXX compiler")
  endif()
endfunction()
