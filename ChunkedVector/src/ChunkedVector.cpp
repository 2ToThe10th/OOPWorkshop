//
// Created by 2ToThe10th on 15.03.2020.
//

#ifndef CHUNKEDVECTOR__CHUNKEDVECTOR_CPP_
#define CHUNKEDVECTOR__CHUNKEDVECTOR_CPP_

#include "ChunkedVector.hpp"
#include <cassert>
#ifndef NDEBUG
#include <iostream>
#endif

template <typename T, size_t allocate_memory_for_one_time>
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>>::
    ChunkedVector(size_t new_size) {
  assert(CheckVectorAndWriteDump());
  Resize(new_size);
  assert(CheckVectorAndWriteDump());
}

template <typename T, size_t allocate_memory_for_one_time>
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>>::
    ChunkedVector(size_t new_size, T common_value) {
  assert(CheckVectorAndWriteDump());
  Resize(new_size, common_value);
  assert(CheckVectorAndWriteDump());
}

template <typename T, size_t allocate_memory_for_one_time>
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>>::
    ChunkedVector(const ChunkedVector<T, allocate_memory_for_one_time> &other) {
  assert(CheckVectorAndWriteDump());
  IncreaseSizeToWithoutImplement(other.size_);
  for (size_t i = 0; i < other.size_; ++i) {
    new (AtPointer(i)) T(other[i]);
  }
  assert(CheckVectorAndWriteDump());
}

