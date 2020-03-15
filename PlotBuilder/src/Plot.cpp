//
// Created by 2ToThe10th on 10.03.2020.
//

#ifndef PLOTBUILDER_SRC_PLOT_CPP_
#define PLOTBUILDER_SRC_PLOT_CPP_

#include "Plot.hpp"

template <size_t allocate_memory_for_one_time>
Plot<allocate_memory_for_one_time>::Plot(const sf::Vector2u &size_of_window) {
  window_size_ = size_of_window;
}

template <size_t allocate_memory_for_one_time>
void Plot<allocate_memory_for_one_time>::PollEvent() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window_.close();
    }
  }
}

template <size_t allocate_memory_for_one_time>
bool Plot<allocate_memory_for_one_time>::IsOpen() {
  return window_.isOpen();
}

template <size_t allocate_memory_for_one_time>
void Plot<allocate_memory_for_one_time>::AddGraph(
    const ChunkedVector<sf::Vector2u, allocate_memory_for_one_time> &new_graph,
    const sf::Color &color) {
  size_of_graph_y_ = std::max<size_t>(size_of_graph_y_, new_graph[0].y);
  for (size_t i = 1; i < new_graph.Size(); ++i) {
    assert(new_graph[i - 1].x < new_graph[i].x);
    size_of_graph_y_ = std::max<size_t>(size_of_graph_y_, new_graph[i].y);
  }
  if (new_graph.Size()) {
    size_of_graph_x_ = std::max<size_t>(size_of_graph_x_, new_graph.Back().x);
  }
  graph_vector_.EmplaceBack(new_graph, color);
}

template <size_t allocate_memory_for_one_time>
void Plot<allocate_memory_for_one_time>::SetName(
    const std::string &new_window_name) {
  window_name_ = new_window_name;
}

template <size_t allocate_memory_for_one_time>
void Plot<allocate_memory_for_one_time>::SetWindowSize(
    const sf::Vector2u &new_window_size) {
  window_size_ = new_window_size;
  start_position_ = {place_for_number_ * window_size_.x,
                     place_for_number_ * window_size_.y};
  place_for_graph_ = {
      (unsigned int)std::floor(window_size_.x - start_position_.x),
      (unsigned int)std::floor(window_size_.y - start_position_.y)};
}

template <size_t allocate_memory_for_one_time>
void Plot<allocate_memory_for_one_time>::Draw() {
  window_.create(sf::VideoMode(window_size_.x, window_size_.y), window_name_,
                 sf::Style::Close);
  window_.clear(sf::Color::White);

  DrawAxis();

  DrawAndRoundScale();

  for (size_t k = 0; k < graph_vector_.Size(); ++k) {
    DrawKthGraph(k);
  }

  window_.display();
}

template <size_t allocate_memory_for_one_time>
void Plot<allocate_memory_for_one_time>::DrawAxis() {
  sf::RectangleShape axis_x(sf::Vector2f(
      (1 - place_for_number_) * window_size_.x + axis_thickness_ / 2,
      axis_thickness_));
  axis_x.setFillColor(sf::Color::Black);
  axis_x.setPosition(start_position_.x - axis_thickness_ / 2,
                     window_size_.y -
                         (start_position_.y + axis_thickness_ / 2));
  window_.draw(axis_x);

  sf::RectangleShape axis_y(
      sf::Vector2f(axis_thickness_, (1 - place_for_number_) * window_size_.y +
                                        axis_thickness_ / 2));
  axis_y.setFillColor(sf::Color::Black);
  axis_y.setPosition(start_position_.x - axis_thickness_ / 2, 0);
  window_.draw(axis_y);
}

template <size_t allocate_memory_for_one_time>
void Plot<allocate_memory_for_one_time>::GetScientificFormAndRound(
    size_t &number, size_t &power, size_t &significand) {
  size_t old_number = number;
  number = 1;
  while (old_number >= 100) {
    old_number /= 10;
    number *= 10;
    ++power;
  }
  significand = old_number + 1;
  number *= significand;
}

