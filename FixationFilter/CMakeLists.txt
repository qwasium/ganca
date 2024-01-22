add_library(FixationFilter)
target_sources(FixationFilter
  PRIVATE
    include/fixationfilter/FixationFilter.hpp
    src/FixationFilter.cpp)
target_include_directories(FixationFilter
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_compile_features(FixationFilter PUBLIC cxx_std_17)
set_target_properties(FixationFilter PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER include/fixationfilter/FixationFilter.hpp)
#target_link_libraries(FixationFilter PUBLIC ...)
add_library(${PROJECT_NAMESPACE}::FixationFilter ALIAS FixationFilter)

add_subdirectory(tests)

# Install
install(TARGETS FixationFilter
  EXPORT ${PROJECT_NAME}Targets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fixationfilter
  )
