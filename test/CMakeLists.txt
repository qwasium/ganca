set(CMAKE_CURRENT_BINARY_DIR ${PROJECT_BINARY_DIR}/test)

# heatmap
add_executable(heatmapTest ${CMAKE_CURRENT_SOURCE_DIR}/heatmapTest.cpp)

# debug
message("dir from test")
message("project src dir : ${PROJECT_SOURCE_DIR}")
message("project bin dir : ${PROJECT_BINARY_DIR}")
message("cmake src dir   : ${CMAKE_SOURCE_DIR}")
message("cmake bin dir   : ${CMAKE_BINARY_DIR}")
message("cur src dir     : ${CMAKE_CURRENT_SOURCE_DIR}")
message("cur bin dir     : ${CMAKE_CURRENT_BINARY_DIR}")