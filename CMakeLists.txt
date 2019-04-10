cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0048 NEW)

# check supported OS
if (WIN32 OR APPLE)
    message(FATAL_ERROR "Sorry, only Linux is supported.")
endif ()

# set project infos
project(wrappi VERSION 1.0.0 LANGUAGES CXX)

# create library
add_library(wrappi SHARED)

target_include_directories(wrappi PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_sources(wrappi PRIVATE
        src/base.cpp
        src/branch.cpp
        src/cache.cpp
        src/cycles.cpp
        src/instructions.cpp
        src/misc.cpp
        src/tlb.cpp
        src/manager.cpp)

set_target_properties(wrappi PROPERTIES
        PUBLIC_HEADER include/wrappi.h
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
        CXX_EXTENSIONS ON)


# manage dependencies
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(OpenMP REQUIRED)
find_package(PAPI REQUIRED)
find_package(Hwloc)

if (OpenMP_CXX_FOUND)
    target_link_libraries(wrappi PUBLIC OpenMP::OpenMP_CXX)
endif ()

if (PAPI_FOUND)
    target_compile_definitions(wrappi PUBLIC HAVE_PAPI=1)
    target_include_directories(wrappi PUBLIC ${PAPI_INCLUDE_DIRS})
    target_link_libraries(wrappi PUBLIC ${PAPI_LIBRARIES})
endif ()

if (HWLOC_FOUND)
    target_compile_definitions(wrappi PUBLIC HAVE_HWLOC=1)
    target_include_directories(wrappi PUBLIC ${HWLOC_INCLUDE_DIR})
    target_link_libraries(wrappi PUBLIC ${HWLOC_LIBRARY})
endif ()


# manage compilation options
target_compile_features(wrappi PUBLIC cxx_std_14)

# set build-type dependent options
set(DEFAULT_BUILD_TYPE "Release")

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif ()

if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_VERBOSE_MAKEFILE ON)
    target_compile_options(wrappi PRIVATE -Wall)
    target_compile_options(wrappi PRIVATE -Wextra)
    target_compile_definitions(wrappi PRIVATE DEBUG=1)
else ()
    target_compile_options(wrappi PRIVATE -O3)
    target_compile_options(wrappi PRIVATE -funroll-loops)
    target_compile_options(wrappi PRIVATE -march=native)
    target_compile_options(wrappi PRIVATE -D_REENTRANT)
    target_compile_options(wrappi PRIVATE -Wcast-align)
    target_compile_options(wrappi PRIVATE -Wpacked)
endif ()

# export target from build/install trees
export(TARGETS wrappi FILE wrappi-config.cmake)
export(PACKAGE wrappi)

install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/wrappi"
        DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
        FILES_MATCHING PATTERN "*.h")

install(TARGETS wrappi
        EXPORT wrappi-targets
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

install(EXPORT wrappi-targets
        FILE wrappi-config.cmake
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/cmake/wrappi)