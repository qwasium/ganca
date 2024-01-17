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