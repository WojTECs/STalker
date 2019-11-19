project(STalkerApplicationExample)

set(SOURCES
	src/main.cpp
)

add_executable(STalkerApplicationExample ${SOURCES})

#pthread requires flags below on Arch derived systems to build properly
#Linux CC 4.19.59-1-MANJARO #1 SMP PREEMPT Mon Jul 15 18:23:58 UTC 2019 x86_64 GNU/Linux
set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)

target_compile_options(STalkerApplicationExample PRIVATE -Werror)
target_compile_features(STalkerApplicationExample PRIVATE cxx_std_17)

#Those fixed paths look awful but they're meant for a fixed system(this very virtual machine)
#it's the simplest sufficient solutin in this case
include_directories("/opt/ros/melodic/include/")
target_link_libraries(STalkerApplicationExample PRIVATE STalkerLibrary
    /opt/ros/melodic/lib/libroscpp.so
    /opt/ros/melodic/lib/librosconsole.so
    /opt/ros/melodic/lib/librostime.so
    /opt/ros/melodic/lib/librospack.so
    /opt/ros/melodic/lib/libroscpp_serialization.so
    /usr/lib/${ARCHITECTURE}/libboost_system.so
    /usr/lib/${ARCHITECTURE}/libboost_thread.so)













