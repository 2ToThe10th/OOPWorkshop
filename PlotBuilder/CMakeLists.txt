cmake_minimum_required(VERSION 3.10)
project(PlotBuilder)

set(CMAKE_CXX_STANDARD 17)

add_executable(PlotBuilder main.cpp src/PlotBuilder.hpp src/Plot.hpp src/PlotBuilder.cpp src/Plot.cpp src/Graph.cpp src/Graph.hpp)

target_link_libraries(PlotBuilder sfml-graphics sfml-window sfml-system sfml-audio sfml-network)