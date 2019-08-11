project(STalkerLibrary)

#Some people say that GLOB is a bad practice cuz after git pull you have to rerun cmake
# but I don't think it's a big problem. And CMAke is cleaner for sure
file(GLOB_RECURSE lib1_SOURCES
        "*.h"
        "*.cpp"
)

add_library(STalkerLibrary SHARED ${lib1_SOURCES})

target_compile_options(STalkerLibrary PRIVATE -Werror)
target_compile_features(STalkerLibrary PRIVATE cxx_std_17)

set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Threads REQUIRED)

#Those fixed paths look awful but they're meant for a fixed system(this very virtual machine)
#it's the simplest sufficient solutin in this case
target_include_directories(STalkerLibrary
	PUBLIC include
	PRIVATE src
        "/opt/ros/melodic/include/"
)

target_link_libraries(STalkerLibrary PRIVATE
    /opt/ros/melodic/lib/libroscpp.so
    /opt/ros/melodic/lib/librosconsole.so
    /usr/lib/x86_64-linux-gnu/libboost_system.so
    /usr/lib/x86_64-linux-gnu/libboost_thread.so
    Threads::Threads)