template <size_t allocate_memory_for_one_time>
void Plot<allocate_memory_for_one_time>::DrawAndRoundScale() {
  size_t power_x = 0;
  size_t significand_x = 0;
  size_t power_y = 0;
  size_t significand_y = 0;

  GetScientificFormAndRound(size_of_graph_x_, power_x, significand_x);
  GetScientificFormAndRound(size_of_graph_y_, power_y, significand_y);

  sf::Font font;
  if (!font.loadFromFile(
          "/home/sasha/OOPWorkshop/PlotBuilder/res/ArialMT.ttf")) {
    std::cout << "font not loaded" << std::endl;
    return;
  }

  int count_of_number_on_x =
      (place_for_graph_.x - place_not_to_write_) / period;
  for (int i = 1; i <= count_of_number_on_x; ++i) {
    std::string string_to_draw =
        std::to_string((significand_x / count_of_number_on_x) * i);
    if (power_x > 0) {
      string_to_draw += "e" + std::to_string(power_x);
    }
    sf::Vector2f where_to_place = {
        start_position_.x +
            GetXOnGraph((size_of_graph_x_ / count_of_number_on_x) * i) -
            expected_size_of_text_x_,
        (1 - place_for_number_ / 2) * window_size_.y -
            expected_size_of_text_y_};
    sf::Text text(string_to_draw, font);
    text.setPosition(where_to_place);
    text.setFillColor(sf::Color::Black);
    window_.draw(text);
  }

  int count_of_number_on_y =
      (place_for_graph_.y - place_not_to_write_) / period;
  for (int i = 1; i <= count_of_number_on_y; ++i) {
    std::string string_to_draw =
        std::to_string((significand_y / count_of_number_on_y) * i);
    if (power_y > 0) {
      string_to_draw += "e" + std::to_string(power_y);
    }
    sf::Vector2f where_to_place = {
        (place_for_number_ / 2) * window_size_.x - expected_size_of_text_x_,
        window_size_.y -
            (start_position_.y +
             GetYOnGraph((size_of_graph_y_ / count_of_number_on_y) * i)) -
            expected_size_of_text_y_};
    sf::Text text(string_to_draw, font);
    text.setPosition(where_to_place);
    text.setFillColor(sf::Color::Black);
    window_.draw(text);
  }
}

template <size_t allocate_memory_for_one_time>
void Plot<allocate_memory_for_one_time>::DrawKthGraph(size_t k) {
  // draw points:
  for (int point_number = 0; point_number < graph_vector_[k].Size();
       ++point_number) {
    sf::CircleShape point(point_radius_);
    point.setPosition(
        start_position_.x + GetXOnGraph(graph_vector_[k][point_number].x) -
            point_radius_,
        window_size_.y -
            (start_position_.y + GetYOnGraph(graph_vector_[k][point_number].y) +
             point_radius_));
    point.setFillColor(graph_vector_[k].Color());
    window_.draw(point);
  }
  // draw lines:
  if (graph_vector_[k].Size() > 1) {
    sf::VertexArray line_of_graph(sf::Lines, 2);
    for (size_t point_number = 1; point_number < graph_vector_[k].Size();
         ++point_number) {
      line_of_graph[0].position = sf::Vector2f(
          start_position_.x + GetXOnGraph(graph_vector_[k][point_number - 1].x),
          window_size_.y - (start_position_.y +
                            GetYOnGraph(graph_vector_[k][point_number - 1].y)));
      line_of_graph[0].color = graph_vector_[k].Color();
      line_of_graph[1].position = sf::Vector2f(
          start_position_.x + GetXOnGraph(graph_vector_[k][point_number].x),
          window_size_.y - (start_position_.y +
                            GetYOnGraph(graph_vector_[k][point_number].y)));
      line_of_graph[1].color = graph_vector_[k].Color();
      window_.draw(line_of_graph);
    }
  }
}

template <size_t allocate_memory_for_one_time>
float Plot<allocate_memory_for_one_time>::GetXOnGraph(unsigned int x) {
  return ((float)x / size_of_graph_x_) *
         (place_for_graph_.x - place_not_to_write_);
}
template <size_t allocate_memory_for_one_time>
float Plot<allocate_memory_for_one_time>::GetYOnGraph(unsigned int y) {
  return ((float)y / size_of_graph_y_) *
         (place_for_graph_.y - place_not_to_write_);
}

#endif // PLOTBUILDER_SRC_PLOT_CPP_
