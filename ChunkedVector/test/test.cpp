#include <gtest/gtest.h>
#include "../src/ChunkedVector.hpp"
#include <vector>
#include <random>
#include <unistd.h>
#include <sys/resource.h>
#include <../../StatisticInt/StatisticInt.h>

TEST(ChunkedVector, Place) {

}

TEST(ChunkedVector, ResizeIncrease) {
  ChunkedVector<int, 4> vec(3);
  ASSERT_EQ(vec.Size(), 3);
  for (int i = 0; i < 3; ++i) {
    vec[i] = i * 100 + 4;
  }
  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 4);
  }
  vec.Resize(10);
  ASSERT_EQ(vec.Size(), 10);
  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 4);
  }
  for (int i = 0; i < 10; ++i) {
    vec[i] = i * 100 + 5;
  }
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 5);
  }
  vec.Resize(20);
  ASSERT_EQ(vec.Size(), 20);
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 5);
  }
  for (int i = 0; i < 20; ++i) {
    vec[i] = i * 100 + 7;
  }
  for (int i = 0; i < 20; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 7);
  }
}

TEST(ChunkedVector, ResizeIncreaseOnString) {
  ChunkedVector<std::string, 3> vec(4);
  ASSERT_EQ(vec.Size(), 4);
  for (int i = 0; i < 4; ++i) {
    ASSERT_EQ(vec[i], "");
  }
  vec.Resize(10);
  ASSERT_EQ(vec.Size(), 10);
  for (int i = 0; i < 4; ++i) {
    ASSERT_EQ(vec[i], "");
  }
  for (int i = 0; i < 10; ++i) {
    vec[i] = "aabbcc";
  }
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(vec[i], "aabbcc");
  }
}

TEST(ChunkedVector, ResizeDecrease) {
  ChunkedVector<int, 4> vec(25);
  ASSERT_EQ(vec.Size(), 25);
  for (int i = 0; i < 25; ++i) {
    vec[i] = i * 100 + 4;
  }
  for (int i = 0; i < 25; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 4);
  }
  vec.Resize(10);
  ASSERT_EQ(vec.Size(), 10);
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 4);
  }
  for (int i = 0; i < 10; ++i) {
    vec[i] = i * 100 + 5;
  }
  for (int i = 0; i < 10; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 5);
  }
  vec.Resize(3);
  ASSERT_EQ(vec.Size(), 3);
  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 5);
  }
  for (int i = 0; i < 3; ++i) {
    vec[i] = i * 100 + 7;
  }
  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 7);
  }
  vec.Resize(0);
  ASSERT_EQ(vec.Size(), 0);
}

TEST(ChunkedVector, ResizeDecreaseAndIncrease) {
  ChunkedVector<int, 4> vec(25);
  ASSERT_EQ(vec.Size(), 25);
  for (int i = 0; i < 25; ++i) {
    vec[i] = i * 100 + 4;
  }
  for (int i = 0; i < 25; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 4);
  }
  vec.Resize(30);
  ASSERT_EQ(vec.Size(), 30);
  for (int i = 0; i < 25; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 4);
  }
  for (int i = 0; i < 30; ++i) {
    vec[i] = i * 100 + 5;
  }
  for (int i = 0; i < 30; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 5);
  }
  vec.PushBack(3005);
  ASSERT_EQ(vec.Size(), 31);
  for (int i = 0; i < 31; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 5);
  }
  vec.PopBack();
  ASSERT_EQ(vec.Size(), 30);
  for (int i = 0; i < 30; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 5);
  }
  vec.PopBack();
  ASSERT_EQ(vec.Size(), 29);
  for (int i = 0; i < 29; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 5);
  }
  vec.Resize(3);
  ASSERT_EQ(vec.Size(), 3);
  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 5);
  }
  for (int i = 0; i < 3; ++i) {
    vec[i] = i * 100 + 7;
  }
  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 7);
  }
  vec.EmplaceBack(307);
  ASSERT_EQ(vec.Size(), 4);
  for (int i = 0; i < 4; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 7);
  }
  vec.PopBack();
  ASSERT_EQ(vec.Size(), 3);
  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(vec[i], i * 100 + 7);
  }
  vec.Resize(0);
  ASSERT_EQ(vec.Size(), 0);
}

