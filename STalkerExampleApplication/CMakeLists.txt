project(STalkerApplicationExample)

add_executable(STalkerApplicationExample src/main.cpp)
target_compile_options(STalkerApplicationExample PRIVATE -Werror)

find_package(Boost)
if(Boost_FOUND)
    target_include_directories(STalkerApplicationExample PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(STalkerApplicationExample PRIVATE ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Boost couldn't be find.")
endif()

find_package(roscpp)
if(roscpp_FOUND)
    target_include_directories(STalkerApplicationExample PRIVATE ${roscpp_INCLUDE_DIRS})
    target_link_libraries(STalkerApplicationExample PRIVATE ${roscpp_LIBRARIES})
else()
    message(FATAL_ERROR "RosCpp couldn't be find.")
endif()

target_link_libraries(STalkerApplicationExample PRIVATE STalkerLibrary)













