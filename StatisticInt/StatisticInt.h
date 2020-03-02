//
// Created by 2ToThe10th on 15.02.2020.
//
#ifndef STATISTICINT_STATISTICINT_H
#define STATISTICINT_STATISTICINT_H

#include "Statistic.h"

class StatisticInt {
 public:
  // constructor
  StatisticInt() : number_(0) {
    statistic.IncreaseNumberOfConstructor();
  }

  StatisticInt(int number) : number_(number) {
    statistic.IncreaseNumberOfConstructor();
  }

  StatisticInt(const StatisticInt& other) : number_(other.number_) {
    statistic.IncreaseNumberOfConstructor();
  }

  // =
  StatisticInt &operator=(const StatisticInt &other) {
    statistic.IncreaseNumberOfAssigment();
    number_ = other.number_;
    return *this;
  }

  StatisticInt &operator=(const int other) {
    statistic.IncreaseNumberOfAssigment();
    number_ = other;
    return *this;
  }

  // +=
  StatisticInt &operator+=(const StatisticInt &other) {
    statistic.IncreaseNumberOfPlus();
    number_ += other.number_;
    return *this;
  }

  StatisticInt &operator+=(const int other) {
    statistic.IncreaseNumberOfPlus();
    number_ += other;
    return *this;
  }

  // ++
  StatisticInt &operator++() {
    statistic.IncreaseNumberOfPlus();
    ++number_;
    return *this;
  }

  StatisticInt operator++(int) {
    statistic.IncreaseNumberOfPlus();
    return StatisticInt(number_++);
  }

  // -=
  StatisticInt &operator-=(const StatisticInt &other) {
    statistic.IncreaseNumberOfPlus();
    number_ -= other.number_;
    return *this;
  }

  StatisticInt &operator-=(const int other) {
    statistic.IncreaseNumberOfPlus();
    number_ -= other;
    return *this;
  }

  // --
  StatisticInt &operator--() {
    statistic.IncreaseNumberOfPlus();
    --number_;
    return *this;
  }

  StatisticInt operator--(int) {
    statistic.IncreaseNumberOfPlus();
    return StatisticInt(number_--);
  }

  // *=
  StatisticInt &operator*=(const StatisticInt &other) {
    statistic.IncreaseNumberOfMultiply();
    number_ *= other.number_;
    return *this;
  }

  StatisticInt &operator*=(const int other) {
    statistic.IncreaseNumberOfMultiply();
    number_ *= other;
    return *this;
  }

  // /=
  StatisticInt &operator/=(const StatisticInt &other) {
    statistic.IncreaseNumberOfDivide();
    number_ /= other.number_;
    return *this;
  }

  StatisticInt &operator/=(const int other) {
    statistic.IncreaseNumberOfMultiply();
    number_ /= other;
    return *this;
  }

  // %=
  StatisticInt &operator%=(const StatisticInt &other) {
    statistic.IncreaseNumberOfDivide();
    number_ %= other.number_;
    return *this;
  }

  StatisticInt &operator%=(const int other) {
    statistic.IncreaseNumberOfMultiply();
    number_ %= other;
    return *this;
  }

  // +
  StatisticInt operator+(const StatisticInt &other) {
    statistic.IncreaseNumberOfPlus();
    return StatisticInt(number_ + other.number_);
  }

  StatisticInt operator+(const int other) {
    statistic.IncreaseNumberOfPlus();
    return StatisticInt(number_ + other);
  }

  friend StatisticInt operator+(const int first, const StatisticInt &second) {
    statistic.IncreaseNumberOfPlus();
    return StatisticInt(first + second.number_);
  }

  // -
  StatisticInt operator-(const StatisticInt &other) {
    statistic.IncreaseNumberOfPlus();
    return StatisticInt(number_ - other.number_);
  }

  StatisticInt operator-(const int other) {
    statistic.IncreaseNumberOfPlus();
    return StatisticInt(number_ - other);
  }

