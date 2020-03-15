//
// Created by 2ToThe10th on 10.03.2020.
//

#ifndef PLOTBUILDER_SRC_GRAPH_HPP_
#define PLOTBUILDER_SRC_GRAPH_HPP_

#include "../../ChunkedVector/src/ChunkedVector.hpp"
#include <SFML/Graphics.hpp>

template <size_t allocate_memory_for_one_time> class Graph {
public:

  Graph(const ChunkedVector<sf::Vector2u, allocate_memory_for_one_time>& graph, const sf::Color& color);
  Graph(Graph&& graph);
  size_t Size() const;
  sf::Vector2u &operator[](size_t index);
  const sf::Vector2u &operator[](size_t index) const;
  const sf::Vector2u &Back() const;
  template <typename... Args> inline void EmplaceBack(Args &&... args);
  sf::Color &Color();

private:
  ChunkedVector<sf::Vector2u, allocate_memory_for_one_time> graph_;
  sf::Color color_;
};
#include "Graph.cpp"

#endif // PLOTBUILDER_SRC_GRAPH_HPP_
