project(STalkerApplicationExample)

set(SOURCES
	src/main.cpp
)

add_executable(STalkerApplicationExample ${SOURCES})

#pthread requires flags below on Arch derived systems to build properly
#Linux CC 4.19.59-1-MANJARO #1 SMP PREEMPT Mon Jul 15 18:23:58 UTC 2019 x86_64 GNU/Linux
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

target_compile_options(STalkerApplicationExample PRIVATE -Werror)
target_compile_features(STalkerApplicationExample PRIVATE cxx_std_17)

target_link_libraries(STalkerApplicationExample PRIVATE STalkerLibrary )
