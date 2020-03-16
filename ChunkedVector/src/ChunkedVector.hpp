//
// Created by 2ToThe10th on 16.02.2020.
//

#ifndef CHUNKEDVECTOR__CHUNKEDVECTOR_HPP_
#define CHUNKEDVECTOR__CHUNKEDVECTOR_HPP_

#include <cassert>
#include <cstdlib>
#include <type_traits>

#ifndef NDEBUG
#include <cstdint>
#include <string>
#endif

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
  inline T *AllocateNewChunk() const;

  inline void FreeChunk(T *chunk_pointer) const;

  inline void FreeChunk(void *chunk_pointer) const;

  inline size_t NumberOfNeededBlocks(size_t size) const;

  inline T *AtPointer(size_t index);

  inline void IncreaseSizeTo(size_t new_size, T common_value);

  inline void IncreaseSizeTo(size_t new_size);

  inline void IncreaseSizeToWithoutImplement(size_t new_size);

  inline void DecreaseSizeTo(size_t new_size);

private:
  ChunkedVector<void *, allocate_memory_for_one_time>
      *pointer_on_chunked_vector_ = nullptr;
  T *pointer_on_small_array_ = nullptr;
  size_t size_ = 0;

#ifndef NDEBUG
public:
  bool CheckVectorAndWriteDump() const;

  bool Ok() const; // return true if struct is Ok

  std::string GetDump(size_t level = 0) const;

private:
  void CheckServiceVector(
      ChunkedVector<void *, allocate_memory_for_one_time> *chunked_vector,
      std::string &dump, std::string &tabs, size_t level) const;

  void CheckServiceVectorChunk(
      ChunkedVector<void *, allocate_memory_for_one_time> *chunked_vector,
      std::string &dump, std::string &tabs) const;

  bool CheckServiceVectorSize(
      ChunkedVector<void *, allocate_memory_for_one_time> *chunked_vector,
      std::string &dump, std::string &tabs) const;

  bool CheckChunk(T *chunk_pointer) const; // return true if canary is Ok

  bool CheckChunk(void *chunk_pointer) const; // return true if canary is Ok

  std::string GetDumpChunk(void *chunk_pointer) const;

  std::string GetDumpChunk(T *chunk_pointer) const;

  inline uint64_t GetCanary(char *memory) const;
#endif
};

#include "ChunkedVector.cpp"

#endif // CHUNKEDVECTOR__CHUNKEDVECTOR_HPP_
