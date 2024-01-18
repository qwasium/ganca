add_library(Heatmap)

target_sources(Heatmap
  PRIVATE
    include/heatmap/Heatmap.hpp
    src/Heatmap.cpp)
target_include_directories(Heatmap
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_compile_features(Heatmap PUBLIC cxx_std_17)
set_target_properties(Heatmap PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER include/heatmap/Heatmap.hpp)
#target_link_libraries(heatmap PUBLIC ...)
add_library(${PROJECT_NAMESPACE}::Heatmap ALIAS Heatmap)

# add_subdirectory(tests)

# Install
install(TARGETS Heatmap
  EXPORT ${PROJECT_NAME}Targets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/heatmap
  )