# developed on cmake 3.22.1 on Ubuntu 22.04/x86_64
# minimum_required is set without testing; pls report bug if it fails.
cmake_minimum_required(VERSION 3.21)

project(ganca VERSION 0.1 LANGUAGES CXX)

# CMP0122: Starting with CMake 3.21,
# UseSWIG generates now a library using default naming conventions.
# https://cmake.org/cmake/help/latest/policy/CMP0122.html
if (POLICY CMP0122)
  cmake_policy(SET CMP0122 NEW)
endif()

# temporarily set to C++ 17
# might change in future development
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

# build dir
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)
set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)


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
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})
set(CMAKE_SWIG_FLAGS "") # option for swig command

message(STATUS "SWIG:")
message(STATUS "    executable: ${SWIG_EXECUTABLE}")
message(STATUS "    version:    ${SWIG_VERSION}")
message(STATUS "    use file:   ${SWIG_USE_FILE}")
message(STATUS "    flags:      ${CMAKE_SWIG_FLAGS}")
# SWIG end -------------------------------------------------------------

# Python ---------------------------------------------------------------
find_package(PythonLibs)
include_directories(${PYTHON_INCLUDE_PATH})

message(STATUS "Python:")
message(STATUS "    include:    ${PYTHON_INCLUDE_PATH}")
message(STATUS "    libraries:  ${PYTHON_LIBRARIES}")
# Python end -----------------------------------------------------------

# csv-parser -----------------------------------------------------------
find_package(Git REQUIRED)

# update submodules
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  option(CHK_SUBMODULE "Check submodules during build" ON) # check submodule: toggle on/off
  if(CHK_SUBMODULE)
    message(STATUS "Submodule update")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
      message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
  endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/csv-parser/CMakeLists.txt")
  message(FATAL_ERROR "The submodules were not downloaded! CHK_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

include_directories(${PROJECT_SOURCE_DIR}/extern/csv-parser/single_include)
# csv-parser end -------------------------------------------------------

# include directories --------------------------------------------------
include_directories(${PROJECT_SOURCE_DIR}/src)
# include directories end ----------------------------------------------


# add_subdirectory(src)
add_subdirectory(test)




# debug
message("dir from root")
message("project src dir : ${PROJECT_SOURCE_DIR}")
message("project bin dir : ${PROJECT_BINARY_DIR}")
message("cmake src dir   : ${CMAKE_SOURCE_DIR}")
message("cmake bin dir   : ${CMAKE_BINARY_DIR}")
message("cur src dir     : ${CMAKE_CURRENT_SOURCE_DIR}")
message("cur bin dir     : ${CMAKE_CURRENT_BINARY_DIR}")