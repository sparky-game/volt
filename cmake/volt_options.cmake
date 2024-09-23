function (volt_set_options)
  option(VOLT_USE_SIMD "Enable SIMD math" ON)
  if (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
    cmake_dependent_option(VOLT_USE_AVX2 "Enable AVX2 instruction set" ON "VOLT_USE_SIMD" OFF)
  endif()

  # Check VOLT_USE_SIMD value is valid
  if (NOT VOLT_USE_SIMD STREQUAL "ON" AND NOT VOLT_USE_SIMD STREQUAL "OFF")
    message(WARNING "VOLT_USE_SIMD is set to an invalid value (${VOLT_USE_SIMD}), defaulting to ON")
    set(VOLT_USE_SIMD ON CACHE STRING "Enable SIMD math" FORCE)
  endif()

  # Check VOLT_USE_AVX2 value is valid
  if (NOT VOLT_USE_AVX2 STREQUAL "ON" AND NOT VOLT_USE_AVX2 STREQUAL "OFF")
    message(WARNING "VOLT_USE_AVX2 is set to an invalid value (${VOLT_USE_AVX2}), defaulting to ON")
    set(VOLT_USE_AVX2 ON CACHE STRING "Enable AVX2 instruction set" FORCE)
  endif()

  message(STATUS "Use SIMD: ${VOLT_USE_SIMD}")
  message(STATUS "Use AVX2: ${VOLT_USE_AVX2}")
endfunction()
