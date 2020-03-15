//
// Created by 2ToThe10th on 15.03.2020.
//

#ifndef CHUNKEDVECTOR__CHUNKEDVECTOR_CPP_
#define CHUNKEDVECTOR__CHUNKEDVECTOR_CPP_

#include "ChunkedVector.hpp"

template <typename T, size_t allocate_memory_for_one_time>
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>>::
    ChunkedVector(size_t new_size) {
  Resize(new_size);
}

template <typename T, size_t allocate_memory_for_one_time>
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>>::
    ChunkedVector(size_t new_size, T common_value) {
  Resize(new_size, common_value);
}

template <typename T, size_t allocate_memory_for_one_time>
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>>::
    ChunkedVector(const ChunkedVector<T, allocate_memory_for_one_time> &other) {
  IncreaseSizeToWithoutImplement(other.size_);
  for (size_t i = 0; i < other.size_; ++i) {
    new (AtPointer(i)) T(other[i]);
  }
}

template <typename T, size_t allocate_memory_for_one_time>
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>>::
    ChunkedVector(ChunkedVector<T, allocate_memory_for_one_time> &&other) {
  pointer_on_small_array_ = other.pointer_on_small_array_;
  other.pointer_on_small_array_ = nullptr;
  pointer_on_chunked_vector_ = other.pointer_on_chunked_vector_;
  other.pointer_on_chunked_vector_ = nullptr;
  size_ = other.size_;
  other.size_ = 0;
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    Resize(size_t new_size, T common_value) {
  if (new_size > size_) {
    IncreaseSizeTo(new_size, common_value);
  } else {
    DecreaseSizeTo(new_size);
  }
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    Resize(size_t new_size) {
  if (new_size > size_) {
    IncreaseSizeTo(new_size);
  } else {
    DecreaseSizeTo(new_size);
  }
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
  for (size_t i = 0; i < size_; ++i) {
    At(i).~T();
  }

  if (pointer_on_chunked_vector_ != nullptr) {
    size_t current_number_of_blocks = pointer_on_chunked_vector_->Size();
    for (size_t i = 0; i < current_number_of_blocks; ++i) {
      delete[](char *) pointer_on_chunked_vector_->At(i);
    }
    delete pointer_on_chunked_vector_;
    pointer_on_chunked_vector_ = nullptr;
  } else if (pointer_on_small_array_ != nullptr) {
    delete[](char *) pointer_on_small_array_;
    pointer_on_small_array_ = nullptr;
  }
  size_ = 0;
}

template <typename T, size_t allocate_memory_for_one_time>
ChunkedVector<
    T, allocate_memory_for_one_time,
    std::enable_if_t<1 < allocate_memory_for_one_time>>::~ChunkedVector() {
  Reset();
}

template <typename T, size_t allocate_memory_for_one_time>
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>> &
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>>::
operator=(const ChunkedVector &other) noexcept {
  Reset();
  IncreaseSizeToWithoutImplement(other.Size());
  for (size_t i = 0; i < size_; ++i) {
    new (AtPointer(i)) T(other.ConstAt(i));
  }
  return *this;
}

template <typename T, size_t allocate_memory_for_one_time>
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>> &
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>>::
operator=(ChunkedVector &&other) noexcept {
  Reset();
  pointer_on_chunked_vector_ = other.pointer_on_chunked_vector_;
  other.pointer_on_chunked_vector_ = nullptr;
  pointer_on_small_array_ = other.pointer_on_small_array_;
  other.pointer_on_small_array_ = nullptr;
  size_ = other.size_;
  other.size_ = 0;
  return *this;
}

template <typename T, size_t allocate_memory_for_one_time>
T &ChunkedVector<T, allocate_memory_for_one_time,
                 std::enable_if_t<1 < allocate_memory_for_one_time>>::Front() {
  assert(size_);
  return At(0);
}

template <typename T, size_t allocate_memory_for_one_time>
const T &
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>>::Front()
    const {
  assert(size_);
  return ConstAt(0);
}

template <typename T, size_t allocate_memory_for_one_time>
T &ChunkedVector<T, allocate_memory_for_one_time,
                 std::enable_if_t<1 < allocate_memory_for_one_time>>::Back() {

  assert(size_);
  return At(size_ - 1);
}

template <typename T, size_t allocate_memory_for_one_time>
const T &
ChunkedVector<T, allocate_memory_for_one_time,
              std::enable_if_t<1 < allocate_memory_for_one_time>>::Back()
    const {
  assert(size_);
  return ConstAt(size_ - 1);
}

template <typename T, size_t allocate_memory_for_one_time>
bool ChunkedVector<
    T, allocate_memory_for_one_time,
    std::enable_if_t<1 < allocate_memory_for_one_time>>::Empty() {
  return !size_;
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    PushBack(const T &new_object) {
  IncreaseSizeToWithoutImplement(size_ + 1);
  new (AtPointer(size_ - 1)) T(new_object);
}

template <typename T, size_t allocate_memory_for_one_time>
template <typename... Args>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    EmplaceBack(Args &&... args) {
  IncreaseSizeToWithoutImplement(size_ + 1);
  new (AtPointer(size_ - 1)) T(args...);
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<
    T, allocate_memory_for_one_time,
    std::enable_if_t<1 < allocate_memory_for_one_time>>::PopBack() {
  assert(size_ > 0);
  DecreaseSizeTo(size_ - 1);
}

template <typename T, size_t allocate_memory_for_one_time>
void ChunkedVector<T, allocate_memory_for_one_time,
                   std::enable_if_t<1 < allocate_memory_for_one_time>>::
    Swap(ChunkedVector &other) {
  std::swap(size_, other.size_);
  std::swap(pointer_on_small_array_, other.pointer_on_small_array_);
  std::swap(pointer_on_chunked_vector_, other.pointer_on_chunked_vector_);
}

template <typename T, size_t allocate_memory_for_one_time>
size_t ChunkedVector<T, allocate_memory_for_one_time,
                     std::enable_if_t<1 < allocate_memory_for_one_time>>::
    NumberOfNeededBlocks(size_t size) {
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
        pointer_on_chunked_vector_->At(0) =
            (T *)new char[sizeof(T) * allocate_memory_for_one_time];
      } else {
        pointer_on_chunked_vector_->At(0) = pointer_on_small_array_;
        pointer_on_small_array_ = nullptr;
      }
      for (size_t i = 1; i < number_of_needed_blocks; ++i) {
        pointer_on_chunked_vector_->At(i) =
            (T *)new char[sizeof(T) * allocate_memory_for_one_time];
      }
    } else {
      if (pointer_on_small_array_ == nullptr) {
        pointer_on_small_array_ =
            (T *)new char[sizeof(T) * allocate_memory_for_one_time];
      }
    }
  } else {
    size_t number_of_needed_blocks = NumberOfNeededBlocks(new_size);
    size_t start_number_of_blocks = pointer_on_chunked_vector_->Size();
    if (start_number_of_blocks < number_of_needed_blocks) {
      pointer_on_chunked_vector_->Resize(number_of_needed_blocks);
    }
    for (size_t i = start_number_of_blocks; i < number_of_needed_blocks; ++i) {
      pointer_on_chunked_vector_->At(i) =
          (T *)new char[sizeof(T) * allocate_memory_for_one_time];
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
      delete[](char *) pointer_on_chunked_vector_->At(i);
    }
    if (number_of_needed_blocks < current_number_of_blocks) {
      pointer_on_chunked_vector_->Resize(number_of_needed_blocks);
    }
  }

  size_ = new_size;
}

#endif // CHUNKEDVECTOR__CHUNKEDVECTOR_CPP_