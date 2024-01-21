add_library(AOIHit)
target_sources(AOIHit
  PRIVATE
    include/aoihit/AOIHit.hpp
    src/AOIHit.cpp)
target_include_directories(AOIHit
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_compile_features(AOIHit PUBLIC cxx_std_17)
set_target_properties(AOIHit PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER include/aoihit/AOIHit.hpp)
#target_link_libraries(AOIHit PUBLIC ...)
add_library(${PROJECT_NAMESPACE}::AOIHit ALIAS AOIHit)

add_subdirectory(tests)

# Install
install(TARGETS AOIHit
  EXPORT ${PROJECT_NAME}Targets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/aoihit
  )