add_library(Helper)

target_sources(Helper
  PRIVATE
    include/helper/Helper.hpp
    src/Helper.cpp)
target_include_directories(Helper
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_compile_features(Helper PUBLIC cxx_std_17)
set_target_properties(Helper PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER include/helper/Helper.hpp)
#target_link_libraries(helper PUBLIC ...)
add_library(${PROJECT_NAMESPACE}::Helper ALIAS Helper)

add_subdirectory(tests)

# Install
install(TARGETS Helper
  EXPORT ${PROJECT_NAME}Targets
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/helper
  )