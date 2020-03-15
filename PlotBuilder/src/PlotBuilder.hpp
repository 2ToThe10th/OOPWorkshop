//
// Created by 2ToThe10th on 24.02.2020.
//
#ifndef PLOTBUILDER_SRC_PLOTBUILDER_HPP_
#define PLOTBUILDER_SRC_PLOTBUILDER_HPP_

#include "Plot.hpp"

template <size_t allocate_memory_for_one_time> class PlotBuilder {
public:
  explicit PlotBuilder(size_t number_of_plot);

  inline Plot<allocate_memory_for_one_time> &At(size_t number_of_plot);
  inline Plot<allocate_memory_for_one_time> &operator[](size_t number_of_plot);

  void Draw();

private:
  inline bool ThereIsOpenWindow();

  ChunkedVector<Plot<allocate_memory_for_one_time> *,
                allocate_memory_for_one_time>
      plot_;
};

#include "PlotBuilder.cpp"

#endif // PLOTBUILDER_SRC_PLOTBUILDER_HPP_
