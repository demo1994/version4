cmake_minimum_required(VERSION 3.10)
project(udpversion2)

set(CMAKE_CXX_STANDARD 11)

add_executable(udpversion2 main.cpp packet.cpp packet.h udprelay.h router.h router.cpp)
find_package(Threads REQUIRED)
target_link_libraries(udpversion2 Threads::Threads)