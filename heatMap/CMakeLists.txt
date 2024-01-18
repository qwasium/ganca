add_library(heatmap)

target_sources(heatmap
  PRIVATE
    include/heatmap/heatmap.hpp
    src/heatmap.cpp)
target_include_directories(heatmap
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_compile_features(heatmap PUBLIC cxx_std_17)
set_target_properties(heatmap PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER include/heatmap/heatmap.hpp)
#target_link_libraries(heatmap PUBLIC ...)
add_library(${PROJECT_NAMESPACE}::heatmap ALIAS heatmap)

add_subdirectory(tests)

# Install
install(TARGETS heatmap
  EXPORT ${PROJECT_NAME}Targets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/heatmap
  )