template<typename T>
void CheckAll(std::vector<T> &vector_from_std, ChunkedVector<T, 20> &chunked_vector) {
  ASSERT_EQ(vector_from_std.size(), chunked_vector.Size());
  ASSERT_EQ(vector_from_std.empty(), chunked_vector.Empty());
//  std::cout << vector_from_std.size() << "\n";
//  for (size_t i = 0; i < vector_from_std.size(); ++i) {
//    std::cout << vector_from_std[i] << "  " << chunked_vector[i] << '\n';
//  }
//  std::cout << "END" << std::endl;
  for (size_t i = 0; i < vector_from_std.size(); ++i) {
    ASSERT_EQ(vector_from_std[i], chunked_vector[i]);
  }
  if (vector_from_std.size() > 0) {
    ASSERT_EQ(vector_from_std.front(), chunked_vector.Front());
    ASSERT_EQ(vector_from_std.back(), chunked_vector.Back());
  }
}

const int MAX_FOR_RANDOM = 1e5;

TEST(ChunkedVector, AllOnInt) {
  for (int time = 0; time < 10; ++time) {
    std::random_device device;
    std::mt19937 random_generator(device());
    std::uniform_int_distribution<int> range(0, MAX_FOR_RANDOM);
    int size = range(random_generator);
    std::vector<int> vector_from_std(size, 0);
    ChunkedVector<int, 20> chunked_vector(size, 0);
    CheckAll(vector_from_std, chunked_vector);
    for (int indexOfResize = 0; indexOfResize < 10; ++indexOfResize) {
      size = range(random_generator);
      vector_from_std.resize(size);
      chunked_vector.Resize(size, 0);
      CheckAll(vector_from_std, chunked_vector);
      for (int i = 0; i < size; ++i) {
        int random_number = range(random_generator);
        vector_from_std[i] = random_number;
        chunked_vector[i] = random_number;
      }
      CheckAll(vector_from_std, chunked_vector);
      int number_of_push_back = range(random_generator);
      for (int i = 0; i < number_of_push_back; ++i) {
        int random_number = range(random_generator);
        vector_from_std.push_back(random_number);
        chunked_vector.PushBack(random_number);
      }
      CheckAll(vector_from_std, chunked_vector);
      int number_of_emplace_back = range(random_generator);
      for (int i = 0; i < number_of_emplace_back; ++i) {
        int random_number = range(random_generator);
        vector_from_std.emplace_back(random_number);
        chunked_vector.EmplaceBack(random_number);
      }
      CheckAll(vector_from_std, chunked_vector);
      int number_of_pop_back = std::min<int>(vector_from_std.size(), 4 * range(random_generator));
      for (int i = 0; i < number_of_pop_back; ++i) {
        vector_from_std.pop_back();
        chunked_vector.PopBack();
      }
      CheckAll(vector_from_std, chunked_vector);
    }
  }
}

TEST(ChunkedVector, AllOnString) {
  for (int time = 0; time < 10; ++time) {
    std::random_device device;
    std::mt19937 random_generator(device());
    std::uniform_int_distribution<int> range(0, MAX_FOR_RANDOM);
    int size = range(random_generator);
    std::vector<std::string> vector_from_std(size);
    ChunkedVector<std::string, 20> chunked_vector(size);
    CheckAll(vector_from_std, chunked_vector);
    for (int indexOfResize = 0; indexOfResize < 10; ++indexOfResize) {
      size = range(random_generator);
      vector_from_std.resize(size);
      chunked_vector.Resize(size, "");
      CheckAll(vector_from_std, chunked_vector);
      for (int i = 0; i < size; ++i) {
        vector_from_std[i] = "abcfr";
        chunked_vector[i] = "abcfr";
      }
      CheckAll(vector_from_std, chunked_vector);
      int number_of_push_back = range(random_generator);
      for (int i = 0; i < number_of_push_back; ++i) {
        vector_from_std.push_back("ggerggv");
        chunked_vector.PushBack("ggerggv");
      }
      CheckAll(vector_from_std, chunked_vector);
      int number_of_emplace_back = range(random_generator);
      for (int i = 0; i < number_of_emplace_back; ++i) {
        vector_from_std.emplace_back("trev vc ");
        chunked_vector.EmplaceBack("trev vc ");
      }
      CheckAll(vector_from_std, chunked_vector);
      int number_of_pop_back = std::min<int>(vector_from_std.size(), 4 * range(random_generator));
      for (int i = 0; i < number_of_pop_back; ++i) {
        vector_from_std.pop_back();
        chunked_vector.PopBack();
      }
      CheckAll(vector_from_std, chunked_vector);
    }
  }
}

