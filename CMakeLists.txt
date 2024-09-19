cmake_minimum_required(VERSION 3.15)

project(FileSpliter)
set(CMAKE_CXX_STANDARD 20)

# checking git
execute_process(
    COMMAND git --version
    RESULT_VARIABLE GIT_FOUND_RESULT
    OUTPUT_QUIET
)

if(GIT_FOUND_RESULT EQUAL 0)
    message(STATUS "checking for git - yes")
else()
    message(FATAL_ERROR "checking for git - no")
endif()

if(EXISTS ${CMAKE_SOURCE_DIR}/src/simdjson)
    message(STATUS "checking for simdjson - yes")
else()
    message(STATUS "checking for simdjson - no")
    execute_process(
        COMMAND git clone --depth=1 https://github.com/simdjson/simdjson.git src/simdjson
        RESULT_VARIABLE CLONE_SIMDJSON_RESULT
    )
endif()

add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cc)
