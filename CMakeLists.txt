cmake_minimum_required(VERSION 3.15)

project(FileSpliter)
set(CMAKE_CXX_STANDARD 20)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DNDEBUG)
endif()

# checking for git
execute_process(
    COMMAND git --version
    RESULT_VARIABLE GIT_FOUND_RESULT
    OUTPUT_QUIET
)

if(GIT_FOUND_RESULT EQUAL 0)
    message(STATUS "Checking for git - yes")
else()
    message(FATAL_ERROR "Checking for git - no")
endif()

# creating third-parties directory
if(NOT EXISTS ${CMAKE_SOURCE_DIR}/third-parties)
    file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/third-parties)
    message(STATUS "Creating ${CMAKE_SOURCE_DIR}/third-parties directory")
endif()

# checking for simdjson
if(EXISTS ${CMAKE_SOURCE_DIR}/third-parties/simdjson)
    message(STATUS "Checking for simdjson - yes")
else()
    message(STATUS "Checking for simdjson - no")
    execute_process(
        COMMAND git clone --depth=1 https://github.com/simdjson/simdjson.git ${CMAKE_SOURCE_DIR}/simdjson
    )
    file(RENAME ${CMAKE_SOURCE_DIR}/simdjson/include ${CMAKE_SOURCE_DIR}/third-parties/simdjson)
    file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/simdjson)
endif()

# checking for fast_io
if(EXISTS ${CMAKE_SOURCE_DIR}/third-parties/fast_io)
    message(STATUS "Checking for fast_io - yes")
else()
    message(STATUS "Checking for fast_io - no")
    execute_process(
        COMMAND git clone -b next --depth=1 https://github.com/cppfastio/fast_io.git ${CMAKE_SOURCE_DIR}/fast_io
    )
    file(RENAME ${CMAKE_SOURCE_DIR}/fast_io/include ${CMAKE_SOURCE_DIR}/third-parties/fast_io)
    file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/fast_io)
endif()

include_directories(${CMAKE_SOURCE_DIR}/third-parties)

add_executable(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cc)
