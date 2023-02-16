cmake_minimum_required(VERSION 3.16)
project(http_server)

set(CMAKE_CXX_STANDARD 20)
# http server
add_executable(http_server main.cpp)
find_package(Threads REQUIRED)
target_link_libraries(http_server Threads::Threads)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(http_server Threads::Threads)
find_package(Boost COMPONENTS thread REQUIRED chrono)
target_link_libraries(http_server Boost::thread)
target_include_directories(http_server PRIVATE helpers)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -include types.hpp network.hpp helpers.hpp constants.hpp helpers/http/headers.hpp helpers/http/server_info.hpp helpers/http/file.hpp helpers/http/logger.hpp")