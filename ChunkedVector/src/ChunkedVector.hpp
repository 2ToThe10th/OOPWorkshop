//
// Created by 2ToThe10th on 16.02.2020.
//

#ifndef CHUNKEDVECTOR__CHUNKEDVECTOR_HPP_
#define CHUNKEDVECTOR__CHUNKEDVECTOR_HPP_

#include <cassert>
#include <cstdlib>
#include <type_traits>

template <typename T, size_t allocate_memory_for_one_time, class Enable = void>
class ChunkedVector;

template <typename T, size_t allocate_memory_for_one_time>
class ChunkedVector<
    T, allocate_memory_for_one_time,
    typename std::enable_if_t<1 < allocate_memory_for_one_time>> {
public:
  ChunkedVector() = default;

  explicit ChunkedVector(size_t new_size);

  explicit ChunkedVector(size_t new_size, T common_value);

  explicit ChunkedVector(
      const ChunkedVector<T, allocate_memory_for_one_time> &other);

  explicit ChunkedVector(
      ChunkedVector<T, allocate_memory_for_one_time> &&other);

  inline void Resize(size_t new_size, T common_value);

  inline void Resize(size_t new_size);

  inline T &At(size_t index);

  inline const T &ConstAt(size_t index) const;

  inline T &operator[](size_t index);

  inline const T &operator[](size_t index) const;

  inline size_t Size() const;

  void Reset();

  ~ChunkedVector();

  inline ChunkedVector &operator=(const ChunkedVector &other) noexcept;

  inline ChunkedVector &operator=(ChunkedVector &&other) noexcept;

  inline T &Front();

  inline const T &Front() const;

  inline T &Back();

  inline const T &Back() const;

  inline bool Empty();

  inline void PushBack(const T &new_object);

  template <typename... Args> inline void EmplaceBack(Args &&... args);

  inline void PopBack();

  inline void Swap(ChunkedVector &other);

private:
  ChunkedVector<void *, allocate_memory_for_one_time>
      *pointer_on_chunked_vector_ = nullptr;
  T *pointer_on_small_array_ = nullptr;
  size_t size_ = 0;

  inline size_t NumberOfNeededBlocks(size_t size);

  inline T *AtPointer(size_t index);

  inline void IncreaseSizeTo(size_t new_size, T common_value);

  inline void IncreaseSizeTo(size_t new_size);

  inline void IncreaseSizeToWithoutImplement(size_t new_size);

  inline void DecreaseSizeTo(size_t new_size);
};

#include "ChunkedVector.cpp"

#endif // CHUNKEDVECTOR__CHUNKEDVECTOR_HPP_
