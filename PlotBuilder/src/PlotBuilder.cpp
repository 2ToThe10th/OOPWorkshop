//
// Created by 2ToThe10th on 10.03.2020.
//
#ifndef PLOTBUILDER_SRC_PLOTBUILDER_CPP_
#define PLOTBUILDER_SRC_PLOTBUILDER_CPP_

#include "PlotBuilder.hpp"

template <size_t allocate_memory_for_one_time>
PlotBuilder<allocate_memory_for_one_time>::PlotBuilder(size_t number_of_plot) {
  plot_.Resize(number_of_plot);
  for (size_t i = 0; i < number_of_plot; ++i) {
    plot_[i] = new Plot<allocate_memory_for_one_time>();
  }
}

template <size_t allocate_memory_for_one_time>
inline Plot<allocate_memory_for_one_time> &
PlotBuilder<allocate_memory_for_one_time>::At(size_t number_of_plot) {
  assert(plot_.At(number_of_plot) != nullptr);
  return *plot_.At(number_of_plot);
}

template <size_t allocate_memory_for_one_time>
inline Plot<allocate_memory_for_one_time> &
    PlotBuilder<allocate_memory_for_one_time>::operator[](
        size_t number_of_plot) {
  return At(number_of_plot);
}

template <size_t allocate_memory_for_one_time>
void PlotBuilder<allocate_memory_for_one_time>::Draw() {
  for (size_t i = 0; i < plot_.Size(); ++i) {
    plot_[i]->Draw();
  }

  while (ThereIsOpenWindow()) {
    for (size_t i = 0; i < plot_.Size(); ++i) {
      if (plot_[i] != nullptr) {
        plot_[i]->PollEvent();
      }
    }
  }
}
template <size_t allocate_memory_for_one_time>
bool PlotBuilder<allocate_memory_for_one_time>::ThereIsOpenWindow() {
  bool there_is_open_window = false;
  for (size_t i = 0; i < plot_.Size(); ++i) {
    if (plot_[i] != nullptr) {
      if (plot_[i]->IsOpen()) {
        there_is_open_window = true;
      } else {
        delete plot_[i];
        plot_[i] = nullptr;
      }
    }
  }
  return there_is_open_window;
}

#endif // PLOTBUILDER_SRC_PLOTBUILDER_CPP_
