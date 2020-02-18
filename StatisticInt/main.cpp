#include <iostream>
#include <algorithm>
#include "algorithm.cpp"

Statistic StatisticInt::statistic;

int32_t main() {

  BinomialExponentiation(5, 6);
  std::cout << "BinomialExponentiation(5, 6)\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  StupidExponentiation(5, 6);
  std::cout << "StupidExponentiation(5, 6)\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  BinomialExponentiation(3, 8);
  std::cout << "BinomialExponentiation(3, 8)\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  StupidExponentiation(3, 8);
  std::cout << "StupidExponentiation(3, 8)\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  BinomialExponentiation(3, 16);
  std::cout << "BinomialExponentiation(3, 16)\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  StupidExponentiation(3, 16);
  std::cout << "StupidExponentiation(3, 16)\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  BinomialExponentiation(1, 25);
  std::cout << "BinomialExponentiation(1, 25)\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  StupidExponentiation(1, 25);
  std::cout << "StupidExponentiation(1, 25)\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  BinomialExponentiation(1, 32);
  std::cout << "BinomialExponentiation(1, 32)\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  StupidExponentiation(1, 32);
  std::cout << "StupidExponentiation(1, 32)\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  BinomialExponentiation(1, 234532);
  std::cout << "BinomialExponentiation(1, 234532)\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  StupidExponentiation(1, 234532);
  std::cout << "StupidExponentiation(1, 234532)\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  FindEulerFunction(32);
  std::cout << "FindEulerFunction(32)\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  FindEulerFunction(1342);
  std::cout << "FindEulerFunction(1342)\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  FindEulerFunction(144432);
  std::cout << "FindEulerFunction(144432)\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  GCD(5, 17385);
  std::cout << "GCD(5, 17385);\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  GCD(34658324, 172345385);
  std::cout << "GCD(34658324, 172345385);\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  GCD(56785345, 23452345);
  std::cout << "GCD(56785345, 23452345);\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  int array1[7] = {6,4,3,5,2,1,8};
  BubbleSort(array1, 7);
  std::cout << "BubbleSort(7);\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  std::vector<int> vec_array1 = {6,4,3,5,2,1,8};
  BubbleSortVector(vec_array1);
  std::cout << "BubbleSortVector(7);\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  int array2[256];
  for (int i = 0; i < 256; ++i) {
    array2[i] = rand();
  }
  BubbleSort(array2, 256);
  std::cout << "BubbleSort(256);\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  std::vector<int> vec_array2(256);
  for (int i = 0; i < 256; ++i) {
    vec_array2[i] = rand();
  }
  BubbleSortVector(vec_array2);
  std::cout << "BubbleSortVector(256);\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  std::sort(vec_array2.begin(), vec_array2.end());
  std::cout << "std::sort(256);\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  int array3[11256];
  for (int i = 0; i < 11256; ++i) {
    array2[i] = rand();
  }
  BubbleSort(array3, 11256);
  std::cout << "BubbleSort(11256);\n";
  StatisticInt::GetStatistic().PrintStatistic(std::cout);
  StatisticInt::GetStatistic().MakeEmpty();

  int a = 'a';
  std::cout << a << '\n' << char(a) << '\n' << double(a) << std::endl;

  return 0;
}