template <typename T, size_t allocate_memory_for_one_time>
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>>::
    ChunkedVector(ChunkedVector<T, allocate_memory_for_one_time> &&other) {
  assert(CheckVectorAndWriteDump());
  pointer_on_small_array_ = other.pointer_on_small_array_;
  other.pointer_on_small_array_ = nullptr;
  pointer_on_chunked_vector_ = other.pointer_on_chunked_vector_;
  other.pointer_on_chunked_vector_ = nullptr;
  size_ = other.size_;
  other.size_ = 0;
  assert(CheckVectorAndWriteDump());
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    Resize(size_t new_size, T common_value) {
  assert(CheckVectorAndWriteDump());
  if (new_size > size_) {
    IncreaseSizeTo(new_size, common_value);
  } else {
    DecreaseSizeTo(new_size);
  }
  assert(CheckVectorAndWriteDump());
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    Resize(size_t new_size) {
  assert(CheckVectorAndWriteDump());
  if (new_size > size_) {
    IncreaseSizeTo(new_size);
  } else {
    DecreaseSizeTo(new_size);
  }
  assert(CheckVectorAndWriteDump());
}

template <typename T, size_t allocate_memory_for_one_time>
T &ChunkedVector<
    T, allocate_memory_for_one_time,
    std::enable_if_t<1 < allocate_memory_for_one_time>>::At(size_t index) {
  assert(index >= 0);
  assert(index < size_);
  if (pointer_on_chunked_vector_ == nullptr) {
    return pointer_on_small_array_[index];
  } else {
    return ((T *)(pointer_on_chunked_vector_->At(
        index /
        allocate_memory_for_one_time)))[index % allocate_memory_for_one_time];
  }
}

template <typename T, size_t allocate_memory_for_one_time>
const T &ChunkedVector<T, allocate_memory_for_one_time,
                       std::enable_if_t<1 < allocate_memory_for_one_time>>::
    ConstAt(size_t index) const {
  assert(index >= 0);
  assert(index < size_);
  if (pointer_on_chunked_vector_ == nullptr) {
    return pointer_on_small_array_[index];
  } else {
    return ((T *)(pointer_on_chunked_vector_->At(
        index /
        allocate_memory_for_one_time)))[index % allocate_memory_for_one_time];
  }
}

template <typename T, size_t allocate_memory_for_one_time>
T &ChunkedVector<T, allocate_memory_for_one_time,
                 std::enable_if_t<1 < allocate_memory_for_one_time>>::
operator[](size_t index) {
  return At(index);
}

template <typename T, size_t allocate_memory_for_one_time>
const T &ChunkedVector<T, allocate_memory_for_one_time,
                       std::enable_if_t<1 < allocate_memory_for_one_time>>::
operator[](size_t index) const {
  return ConstAt(index);
}

template <typename T, size_t allocate_memory_for_one_time>
size_t ChunkedVector<T, allocate_memory_for_one_time,
                     std::enable_if_t<1 < allocate_memory_for_one_time>>::Size()
    const {
  return size_;
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<
    T, allocate_memory_for_one_time,
    std::enable_if_t<1 < allocate_memory_for_one_time>>::Reset() {
  assert(CheckVectorAndWriteDump());
  for (size_t i = 0; i < size_; ++i) {
    At(i).~T();
  }

  if (pointer_on_chunked_vector_ != nullptr) {
    size_t current_number_of_blocks = pointer_on_chunked_vector_->Size();
    for (size_t i = 0; i < current_number_of_blocks; ++i) {
      FreeChunk(pointer_on_chunked_vector_->At(i));
    }
    delete pointer_on_chunked_vector_;
    pointer_on_chunked_vector_ = nullptr;
  } else if (pointer_on_small_array_ != nullptr) {
    FreeChunk(pointer_on_small_array_);
    pointer_on_small_array_ = nullptr;
  }
  size_ = 0;
  assert(CheckVectorAndWriteDump());
}

template <typename T, size_t allocate_memory_for_one_time>
ChunkedVector<
    T, allocate_memory_for_one_time,
    std::enable_if_t<1 < allocate_memory_for_one_time>>::~ChunkedVector() {
  assert(CheckVectorAndWriteDump());
  Reset();
}

template <typename T, size_t allocate_memory_for_one_time>
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>> &
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>>::
operator=(const ChunkedVector &other) noexcept {
  assert(CheckVectorAndWriteDump());
  Reset();
  IncreaseSizeToWithoutImplement(other.Size());
  for (size_t i = 0; i < size_; ++i) {
    new (AtPointer(i)) T(other.ConstAt(i));
  }
  assert(CheckVectorAndWriteDump());
  return *this;
}

template <typename T, size_t allocate_memory_for_one_time>
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>> &
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>>::
operator=(ChunkedVector &&other) noexcept {
  assert(CheckVectorAndWriteDump());
  Reset();
  pointer_on_chunked_vector_ = other.pointer_on_chunked_vector_;
  other.pointer_on_chunked_vector_ = nullptr;
  pointer_on_small_array_ = other.pointer_on_small_array_;
  other.pointer_on_small_array_ = nullptr;
  size_ = other.size_;
  other.size_ = 0;
  assert(CheckVectorAndWriteDump());
  return *this;
}

template <typename T, size_t allocate_memory_for_one_time>
T &ChunkedVector<T, allocate_memory_for_one_time,
                 std::enable_if_t<1 < allocate_memory_for_one_time>>::Front() {
  assert(CheckVectorAndWriteDump());
  assert(size_);
  return At(0);
}

template <typename T, size_t allocate_memory_for_one_time>
const T &
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>>::Front()
    const {
  assert(CheckVectorAndWriteDump());
  assert(size_);
  return ConstAt(0);
}

template <typename T, size_t allocate_memory_for_one_time>
T &ChunkedVector<T, allocate_memory_for_one_time,
                 std::enable_if_t<1 < allocate_memory_for_one_time>>::Back() {
  assert(CheckVectorAndWriteDump());
  assert(size_);
  return At(size_ - 1);
}

template <typename T, size_t allocate_memory_for_one_time>
const T &
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>>::Back()
    const {
  assert(CheckVectorAndWriteDump());
  assert(size_);
  return ConstAt(size_ - 1);
}

template <typename T, size_t allocate_memory_for_one_time>
bool ChunkedVector<
    T, allocate_memory_for_one_time,
    std::enable_if_t<1 < allocate_memory_for_one_time>>::Empty() {
  assert(CheckVectorAndWriteDump());
  return !size_;
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    PushBack(const T &new_object) {
  assert(CheckVectorAndWriteDump());
  IncreaseSizeToWithoutImplement(size_ + 1);
  new (AtPointer(size_ - 1)) T(new_object);
}

template <typename T, size_t allocate_memory_for_one_time>
template <typename... Args>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    EmplaceBack(Args &&... args) {
  assert(CheckVectorAndWriteDump());
  IncreaseSizeToWithoutImplement(size_ + 1);
  new (AtPointer(size_ - 1)) T(args...);
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<
    T, allocate_memory_for_one_time,
    std::enable_if_t<1 < allocate_memory_for_one_time>>::PopBack() {
  assert(CheckVectorAndWriteDump());
  assert(size_ > 0);
  DecreaseSizeTo(size_ - 1);
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    Swap(ChunkedVector &other) {
  assert(CheckVectorAndWriteDump());
  std::swap(size_, other.size_);
  std::swap(pointer_on_small_array_, other.pointer_on_small_array_);
  std::swap(pointer_on_chunked_vector_, other.pointer_on_chunked_vector_);
  assert(CheckVectorAndWriteDump());
}

template <typename T, size_t allocate_memory_for_one_time>
T *ChunkedVector<T, allocate_memory_for_one_time,
                 std::enable_if_t<1 < allocate_memory_for_one_time>>::
    AllocateNewChunk() const {
#ifndef NDEBUG
  char *new_chunk =
      new char[sizeof(T) * allocate_memory_for_one_time + 2 * sizeof(uint64_t)];
  *(uint64_t *)new_chunk = GetCanary(new_chunk);
  *(uint64_t *)(new_chunk + sizeof(T) * allocate_memory_for_one_time +
                sizeof(uint64_t)) =
      GetCanary(new_chunk + sizeof(T) * allocate_memory_for_one_time +
                sizeof(uint64_t));
  return (T *)(new_chunk + sizeof(uint64_t));
#endif
  return (T *)new char[sizeof(T) * allocate_memory_for_one_time];
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    FreeChunk(void *chunk_pointer) const {
#ifndef NDEBUG
  delete[]((char *)chunk_pointer - sizeof(uint64_t));
  return;
#endif
  delete[](char *) chunk_pointer;
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    FreeChunk(T *chunk_pointer) const {
  FreeChunk((void *)chunk_pointer);
}

template <typename T, size_t allocate_memory_for_one_time>
size_t ChunkedVector<T, allocate_memory_for_one_time,
                     std::enable_if_t<1 < allocate_memory_for_one_time>>::
    NumberOfNeededBlocks(size_t size) const {
  if (size == 0) {
    return 0;
  } else {
    return ((size - 1) / allocate_memory_for_one_time) + 1;
  }
}

template <typename T, size_t allocate_memory_for_one_time>
T *ChunkedVector<T, allocate_memory_for_one_time,
                 std::enable_if_t<1 < allocate_memory_for_one_time>>::
    AtPointer(size_t index) {
  assert(index >= 0);
  assert(index < size_);
  if (pointer_on_chunked_vector_ == nullptr) {
    return &pointer_on_small_array_[index];
  } else {
    return &((T *)(pointer_on_chunked_vector_->At(
        index /
        allocate_memory_for_one_time)))[index % allocate_memory_for_one_time];
  }
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    IncreaseSizeTo(size_t new_size, T common_value) {
  size_t old_size = size_;
  IncreaseSizeToWithoutImplement(new_size);
  for (size_t i = old_size; i < new_size; ++i) {
    new (AtPointer(i)) T(common_value);
  }
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    IncreaseSizeTo(size_t new_size) {
  size_t old_size = size_;
  IncreaseSizeToWithoutImplement(new_size);
  for (size_t i = old_size; i < new_size; ++i) {
    new (AtPointer(i)) T();
  }
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    IncreaseSizeToWithoutImplement(size_t new_size) {
  if (pointer_on_chunked_vector_ == nullptr) {
    if (new_size > allocate_memory_for_one_time) {
      size_t number_of_needed_blocks = NumberOfNeededBlocks(new_size);
      pointer_on_chunked_vector_ =
          new ChunkedVector<void *, allocate_memory_for_one_time>(
              number_of_needed_blocks);
      if (pointer_on_small_array_ == nullptr) {
        pointer_on_chunked_vector_->At(0) = AllocateNewChunk();
      } else {
        pointer_on_chunked_vector_->At(0) = pointer_on_small_array_;
        pointer_on_small_array_ = nullptr;
      }
      for (size_t i = 1; i < number_of_needed_blocks; ++i) {
        pointer_on_chunked_vector_->At(i) = AllocateNewChunk();
      }
    } else {
      if (pointer_on_small_array_ == nullptr) {
        pointer_on_small_array_ = AllocateNewChunk();
      }
    }
  } else {
    size_t number_of_needed_blocks = NumberOfNeededBlocks(new_size);
    size_t start_number_of_blocks = pointer_on_chunked_vector_->Size();
    if (start_number_of_blocks < number_of_needed_blocks) {
      pointer_on_chunked_vector_->Resize(number_of_needed_blocks);
    }
    for (size_t i = start_number_of_blocks; i < number_of_needed_blocks; ++i) {
      pointer_on_chunked_vector_->At(i) = AllocateNewChunk();
    }
  }
  size_ = new_size;
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    DecreaseSizeTo(size_t new_size) {
  for (size_t i = new_size; i < size_; ++i) {
    At(i).~T();
  }

  if (pointer_on_chunked_vector_ != nullptr) {
    size_t number_of_needed_blocks = NumberOfNeededBlocks(new_size) + 1;
    size_t current_number_of_blocks = pointer_on_chunked_vector_->Size();
    for (size_t i = number_of_needed_blocks; i < current_number_of_blocks;
         ++i) {
      FreeChunk(pointer_on_chunked_vector_->At(i));
    }
    if (number_of_needed_blocks < current_number_of_blocks) {
      pointer_on_chunked_vector_->Resize(number_of_needed_blocks);
    }
  }

  size_ = new_size;
}

#ifndef NDEBUG

template <typename T, size_t allocate_memory_for_one_time>
bool ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    CheckVectorAndWriteDump() const {
  return Ok() || ((std::cout << GetDump() << std::endl && false));
}

template <typename T, size_t allocate_memory_for_one_time>
bool ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::Ok()
    const {
  if (pointer_on_chunked_vector_ != nullptr) {
    if (pointer_on_chunked_vector_->Size() != NumberOfNeededBlocks(size_) &&
        pointer_on_chunked_vector_->Size() != NumberOfNeededBlocks(size_) + 1) {
      return false;
    }
    if (!pointer_on_chunked_vector_->Ok()) {
      return false;
    }
    for (size_t i = 0; i < pointer_on_chunked_vector_->Size(); ++i) {
      if (!CheckChunk(pointer_on_chunked_vector_->At(i))) {
        return false;
      }
      if (i != 0 && pointer_on_chunked_vector_->At(i) ==
                        pointer_on_chunked_vector_->At(i - 1)) {
        return false;
      }
    }
  }
  if (pointer_on_small_array_ != nullptr) {
    if (!CheckChunk(pointer_on_small_array_)) {
      return false;
    }
  }
  return true;
}

template <typename T, size_t allocate_memory_for_one_time>
std::string ChunkedVector<T, allocate_memory_for_one_time,
                          std::enable_if_t<1 < allocate_memory_for_one_time>>::
    GetDump(size_t level) const {
  std::string dump;
  std::string tabs;
  for (size_t i = 0; i < level; ++i) {
    tabs += "\t";
  }
  if (pointer_on_chunked_vector_ != nullptr) {
    CheckServiceVector(pointer_on_chunked_vector_, dump, tabs, level);
  }
  if (pointer_on_small_array_ != nullptr) {
    if (!CheckChunk(pointer_on_small_array_)) {
      dump += tabs;
      dump += "\x1B[31mArray: ";
      dump += GetDumpChunk(pointer_on_small_array_);
      dump += "\033[0m\n";
    }
  }
  return dump;
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    CheckServiceVector(
        ChunkedVector<void *, allocate_memory_for_one_time> *chunked_vector,
        std::string &dump, std::string &tabs, size_t level) const {
  if (CheckServiceVectorSize(chunked_vector, dump, tabs)) {
    return;
  }
  if (!pointer_on_chunked_vector_->Ok()) {
    dump += tabs;
    dump += "Service ChunkedVector:\n";
    dump += pointer_on_chunked_vector_->GetDump(level + 1);
    dump += tabs;
    dump += "End service ChunkedVector\n";
    return;
  }
  CheckServiceVectorChunk(chunked_vector, dump, tabs);
}

template <typename T, size_t allocate_memory_for_one_time>
bool ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
CheckServiceVectorSize(
    ChunkedVector<void *, allocate_memory_for_one_time> *chunked_vector,
    std::string &dump, std::string &tabs) const {
  if (pointer_on_chunked_vector_->Size() < NumberOfNeededBlocks(size_)) {
    dump += tabs;
    dump += "\x1B[31mToo small size of service vector ";
    dump += std::to_string(pointer_on_chunked_vector_->Size());
    dump += " vs ";
    dump += std::to_string(NumberOfNeededBlocks(size_));
    dump += " needed\033[0m\n";
    return true;
  }
  if (pointer_on_chunked_vector_->Size() > NumberOfNeededBlocks(size_) + 1) {
    dump += tabs;
    dump += "\x1B[31mToo big size of service vector ";
    dump += std::to_string(pointer_on_chunked_vector_->Size());
    dump += " vs ";
    dump += std::to_string(NumberOfNeededBlocks(size_));
    dump += " needed\033[0m\n";
    return true;
  }
  return false;
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    CheckServiceVectorChunk(
        ChunkedVector<void *, allocate_memory_for_one_time> *chunked_vector,
        std::string &dump, std::string &tabs) const {
  for (size_t i = 0; i < pointer_on_chunked_vector_->Size(); ++i) {
    if (!CheckChunk(pointer_on_chunked_vector_->At(i))) {
      dump += tabs;
      dump += "\x1B[31mChunk number ";
      dump += std::to_string(i);
      dump += ": ";
      dump += GetDumpChunk(pointer_on_chunked_vector_->At(i));
      dump += "\033[0m\n";
    }
    if (i != 0 && pointer_on_chunked_vector_->At(i) ==
                      pointer_on_chunked_vector_->At(i - 1)) {
      dump += tabs;
      dump += "\x1B[31mEqual ";
      dump += std::to_string(i - 1);
      dump += " and ";
      dump += std::to_string(i);
      dump += " blocks\033[0m\n";
    }
  }
}

template <typename T, size_t allocate_memory_for_one_time>
bool ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    CheckChunk(T *chunk_pointer) const {
  return CheckChunk((void *)chunk_pointer);
}

template <typename T, size_t allocate_memory_for_one_time>
bool ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    CheckChunk(void *chunk_pointer) const {
  char *chunk_char_ptr = (char *)chunk_pointer;
  if ((*(uint64_t *)(chunk_char_ptr - sizeof(uint64_t))) !=
      GetCanary(chunk_char_ptr - sizeof(uint64_t))) {
    return false;
  }
  if (*(uint64_t *)(chunk_char_ptr +
                    allocate_memory_for_one_time * sizeof(T)) !=
      GetCanary(chunk_char_ptr + allocate_memory_for_one_time * sizeof(T))) {
    return false;
  }
  return true;
}

template <typename T, size_t allocate_memory_for_one_time>
std::string ChunkedVector<T, allocate_memory_for_one_time,
                          std::enable_if_t<1 < allocate_memory_for_one_time>>::
    GetDumpChunk(T *chunk_pointer) const {
  return GetDumpChunk((void *)chunk_pointer);
}

template <typename T, size_t allocate_memory_for_one_time>
std::string ChunkedVector<T, allocate_memory_for_one_time,
                          std::enable_if_t<1 < allocate_memory_for_one_time>>::
    GetDumpChunk(void *chunk_pointer) const {
  std::string dump;
  char *chunk_char_ptr = (char *)chunk_pointer;
  bool is_ok = true;
  if ((*(uint64_t *)(chunk_char_ptr - sizeof(uint64_t))) !=
      GetCanary(chunk_char_ptr - sizeof(uint64_t))) {
    dump += "first canary rewritten at ";
    dump += std::to_string((uint64_t)(chunk_char_ptr - sizeof(uint64_t)));
    is_ok = false;
  }
  if (*(uint64_t *)(chunk_char_ptr +
                    allocate_memory_for_one_time * sizeof(T)) !=
      GetCanary(chunk_char_ptr + allocate_memory_for_one_time * sizeof(T))) {
    if (!is_ok) {
      dump += "; ";
    }
    dump += "second canary rewritten at ";
    dump += std::to_string(
        (uint64_t)(chunk_char_ptr + allocate_memory_for_one_time * sizeof(T)));
  }
  return dump;
}

template <typename T, size_t allocate_memory_for_one_time>
uint64_t ChunkedVector<T, allocate_memory_for_one_time,
                       std::enable_if_t<1 < allocate_memory_for_one_time>>::
GetCanary(char *memory) const {
  return reinterpret_cast<uint64_t>(memory);
}

#endif

#endif // CHUNKEDVECTOR__CHUNKEDVECTOR_CPP_