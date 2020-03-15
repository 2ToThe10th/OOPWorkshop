//
// Created by 2ToThe10th on 10.03.2020.
//

#ifndef PLOTBUILDER_SRC_GRAPH_CPP_
#define PLOTBUILDER_SRC_GRAPH_CPP_

#include "Graph.hpp"


template <size_t allocate_memory_for_one_time>
Graph<allocate_memory_for_one_time>::Graph(
    const ChunkedVector<sf::Vector2u, allocate_memory_for_one_time> &graph,
    const sf::Color& color) {
  graph_ = graph;
  color_ = color;
}

template <size_t allocate_memory_for_one_time>
Graph<allocate_memory_for_one_time>::Graph(Graph &&graph) {
  graph_ = std::move(graph.graph_);
  color_ = std::move(color_);
}

template <size_t allocate_memory_for_one_time>
size_t Graph<allocate_memory_for_one_time>::Size() const {
  return graph_.Size();
}

template <size_t allocate_memory_for_one_time>
sf::Vector2u &Graph<allocate_memory_for_one_time>::operator[](size_t index) {
  return graph_.At(index);
}


template <size_t allocate_memory_for_one_time>
template <typename... Args>
void Graph<allocate_memory_for_one_time>::EmplaceBack(Args &&... args) {
  graph_.EmplaceBack(args...);
}

template <size_t allocate_memory_for_one_time>
sf::Color &Graph<allocate_memory_for_one_time>::Color() {
  return color_;
}

template <size_t allocate_memory_for_one_time>
const sf::Vector2u &
    Graph<allocate_memory_for_one_time>::operator[](size_t index) const {
  return graph_.ConstAt(index);
}

template <size_t allocate_memory_for_one_time>
const sf::Vector2u &Graph<allocate_memory_for_one_time>::Back() const {
  return graph_.Back();
}

#endif // PLOTBUILDER_SRC_GRAPH_CPP_
