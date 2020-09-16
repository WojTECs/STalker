project(STalkerLibrary)

file(GLOB_RECURSE LIB_SOURCES
        "*.h"
        "*.cpp")

add_library(STalkerLibrary SHARED ${LIB_SOURCES})
target_compile_options(STalkerLibrary PRIVATE -Werror)

find_package(Threads REQUIRED)
if(Threads_FOUND)
    target_include_directories(STalkerLibrary PRIVATE ${Threads_INCLUDE_DIRS})
    target_link_libraries(STalkerLibrary PRIVATE ${Threads_LIBRARIES})
else()
    message(FATAL_ERROR "Library 'Threads' couldn't be find.")
endif()

find_package(Boost)
if(Boost_FOUND)
    target_include_directories(STalkerLibrary PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(STalkerLibrary PRIVATE ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Boost couldn't be find.")
endif()

find_package(roscpp)
if(roscpp_FOUND)
    target_include_directories(STalkerLibrary PRIVATE ${roscpp_INCLUDE_DIRS})
    target_link_libraries(STalkerLibrary PRIVATE ${roscpp_LIBRARIES})
else()
    message(FATAL_ERROR "RosCpp couldn't be find.")
endif()

target_include_directories(STalkerLibrary
        PUBLIC include
        PRIVATE src
)
