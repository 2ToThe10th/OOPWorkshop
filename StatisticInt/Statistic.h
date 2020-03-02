//
// Created by 2ToThe10th on 15.02.2020.
//
#include <fstream>

#ifndef STATISTICINT_STATISTIC_H
#define STATISTICINT_STATISTIC_H

#include <cstdlib>
class Statistic {
 public:
  inline void IncreaseNumberOfPlus() {
    ++number_of_plus_;
  }

  inline void IncreaseNumberOfAssigment() {
    ++number_of_assignment_;
  }

  inline void IncreaseNumberOfDivide() {
    ++number_of_divide_;
  }

  inline void IncreaseNumberOfMultiply() {
    ++number_of_multiply_;
  }

  inline void IncreaseNumberOfCompare() {
    ++number_of_compare_;
  }

  inline void IncreaseNumberOfConstructor() {
    ++number_of_constructor_;
  }
  inline void IncreaseNumberOfDestructor() {
    ++number_of_destructor_;
  }

  inline size_t GetNumberOfPlus() {
    return number_of_plus_;
  }

  inline size_t GetNumberOfAssigment() {
    return number_of_assignment_;
  }

  inline size_t GetNumberOfDivide() {
    return number_of_divide_;
  }

  inline size_t GetNumberOfMultiply() {
    return number_of_multiply_;
  }

  inline size_t GetNumberOfCompare() {
    return number_of_compare_;
  }

  inline size_t GetNumberOfConstructor() {
    return number_of_constructor_;
  }

  inline size_t GetNumberOfDestructor() {
    return number_of_destructor_;
  }

  inline size_t GetNumberOfOperation() {
    return number_of_plus_ + number_of_assignment_ + number_of_multiply_ + number_of_divide_ + number_of_compare_
      + number_of_constructor_ + number_of_destructor_;
  }

  inline void PrintStatistic(std::ostream &out) {
    out << "Number of Plus operations = " << number_of_plus_ << "\n"
        << "Number of Assigment = " << number_of_assignment_ << "\n"
        << "Number of Multiply = " << number_of_multiply_ << "\n"
        << "Number of Divide = " << number_of_divide_ << "\n"
        << "Number of Compares = " << number_of_compare_ << "\n"
        << "Number of Constructor = " << number_of_constructor_ << "\n"
        << "Number of Destructor = " << number_of_destructor_ << "\n"
        << "-------------------------------------------------------\n";
  }

  void MakeEmpty() {
    number_of_plus_ = 0;
    number_of_assignment_ = 0;
    number_of_multiply_ = 0;
    number_of_divide_ = 0;
    number_of_compare_ = 0;
    number_of_constructor_ = 0;
    number_of_destructor_ = 0;
  }

 private:
  size_t number_of_plus_ = 0;
  size_t number_of_multiply_ = 0;
  size_t number_of_divide_ = 0;
  size_t number_of_compare_ = 0;
  size_t number_of_assignment_ = 0;
  size_t number_of_constructor_ = 0;
  size_t number_of_destructor_ = 0;
};

#endif // STATISTICINT_STATISTIC_H
