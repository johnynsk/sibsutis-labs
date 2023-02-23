cmake_minimum_required(VERSION 3.16)
project(lab3)
include_directories("/opt/boost/")

set(BOOST_ROOT "/opt/boost/boost_1_81_0/" CACHE PATH "Boost library path" )
set(Boost_NO_SYSTEM_PATHS on CACHE BOOL "Do not search system for Boost" )

set(CMAKE_CXX_STANDARD 20)
add_executable(server server.cpp)

find_package(Threads REQUIRED)
target_link_libraries(server Threads::Threads)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost COMPONENTS program_options)
target_link_libraries(server Boost::program_options)
target_include_directories(server PRIVATE src)

add_executable(client client.cpp)
find_package(Boost 1.81.0 COMPONENTS program_options)
target_link_libraries(client Boost::program_options)
target_include_directories(client PRIVATE src)