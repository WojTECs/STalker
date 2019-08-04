project(STalkerLibrary)

file(GLOB_RECURSE lib1_SOURCES
        "*.h"
        "*.cpp"
)

add_library(STalkerLibrary SHARED ${lib1_SOURCES})

target_compile_options(STalkerLibrary PRIVATE -Werror)
target_compile_features(STalkerLibrary PRIVATE cxx_std_17)

#pthread requires flags below on Arch derived systems to build properly
#Linux CC 4.19.59-1-MANJARO #1 SMP PREEMPT Mon Jul 15 18:23:58 UTC 2019 x86_64 GNU/Linux
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread -lstdc++fs")

find_package(Threads REQUIRED)

target_include_directories(STalkerLibrary
	PUBLIC include
	PRIVATE src
)

target_link_libraries(STalkerLibrary PRIVATE /usr/lib/x86_64-linux-gnu/libboost_system.so /usr/lib/x86_64-linux-gnu/libboost_thread.so Threads::Threads)
