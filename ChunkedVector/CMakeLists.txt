cmake_minimum_required(VERSION 3.15)
project(ChunkedVector)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(../googletest build)
include_directories(../googletest/googletest/include)
include_directories(../googletest/googlemock/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
include_directories(test)
set(SOURCE_DEBUG_FILES test/test.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES src/main.cpp src/ChunkedVector.hpp src/ChunkedVector.cpp)

add_executable(ChunkedVector ${SOURCE_FILES} ${SOURCE_DEBUG_FILES})
target_link_libraries(ChunkedVector gtest gtest_main)
