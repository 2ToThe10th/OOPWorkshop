//
// Created by 2ToThe10th on 15.02.2020.
//
#ifndef STATISTICINT_ALGORITHM_H
#define STATISTICINT_ALGORITHM_H

#include <vector>
#include "StatisticInt.h"


StatisticInt BinomialExponentiation(StatisticInt argument, StatisticInt degree) {
  if (degree == StatisticInt(0))
    return StatisticInt(1);
  if (degree % StatisticInt(2) == StatisticInt(1))
    return BinomialExponentiation(argument, degree - 1) * argument;
  else {
    StatisticInt argument_in_doubled_degree =
      BinomialExponentiation(argument, degree / 2);
    return argument_in_doubled_degree * argument_in_doubled_degree;
  }
}

StatisticInt StupidExponentiation(StatisticInt argument, StatisticInt degree) {
  StatisticInt answer = 1;
  for (StatisticInt i = 0; i < degree; ++i) {
    answer *= argument;
  }
  return answer;
}

int FindEulerFunction(int number) {
  int euler_function_of_number = number;
  for (int i = 2; i * i <= number; i += 1)
    if (number % i == 0) {
      while (number % i == 0)
        number /= i;
      euler_function_of_number -= euler_function_of_number / i;
    }
  if (number > 1)
    euler_function_of_number -= euler_function_of_number / number;
  return euler_function_of_number;
}

int GCD(int first, int second) {
  if (second == 0)
    return first;
  else
    return GCD(second, first % second);
}

void BubbleSort(StatisticInt* start_of_array, StatisticInt number_of_elements) {
  for (StatisticInt i = 1; i < number_of_elements; ++i) {
    for (StatisticInt j = 1; j < number_of_elements - i + 1; ++j) {
      if (start_of_array[j - 1] > start_of_array[j]) {
        std::swap(start_of_array[j - 1], start_of_array[j]);
      }
    }
  }
}

void SelectionSort(StatisticInt* start_of_array, StatisticInt number_of_elements) {
  for (StatisticInt i = 1; i < number_of_elements; ++i) {
    int min_element = start_of_array[i];
    int min_index = i;
    for (StatisticInt j = i + 1; j < number_of_elements; ++j) {
      if (start_of_array[j] < min_element) {
        min_element = start_of_array[j];
        min_index = j;
      }
    }
    if (min_index > i) {
      std::swap(start_of_array[i], start_of_array[min_index]);
    }
  }
}

void BubbleSortVector(std::vector<int> vector) {
  for (size_t i = 1; i < vector.size(); ++i) {
    for (size_t j = 1; j < vector.size() - i; ++j) {
      if (vector[j - 1] > vector[j]) {
        std::swap(vector[j - 1], vector[j]);
      }
    }
  }
}

#endif
