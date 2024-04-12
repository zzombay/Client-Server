cmake_minimum_required(VERSION 3.28)
project(Client)

set(CMAKE_CXX_STANDARD 17)

add_executable(Client WIN32 src/main.cpp
        src/client.cpp
        src/client.h)


target_link_options(Client PRIVATE -mwindows)
if(WIN32)
    target_link_libraries(Client wsock32 ws2_32)
endif()