cmake_minimum_required(VERSION 3.7)

if(NOT UNIX)
    message(FATAL_ERROR "The library is meant only for Unix. Your platform is not supported.")
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug FORCE)
endif()

set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

message(STATUS "Setting build type - ${CMAKE_BUILD_TYPE}")

project(STalker)

add_subdirectory(STalkerExampleApplication)
add_subdirectory(STalkerLibrary)

message(STATUS "CMake ${CMAKE_VERSION} successfully configured ${PROJECT_NAME} using ${CMAKE_GENERATOR} generator")
