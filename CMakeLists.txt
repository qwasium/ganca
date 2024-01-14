# developed on cmake 3.22.1 on Ubuntu 22.04/x86_64
# minimum_required is set without testing; pls report bug if it fails.
cmake_minimum_required(VERSION 3.21)

project(ganca VERSION 0.1 LANGUAGES CXX)

# CMP0122: Starting with CMake 3.21,
# UseSWIG generates now a library using default naming conventions.
if (POLICY CMP0122)
cmake_policy(SET CMP0122 NEW)
endif()

# temporarily set to C++ 17
# might change in future development
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


message("${PROJECT_NAME} ver${PROJECT_VERSION}")
# cmake minimum ver
message("cmake min ver: ${CMAKE_MINIMUM_REQUIRED_VERSION}")
# compiler
message("compiler     : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
# build system
message("build system : ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION}")
# build arch
message("build arch   : ${CMAKE_SYSTEM_PROCESSOR}")
# build flags
message("build flags  : ${CMAKE_CXX_FLAGS}")
# cxx version
message("cxx version  : ${CMAKE_CXX_STANDARD}")
message("\n")

# openCV ---------------------------------------------------------------
# https://github.com/opencv/opencv/blob/4.x/samples/cpp/example_cmake/CMakeLists.txt
# Find OpenCV, you may need to set OpenCV_DIR variable
# to the absolute path to the directory containing OpenCVConfig.cmake file
# via the command line or GUI
find_package(OpenCV REQUIRED)

message(STATUS "OpenCV library status:")
message(STATUS "    config:       ${OpenCV_DIR}")
message(STATUS "    version:      ${OpenCV_VERSION}")
message(STATUS "    libraries:    ${OpenCV_LIBS}")
message(STATUS "    include path: ${OpenCV_INCLUDE_DIRS}")
# openCV end ------------------------------------------------------------

# SWIG -----------------------------------------------------------------
FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})
SET(CMAKE_SWIG_FLAGS "") # option for swig command

message(STATUS "swig:")
message(STATUS "    executable: ${SWIG_EXECUTABLE}")
message(STATUS "    version:    ${SWIG_VERSION}")
message(STATUS "    use file:   ${SWIG_USE_FILE}")
message(STATUS "    flags:      ${CMAKE_SWIG_FLAGS}")
# SWIG end -------------------------------------------------------------

# Python ---------------------------------------------------------------
FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})

message(STATUS "python:")
message(STATUS "    include:    ${PYTHON_INCLUDE_PATH}")
message(STATUS "    libraries:  ${PYTHON_LIBRARIES}")
# Python end -----------------------------------------------------------

# directories
# add_subdirectory(src)
# add_subdirectory(test)

add_executable(heatmapTest
  ${PROJECT_BINARY_DIR}/src/heatmap.hpp
  ${PROJECT_BINARY_DIR}/test/heatmapTest.cpp
  ${PROJECT_BINARY_DIR}/test/include/csv-parser/csv.hpp)


# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)


# debug
message("project name: ${PROJECT_NAME}")
message("project version: ${PROJECT_VERSION}")
message("project source dir: ${PROJECT_SOURCE_DIR}")
message("src dir: ${CMAKE_CURRENT_SOURCE_DIR}/src")
message("bin dir: ${CMAKE_CURRENT_BINARY_DIR}")
message("build dir: ${CMAKE_CURRENT_BINARY_DIR}/build")