set_property(SOURCE aoihit.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE aoihit.i PROPERTY SWIG_MODULE_NAME pyAOIHit)
swig_add_library(pyAOIHit
  TYPE MODULE
  LANGUAGE python
  OUTPUT_DIR ${PYTHON_PROJECT_DIR}/aoihit
  SOURCES aoihit.i)
add_library(${PROJECT_NAMESPACE}::pyAOIHit ALIAS pyAOIHit)

target_include_directories(pyAOIHit
  PRIVATE
  ../include
  ${Python3_INCLUDE_DIRS}
  )
set_property(TARGET pyAOIHit PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES ON)

# note: macOS is APPLE and also UNIX !
if(APPLE)
  set_target_properties(pyAOIHit PROPERTIES
    SUFFIX ".so"
    INSTALL_RPATH "@loader_path;@loader_path/../../${PYTHON_PROJECT}/.libs"
    )
  set_property(TARGET pyAOIHit APPEND PROPERTY
    LINK_FLAGS "-flat_namespace -undefined suppress"
    )
elseif(UNIX)
  set_target_properties(pyAOIHit PROPERTIES
    INSTALL_RPATH "$ORIGIN:$ORIGIN/../../${PYTHON_PROJECT}/.libs"
    )
endif()
target_link_libraries(pyAOIHit PRIVATE ${PROJECT_NAMESPACE}::AOIHit)

# Variable PYTHON_LIBRARIES can contains keyword `optimized`
# which won't be interpreted inside a generator expression.
# i.e. we can't use: $<$<PLATFORM_ID:Windows>:${PYTHON_LIBRARIES}>
# see: https://cmake.org/cmake/help/git-stage/command/target_link_libraries.html#command:target_link_libraries
if(MSVC)
  target_link_libraries(pyAOIHit PRIVATE ${Python3_LIBRARIES})
endif()
