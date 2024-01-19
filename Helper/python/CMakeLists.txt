set_property(SOURCE helper.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE helper.i PROPERTY SWIG_MODULE_NAME pyHelper)
swig_add_library(pyHelper
  TYPE MODULE
  LANGUAGE python
  OUTPUT_DIR ${PYTHON_PROJECT_DIR}/helper
  SOURCES helper.i)
add_library(${PROJECT_NAMESPACE}::pyHelper ALIAS pyHelper)

target_include_directories(pyHelper
  PRIVATE
  ../include
  ${Python3_INCLUDE_DIRS}
  )
set_property(TARGET pyHelper PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES ON)

# note: macOS is APPLE and also UNIX !
if(APPLE)
  set_target_properties(pyHelper PROPERTIES
    SUFFIX ".so"
    INSTALL_RPATH "@loader_path;@loader_path/../../${PYTHON_PROJECT}/.libs"
    )
  set_property(TARGET pyHelper APPEND PROPERTY
    LINK_FLAGS "-flat_namespace -undefined suppress"
    )
elseif(UNIX)
  set_target_properties(pyHelper PROPERTIES
    INSTALL_RPATH "$ORIGIN:$ORIGIN/../../${PYTHON_PROJECT}/.libs"
    )
endif()
target_link_libraries(pyHelper PRIVATE ${PROJECT_NAMESPACE}::Helper)

# Variable PYTHON_LIBRARIES can contains keyword `optimized`
# which won't be interpreted inside a generator expression.
# i.e. we can't use: $<$<PLATFORM_ID:Windows>:${PYTHON_LIBRARIES}>
# see: https://cmake.org/cmake/help/git-stage/command/target_link_libraries.html#command:target_link_libraries
if(MSVC)
  target_link_libraries(pyHelper PRIVATE ${Python3_LIBRARIES})
endif()
