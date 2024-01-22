set_property(SOURCE fixationfilter.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE fixationfilter.i PROPERTY SWIG_MODULE_NAME pyFixationFilter)
swig_add_library(pyFixationFilter
  TYPE MODULE
  LANGUAGE python
  OUTPUT_DIR ${PYTHON_PROJECT_DIR}/fixationfilter
  SOURCES fixationfilter.i)
add_library(${PROJECT_NAMESPACE}::pyFixationFilter ALIAS pyFixationFilter)

target_include_directories(pyFixationFilter
  PRIVATE
  ../include
  ${Python3_INCLUDE_DIRS}
  )
set_property(TARGET pyFixationFilter PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES ON)

# note: macOS is APPLE and also UNIX !
if(APPLE)
  set_target_properties(pyFixationFilter PROPERTIES
    SUFFIX ".so"
    INSTALL_RPATH "@loader_path;@loader_path/../../${PYTHON_PROJECT}/.libs"
    )
  set_property(TARGET pyFixationFilter APPEND PROPERTY
    LINK_FLAGS "-flat_namespace -undefined suppress"
    )
elseif(UNIX)
  set_target_properties(pyFixationFilter PROPERTIES
    INSTALL_RPATH "$ORIGIN:$ORIGIN/../../${PYTHON_PROJECT}/.libs"
    )
endif()
target_link_libraries(pyFixationFilter PRIVATE ${PROJECT_NAMESPACE}::FixationFilter)

# Variable PYTHON_LIBRARIES can contains keyword `optimized`
# which won't be interpreted inside a generator expression.
# i.e. we can't use: $<$<PLATFORM_ID:Windows>:${PYTHON_LIBRARIES}>
# see: https://cmake.org/cmake/help/git-stage/command/target_link_libraries.html#command:target_link_libraries
if(MSVC)
  target_link_libraries(pyFixationFilter PRIVATE ${Python3_LIBRARIES})
endif()