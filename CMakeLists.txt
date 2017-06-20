cmake_minimum_required(VERSION 2.8)

project(k-means)

if (UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
endif ()

add_executable(k-means src/main.cpp src/k-means.cpp)
#target_link_libraries(k-means -L/usr/lib -L/usr/local/lib -std=c++11)

