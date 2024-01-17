
# update submodules
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
  option(CHK_SUBMODULE "Check submodules during build" ON) # check submodule: toggle on/off
  if(CHK_SUBMODULE)
    message(STATUS "Submodule update")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
      message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    elseif(GIT_SUBMOD_RESULT EQUAL "1")
      message(STATUS "Submodule update done")
    endif()
  endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/extern/csv-parser/CMakeLists.txt")
  message(FATAL_ERROR "The submodules were not downloaded! CHK_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

# add csv-parser header file
include_directories(${PROJECT_SOURCE_DIR}/extern/csv-parser/single_include)