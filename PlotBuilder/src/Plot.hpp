//
// Created by 2ToThe10th on 24.02.2020.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../../ChunkedVector/src/ChunkedVector.hpp"

#ifndef PLOTBUILDER_SRC_PLOT_H_
#define PLOTBUILDER_SRC_PLOT_H_

template<size_t allocate_memory_for_one_time>
class Plot {
 public:
  Plot() = default;
  explicit Plot(const sf::Vector2u &size_of_window);

  bool IsOpen();
  void PollEvent();
  void AddGraph(const ChunkedVector<sf::Vector2u, allocate_memory_for_one_time> &new_graph, sf::Color color);
  void SetName(const std::string &new_window_name);
  void SetWindowSize(const sf::Vector2u new_window_size);
  void Draw();

  ~Plot() = default;

 private:
  std::string window_name_;
  sf::Vector2u window_size_ = sf::Vector2u(1200, 800);
  sf::RenderWindow window_;
  ChunkedVector<ChunkedVector<sf::Vector2u, allocate_memory_for_one_time>, allocate_memory_for_one_time> graph_;
  ChunkedVector<sf::Color, allocate_memory_for_one_time> color_;
};

template<size_t allocate_memory_for_one_time>
Plot<allocate_memory_for_one_time>::Plot(const sf::Vector2u &size_of_window) {
  window_size_ = size_of_window;
}

template<size_t allocate_memory_for_one_time>
void Plot<allocate_memory_for_one_time>::PollEvent() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_.close();
    }
  }
}

template<size_t allocate_memory_for_one_time>
bool Plot<allocate_memory_for_one_time>::IsOpen() {
  return window_.isOpen();
}

template<size_t allocate_memory_for_one_time>
void Plot<allocate_memory_for_one_time>::AddGraph(const ChunkedVector<sf::Vector2u,
                                                                      allocate_memory_for_one_time> &new_graph,
                                                  sf::Color color) {
  for (size_t i = 1; i < new_graph.Size(); ++i) {
    assert(new_graph[i - 1].x < new_graph[i].x);
  }
  graph_.EmplaceBack(new_graph);
  color_.EmplaceBack(color);
}

template<size_t allocate_memory_for_one_time>
void Plot<allocate_memory_for_one_time>::SetName(const std::string &new_window_name) {
  window_name_ = new_window_name;
}

template<size_t allocate_memory_for_one_time>
void Plot<allocate_memory_for_one_time>::SetWindowSize(const sf::Vector2u new_window_size) {
  window_size_ = new_window_size;
}
template<size_t allocate_memory_for_one_time>
void Plot<allocate_memory_for_one_time>::Draw() {
  window_.create(sf::VideoMode(window_size_.x, window_size_.y), window_name_, sf::Style::Close);
  window_.clear(sf::Color::White);

  float place_for_number = 0.08;
  float axis_thickness = 5;
  float point_radius = 5;
  float line_thickness = 1;
  sf::Vector2f start_position = {place_for_number * window_size_.x, place_for_number * window_size_.y};

  //std::cout << start_position.x << ' ' << start_position.y << std::endl;

  sf::RectangleShape
    axis_x(sf::Vector2f((1 - place_for_number) * window_size_.x + axis_thickness / 2, axis_thickness));
  axis_x.setFillColor(sf::Color::Black);
  axis_x.setPosition(start_position.x - axis_thickness / 2, window_size_.y - (start_position.y + axis_thickness / 2));

//  std::cout << axis_x.getPosition().x << ' ' << axis_x.getPosition().y << std::endl;
  window_.draw(axis_x);

  sf::RectangleShape
    axis_y(sf::Vector2f(axis_thickness, (1 - place_for_number) * window_size_.y + axis_thickness / 2));
  axis_y.setFillColor(sf::Color::Black);
  axis_y.setPosition(start_position.x - axis_thickness / 2, 0);
  window_.draw(axis_y);


  for (size_t i = 0; i < graph_.Size(); ++i) {
    for (int point_number = 0; point_number < graph_[i].Size(); ++point_number) {
      sf::CircleShape point(point_radius);
      point.setPosition(start_position.x + graph_[i][point_number].x - point_radius,
                        window_size_.y - (start_position.y + graph_[i][point_number].y + point_radius));
      //std::cout << point.getPosition().x + point_radius << ' ' << point.getPosition().y - point_radius << std::endl;
      point.setFillColor(color_[i]);
      window_.draw(point);
    }
    if (graph_[i].Size() > 1) {
      std::cout << "i=" << i << std::endl;
      sf::VertexArray line_of_graph(sf::TriangleStrip, 2 * graph_[i].Size());
      for (size_t point_number = 0; point_number < graph_[i].Size(); ++point_number) {
        line_of_graph[2 * point_number].position = sf::Vector2f(start_position.x + graph_[i][point_number].x, window_size_.y - (start_position.y + graph_[i][point_number].y + line_thickness / 2));
        line_of_graph[2 * point_number].color = color_[i];
        line_of_graph[2 * point_number + 1].position = sf::Vector2f(start_position.x + graph_[i][point_number].x, window_size_.y - (start_position.y + graph_[i][point_number].y - line_thickness / 2));
        line_of_graph[2 * point_number + 1].color = color_[i];
        std::cout << line_of_graph[2 * point_number].position.x << ' ' << line_of_graph[2 * point_number].position.y << ' '
                  << line_of_graph[2 * point_number + 1].position.x << ' ' << line_of_graph[2 * point_number + 1].position.y << std::endl;
      }
      window_.draw(line_of_graph);
    }
  }

  window_.display();
}

#endif //PLOTBUILDER_SRC_PLOT_H_

