//
// Created by 2ToThe10th on 24.02.2020.
//
#ifndef PLOTBUILDER_SRC_PLOT_HPP_
#define PLOTBUILDER_SRC_PLOT_HPP_

#include "Graph.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

template <size_t allocate_memory_for_one_time> class Plot {
public:
  Plot() = default;
  explicit Plot(const sf::Vector2u &size_of_window);

  bool IsOpen();
  void PollEvent();
  void AddGraph(const ChunkedVector<sf::Vector2u, allocate_memory_for_one_time>
                    &new_graph,
                const sf::Color &color);
  void SetName(const std::string &new_window_name);
  void SetWindowSize(const sf::Vector2u &new_window_size);
  void Draw();

  ~Plot() = default;

private:
  void GetScientificFormAndRound(size_t &number, size_t &power,
                                 size_t &significand);
  void DrawAxis();
  void DrawAndRoundScale();
  void DrawKthGraph(size_t k);
  float GetXOnGraph(unsigned int x);
  float GetYOnGraph(unsigned int y);

  std::string window_name_;
  sf::Vector2u window_size_ = sf::Vector2u(1200, 800);
  sf::RenderWindow window_;
  ChunkedVector<Graph<allocate_memory_for_one_time>,
                allocate_memory_for_one_time>
      graph_vector_;

  size_t size_of_graph_y_ = 10;
  size_t size_of_graph_x_ = 10;
  constexpr static const float place_for_number_ = 0.08;
  sf::Vector2f start_position_ = {place_for_number_ * window_size_.x,
                                  place_for_number_ *window_size_.y};
  sf::Vector2u place_for_graph_ = {
      (unsigned int)std::floor(window_size_.x - start_position_.x),
      (unsigned int)std::floor(window_size_.y - start_position_.y)};
  constexpr static const float axis_thickness_ = 5;
  constexpr static const float point_radius_ = 5;
  constexpr static const unsigned int period = 200;
  constexpr static const unsigned int place_not_to_write_ = 100;
  constexpr static const float expected_size_of_text_x_ = 35;
  constexpr static const float expected_size_of_text_y_ = 25;
};

#include "Plot.cpp"

#endif // PLOTBUILDER_SRC_PLOT_HPP_