TEST(STDVector, AllOnIntSpeedTest) {
  struct rusage rusage;
  getrusage(RUSAGE_SELF, &rusage);

  for (int time = 0; time < 10; ++time) {
    std::mt19937 random_generator(1111);
    std::uniform_int_distribution<int> range(0, MAX_FOR_RANDOM);
    int size = range(random_generator);
    std::vector<int> vector_from_std(size, 0);
    for (int indexOfResize = 0; indexOfResize < 10; ++indexOfResize) {
      size = range(random_generator);
      vector_from_std.resize(size);
      for (int i = 0; i < size; ++i) {
        int random_number = range(random_generator);
        vector_from_std[i] = random_number;
      }
      int number_of_push_back = range(random_generator);
      for (int i = 0; i < number_of_push_back; ++i) {
        int random_number = range(random_generator);
        vector_from_std.push_back(random_number);
      }
      int number_of_emplace_back = range(random_generator);
      for (int i = 0; i < number_of_emplace_back; ++i) {
        int random_number = range(random_generator);
        vector_from_std.emplace_back(random_number);
      }
      int number_of_pop_back = std::min<int>(vector_from_std.size(), 4 * range(random_generator));
      for (int i = 0; i < number_of_pop_back; ++i) {
        vector_from_std.pop_back();
      }
    }
  }

  long long time_start = rusage.ru_utime.tv_sec * (long long)1e6 + rusage.ru_utime.tv_usec;
  getrusage(RUSAGE_SELF, &rusage);
  std::cout << "std::vector: " <<  rusage.ru_utime.tv_sec * (long long)1e6 + rusage.ru_utime.tv_usec  - time_start << std::endl;
}

TEST(ChunkedVector, AllOnIntSpeedTest) {
  struct rusage rusage;
  getrusage(RUSAGE_SELF, &rusage);

  for (int time = 0; time < 10; ++time) {
    std::mt19937 random_generator(1111);
    std::uniform_int_distribution<int> range(0, MAX_FOR_RANDOM);
    int size = range(random_generator);
    ChunkedVector<int, 1000> chunked_vector(size, 0);
    for (int indexOfResize = 0; indexOfResize < 10; ++indexOfResize) {
      size = range(random_generator);
      chunked_vector.Resize(size, 0);
      for (int i = 0; i < size; ++i) {
        int random_number = range(random_generator);
        chunked_vector[i] = random_number;
      }
      int number_of_push_back = range(random_generator);
      for (int i = 0; i < number_of_push_back; ++i) {
        int random_number = range(random_generator);
        chunked_vector.PushBack(random_number);
      }
      int number_of_emplace_back = range(random_generator);
      for (int i = 0; i < number_of_emplace_back; ++i) {
        int random_number = range(random_generator);
        chunked_vector.EmplaceBack(random_number);
      }
      int number_of_pop_back = std::min<int>(chunked_vector.Size(), 4 * range(random_generator));
      for (int i = 0; i < number_of_pop_back; ++i) {
        chunked_vector.PopBack();
      }
    }
  }

  long long time_start = rusage.ru_utime.tv_sec * (long long)1e6 + rusage.ru_utime.tv_usec;
  getrusage(RUSAGE_SELF, &rusage);
  std::cout << "ChunkedVector: " <<  rusage.ru_utime.tv_sec * (long long)1e6 + rusage.ru_utime.tv_usec  - time_start << std::endl;
}