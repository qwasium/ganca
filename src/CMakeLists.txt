include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Python ---------------------------------------------------------------
# set(CMAKE_CURRENT_BINARY_DIR ${PROJECT_BINARY_DIR}/python)

# example
set_source_files_properties(example.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(example.i PROPERTIES SWIG_FLAGS "-includeall")

swig_add_library(example
		LANGUAGE python
		# OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/python
		SOURCES example.i example.cpp)
target_link_libraries(example ${PYTHON_LIBRARIES})

# helpers
set_source_files_properties(helpers.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(helpers.i PROPERTIES SWIG_FLAGS "-includeall")

swig_add_library(helpers
		LANGUAGE python
		SOURCES helpers.i helpers.cpp)
target_link_libraries(helpers ${PYTHON_LIBRARIES})

set_property(TARGET helpers PROPERTY SWIG_USE_TARGET_INCLUDE_DIRECTORIES ON)

# Python end ---------------------------------------------------------------