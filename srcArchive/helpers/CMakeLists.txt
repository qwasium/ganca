include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(helpers)

# Python ---------------------------------------------------------------
# set(CMAKE_CURRENT_BINARY_DIR ${PROJECT_BINARY_DIR}/python)

# helpers
set_source_files_properties(helpers.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(helpers.i PROPERTIES SWIG_FLAGS "-includeall")

swig_add_library(helpers
	LANGUAGE python
	SOURCES helpers.i helpers.cpp)

# target_include_directories(helpers
# 	PRIVATE
# 	${PYTHON_INCLUDE_DIRS})

set_property(TARGET helpers PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES ON)

target_link_libraries(helpers ${PYTHON_LIBRARIES})


# Python end ---------------------------------------------------------------