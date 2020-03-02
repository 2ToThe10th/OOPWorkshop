cmake_minimum_required(VERSION 3.10)
project(StatisticInt)

set(CMAKE_CXX_STANDARD 14)

add_executable(StatisticInt main.cpp)

target_link_libraries(StatisticInt sfml-graphics sfml-window sfml-system sfml-audio sfml-network)