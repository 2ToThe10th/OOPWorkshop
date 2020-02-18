//
// Created by 2ToThe10th on 15.02.2020.
//
#ifndef STATISTICINT_ALGORITHM_H
#define STATISTICINT_ALGORITHM_H

#include <vector>
#include "StatisticInt.h"

#define int StatisticInt

int BinomialExponentiation(int argument, int degree) {
  if (degree == 0)
    return 1;
  if (degree % 2 == 1)
    return BinomialExponentiation(argument, degree - 1) * argument;
  else {
    int argument_in_doubled_degree =
      BinomialExponentiation(argument, degree / 2);
    return argument_in_doubled_degree * argument_in_doubled_degree;
  }
}

int StupidExponentiation(int argument, int degree) {
  int answer = 1;
  for (int i = 0; i < degree; ++i) {
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

void BubbleSort(int* start_of_array, int number_of_elements) {
  for (int i = 1; i < number_of_elements; ++i) {
    for (int j = 1; j < number_of_elements - i; ++j) {
      if (start_of_array[j - 1] > start_of_array[j]) {
        std::swap(start_of_array[j - 1], start_of_array[j]);
      }
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
