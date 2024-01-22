# developed on cmake 3.22.1 on Ubuntu 22.04/x86_64
# minimum_required is set without testing; pls report bug if it fails.
cmake_minimum_required(VERSION 3.21)

# CMP0122: https://cmake.org/cmake/help/latest/policy/CMP0122.html
if (POLICY CMP0122)
  cmake_policy(SET CMP0122 NEW)
endif()

project(ganca VERSION 0.1 LANGUAGES CXX)
set(PROJECT_NAMESPACE ganca) # user defined
# set(PROJECT_NAMESPACE cs)

# temporarily set to C++ 17
# might change in future development
enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add cmake scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# export compile_commands.json
option(CMAKE_EXPORT_COMPILE_COMMANDS "Export compile command" TRUE)

# print build info
message("#######################################")
message("${PROJECT_NAME} ver${PROJECT_VERSION}")
message("cmake min ver : ${CMAKE_MINIMUM_REQUIRED_VERSION}")
message("compiler      : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message("build system  : ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION}")
message("build arch    : ${CMAKE_SYSTEM_PROCESSOR}")
message("build flags   : ${CMAKE_CXX_FLAGS}")
message("c++ version   : ${CMAKE_CXX_STANDARD}")
message("#######################################")

# multi-config generator ------------------------------------------------
get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(isMultiConfig)
  if(NOT CMAKE_CONFIGURATION_TYPES) # Specifies the available build types (configurations) on multi-config generators (e.g. Visual Studio, Xcode, or Ninja Multi-Config) as a semicolon-separated list.
    set(CMAKE_CONFIGURATION_TYPES "Release;Debug" CACHE STRING
    "Choose the type of builds, options are: Debug Release RelWithDebInfo MinSizeRel. (default: Release;Debug)"
    FORCE)
  endif()
  message(STATUS "Configuration types: ${CMAKE_CONFIGURATION_TYPES}")
else()
  if(NOT CMAKE_BUILD_TYPE) # Specifies the build type on single-configuration generators (e.g. Makefile Generators or Ninja).
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
    "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel. (default: Release)"
    FORCE)
  endif()
  message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
endif()
# multi-config generator end --------------------------------------------

# Layout build dir like install dir -------------------------------------
include(GNUInstallDirs)
if(UNIX)
  option(BUILD_SHARED_LIBS "Build shared libraries (.so or .dyld)." ON) # Global flag to cause add_library() to create shared libraries if on.
  # Use the install path for the RPATH (Run-time Path).
  # Since we want to use the CMAKE_BINARY_DIR to generate the wrapper package (e.g. python wheel package)...
  # ...as well as be able to test from the build directory.
  # We need to enable CMAKE_BUILD_WITH_INSTALL_RPATH to TRUE and have a finely-tuned RPATH for each library.
  set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
  # for multi-config build system (e.g. Xcode, Ninja Multi-Config)
  # CMAKE_CONFIGURATION_TYPES is empty on single-config generator
  foreach(OutputConfig IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER ${OutputConfig} OUTPUTCONFIG)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OutputConfig}/${CMAKE_INSTALL_LIBDIR})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OutputConfig}/${CMAKE_INSTALL_LIBDIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OutputConfig}/${CMAKE_INSTALL_BINDIR})
  endforeach()
else()
  # Currently Only support static build for windows
  option(BUILD_SHARED_LIBS "Build shared libraries (.dll)." OFF)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
  # for multi-config builds (e.g. msvc)
  foreach(OutputConfig IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER ${OutputConfig} OUTPUTCONFIG)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OutputConfig}/${CMAKE_INSTALL_BINDIR})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OutputConfig}/${CMAKE_INSTALL_BINDIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${OutputConfig}/${CMAKE_INSTALL_BINDIR})
  endforeach()
endif()
# Layout build dir like install dir end ---------------------------------

# build target language selection ---------------------------------------
# build C++ library?
option(BUILD_CXX "Build C++ library" ON)
message(STATUS "Build C++ library: ${BUILD_CXX}")

# build Python library?
option(BUILD_PYTHON "Build Python Library" OFF)
message(STATUS "Build Python: ${BUILD_PYTHON}")

# build R library?
option(BUILD_R "Build R Library" OFF)
message(STATUS "Build R: ${BUILD_R}")
# build target language selection end -----------------------------------

# Disable CTest targets
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
include(CTest)

# git
find_package(Git REQUIRED)

# openCV(local install)
# include(opencv) # /cmake/opencv.cmake

# csv-parser(git submodule)
include(csvparser) # /cmake/csvparser.cmake

# build C++ library
include(cpp) # /cmake/cpp.cmake

# SWIG for Windows
if(WIN32 AND (BUILD_R OR BUILD_PYTHON))
  include(swig) # /cmake/swig.cmake
endif()

# build Python library
if(BUILD_PYTHON)
  option(FETCH_PYTHON_DEPS "Install python required modules if not available" ON)
  message(STATUS "Python fetch dependencies: ${FETCH_PYTHON_DEPS}")
endif()
include(python)

# copy test data
file(COPY ${PROJECT_SOURCE_DIR}/test_data DESTINATION ${PROJECT_BINARY_DIR})