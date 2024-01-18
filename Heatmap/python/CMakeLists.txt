set_property(SOURCE heatmap.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE heatmap.i PROPERTY SWIG_MODULE_NAME pyHeatmap)
swig_add_library(pyHeatmap
  TYPE MODULE
  LANGUAGE python
  OUTPUT_DIR ${PYTHON_PROJECT_DIR}/heatmap
  SOURCES heatmap.i)
add_library(${PROJECT_NAMESPACE}::pyHeatmap ALIAS pyHeatmap)

target_include_directories(pyHeatmap
  PRIVATE
  ../include
  ${Python3_INCLUDE_DIRS}
  )
set_property(TARGET pyHeatmap PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES ON)

# note: macOS is APPLE and also UNIX !
if(APPLE)
  set_target_properties(pyHeatmap PROPERTIES
    SUFFIX ".so"
    INSTALL_RPATH "@loader_path;@loader_path/../../${PYTHON_PROJECT}/.libs"
    )
  set_property(TARGET pyHeatmap APPEND PROPERTY
    LINK_FLAGS "-flat_namespace -undefined suppress"
    )
elseif(UNIX)
  set_target_properties(pyHeatmap PROPERTIES
    INSTALL_RPATH "$ORIGIN:$ORIGIN/../../${PYTHON_PROJECT}/.libs"
    )
endif()
target_link_libraries(pyHeatmap PRIVATE ${PROJECT_NAMESPACE}::Heatmap)

# Variable PYTHON_LIBRARIES can contains keyword `optimized`
# which won't be interpreted inside a generator expression.
# i.e. we can't use: $<$<PLATFORM_ID:Windows>:${PYTHON_LIBRARIES}>
# see: https://cmake.org/cmake/help/git-stage/command/target_link_libraries.html#command:target_link_libraries
if(MSVC)
  target_link_libraries(pyHeatmap PRIVATE ${Python3_LIBRARIES})
endif()
