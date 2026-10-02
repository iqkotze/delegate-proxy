# Build options and cache variables.
set(DG_CXX_STANDARD "20" CACHE STRING "C++ standard for all sources (20 or 23)")
set_property(CACHE DG_CXX_STANDARD PROPERTY STRINGS 20 23)
if(NOT DG_CXX_STANDARD MATCHES "^(20|23)$")
  message(FATAL_ERROR "DG_CXX_STANDARD must be 20 or 23")
endif()

set(ADMIN "root@localhost" CACHE STRING "Administrator mail address compiled into delegated")
set(ADMINPASS "" CACHE STRING "Administrator password compiled into delegated")
set(LICENSEE "" CACHE STRING "Licensee string compiled into delegated")
set(IMPSIZE "10000" CACHE STRING "Size limit for embedded files")

option(DG_BUILD_SUBIN "Build the subin helper programs" OFF)
option(DG_EXTRA_WARNINGS "Enable additional compiler warnings" OFF)
option(DG_WERROR "Treat compiler warnings as errors" OFF)

find_package(GTest QUIET)
option(DG_BUILD_TESTS "Build the GoogleTest unit tests" ${GTest_FOUND})

if(ADMIN STREQUAL "root@localhost")
  message(STATUS "ADMIN is the default root@localhost")
endif()

find_package(OpenSSL 3.0 REQUIRED)
find_package(ZLIB REQUIRED)