  friend StatisticInt operator-(const int first, const StatisticInt &second) {
    statistic.IncreaseNumberOfPlus();
    return StatisticInt(first - second.number_);
  }

  // *
  StatisticInt operator*(const StatisticInt &other) {
    statistic.IncreaseNumberOfPlus();
    return StatisticInt(number_ * other.number_);
  }

  StatisticInt operator*(const int other) {
    statistic.IncreaseNumberOfPlus();
    return StatisticInt(number_ * other);
  }

  friend StatisticInt operator*(const int first, const StatisticInt &second) {
    statistic.IncreaseNumberOfPlus();
    return StatisticInt(first * second.number_);
  }

  // /
  StatisticInt operator/(const StatisticInt &other) {
    statistic.IncreaseNumberOfPlus();
    return StatisticInt(number_ / other.number_);
  }

  StatisticInt operator/(const int other) {
    statistic.IncreaseNumberOfPlus();
    return StatisticInt(number_ / other);
  }

  friend StatisticInt operator/(const int first, const StatisticInt &second) {
    statistic.IncreaseNumberOfPlus();
    return StatisticInt(first / second.number_);
  }

  // %
  StatisticInt operator%(const StatisticInt &other) {
    statistic.IncreaseNumberOfPlus();
    return StatisticInt(number_ % other.number_);
  }

  StatisticInt operator%(const int other) {
    statistic.IncreaseNumberOfPlus();
    return StatisticInt(number_ % other);
  }

  friend StatisticInt operator%(const int first, const StatisticInt &second) {
    statistic.IncreaseNumberOfPlus();
    return StatisticInt(first % second.number_);
  }

  // ==
  bool operator==(const StatisticInt &other) {
    statistic.IncreaseNumberOfCompare();
    return number_ == other.number_;
  }

  bool operator==(const int other) {
    statistic.IncreaseNumberOfCompare();
    return number_ == other;
  }

  friend bool operator==(const int first, const StatisticInt &second) {
    statistic.IncreaseNumberOfCompare();
    return first == second.number_;
  }

  // <
  bool operator<(const StatisticInt &other) {
    statistic.IncreaseNumberOfCompare();
    return number_ < other.number_;
  }

  bool operator<(const int other) {
    statistic.IncreaseNumberOfCompare();
    return number_ < other;
  }

  friend bool operator<(const int first, const StatisticInt &second) {
    statistic.IncreaseNumberOfCompare();
    return first < second.number_;
  }

  // >
  bool operator>(const StatisticInt &other) {
    statistic.IncreaseNumberOfCompare();
    return number_ > other.number_;
  }

  bool operator>(const int other) {
    statistic.IncreaseNumberOfCompare();
    return number_ > other;
  }

  friend bool operator>(const int first, const StatisticInt &second) {
    statistic.IncreaseNumberOfCompare();
    return first > second.number_;
  }

  // <=
  bool operator<=(const StatisticInt &other) {
    statistic.IncreaseNumberOfCompare();
    return number_ <= other.number_;
  }

  bool operator<=(const int other) {
    statistic.IncreaseNumberOfCompare();
    return number_ <= other;
  }

  friend bool operator<=(const int first, const StatisticInt &second) {
    statistic.IncreaseNumberOfCompare();
    return first <= second.number_;
  }

  // >=
  bool operator>=(const int other) {
    statistic.IncreaseNumberOfCompare();
    return number_ >= other;
  }

  bool operator>=(const StatisticInt &other) {
    statistic.IncreaseNumberOfCompare();
    return number_ >= other.number_;
  }

  friend bool operator>=(const int first, const StatisticInt &second) {
    statistic.IncreaseNumberOfCompare();
    return first >= second.number_;
  }

  operator int() {
    return number_;
  }

  ~StatisticInt() {
    statistic.IncreaseNumberOfDestructor();
  };

  static Statistic& GetStatistic() { return statistic; }

 private:
  int number_;
  static Statistic statistic;
};

Statistic StatisticInt::statistic;

#endif // STATISTICINT_STATISTICINT_H


//TODO:
//