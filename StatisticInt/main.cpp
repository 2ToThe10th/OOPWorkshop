#include <iostream>
#include <algorithm>
#include "algorithm.cpp"
#include "../PlotBuilder/src/PlotBuilder.hpp"
#include "../ChunkedVector/src/ChunkedVector.hpp"

constexpr size_t allocate_for_one_time = 100;

int32_t main() {

  PlotBuilder<allocate_for_one_time> plot(2);

  ChunkedVector<sf::Vector2u, allocate_for_one_time> bubble_sort;
  ChunkedVector<sf::Vector2u, allocate_for_one_time> std_sort;

  for (int number_of_element = 1e2; number_of_element < 1e3; number_of_element += 50) {
    StatisticInt array[number_of_element];
    for (int i = 0; i < number_of_element; ++i) {
      array[i] = rand();
    }

    StatisticInt::GetStatistic().MakeEmpty();
    BubbleSort(array, number_of_element);
    bubble_sort.EmplaceBack(number_of_element, StatisticInt::GetStatistic().GetNumberOfOperation());

    StatisticInt::GetStatistic().MakeEmpty();
    std::sort(array, array + number_of_element);
    std_sort.EmplaceBack(number_of_element, StatisticInt::GetStatistic().GetNumberOfOperation());
  }

  plot[0].SetWindowSize({1850, 1000});
  plot[0].SetName("Bubble sort vs std::sort");
  plot[0].AddGraph(bubble_sort, sf::Color::Red);
  plot[0].AddGraph(std_sort, sf::Color::Green);

  ChunkedVector<sf::Vector2u, allocate_for_one_time> stupid_exp;
  ChunkedVector<sf::Vector2u, allocate_for_one_time> bin_exp;

  for (int power = 1e3; power < 1e4; power += 500) {
    StatisticInt::GetStatistic().MakeEmpty();
    StupidExponentiation(2, power);
    stupid_exp.EmplaceBack(power, StatisticInt::GetStatistic().GetNumberOfOperation());

    StatisticInt::GetStatistic().MakeEmpty();
    BinomialExponentiation(2, power);
    bin_exp.EmplaceBack(power, StatisticInt::GetStatistic().GetNumberOfOperation());
  }

  plot[1].SetWindowSize({1850, 1000});
  plot[1].SetName("Stupid exponentiation vs binomial");
  plot[1].AddGraph(stupid_exp, sf::Color::Red);
  plot[1].AddGraph(bin_exp, sf::Color::Green);



  plot.Draw();

  return 0;
}
