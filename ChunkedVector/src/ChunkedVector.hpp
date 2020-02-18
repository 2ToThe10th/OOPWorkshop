//
// Created by 2ToThe10th on 16.02.2020.
//
#include <cstdlib>
#include <cassert>

#ifndef CHUNKEDVECTOR__CHUNKEDVECTOR_H_
#define CHUNKEDVECTOR__CHUNKEDVECTOR_H_

template<typename T, size_t allocate_memory_for_one_time, class Enable = void>
class ChunkedVector;

template<typename T, size_t allocate_memory_for_one_time>
class ChunkedVector<T, allocate_memory_for_one_time, typename std::enable_if_t<1 < allocate_memory_for_one_time> > {
 public:
  ChunkedVector() = default;

  explicit ChunkedVector(size_t new_size) {
    Resize(new_size);
  }

  explicit ChunkedVector(size_t new_size, T common_value) {
    Resize(new_size);
    for (size_t i = 0; i < new_size; ++i) {
      At(i) = common_value;
    }
  }

  inline void Resize(size_t new_size, T common_value) {
    if (new_size > size_) {
      IncreaseSizeTo(new_size, common_value);
    } else {
      DecreaseSizeTo(new_size);
    }
  }

  inline void Resize(size_t new_size) {
    if (new_size > size_) {
      IncreaseSizeTo(new_size);
    } else {
      DecreaseSizeTo(new_size);
    }
  }

  inline T &At(size_t index) {
    assert(index >= 0);
    assert(index < size_);
    if (pointer_on_chunked_vector_ == nullptr) {
      return pointer_on_small_array_[index];
    } else {
      return ((T *) (pointer_on_chunked_vector_->At(index / allocate_memory_for_one_time)))[index
        % allocate_memory_for_one_time];
    }
  }

  inline T &operator[](size_t index) {
    return At(index);
  }

  inline size_t Size() const {
    return size_;
  }

  ~ChunkedVector() {
    if (pointer_on_chunked_vector_ != nullptr) {
      for (size_t i = 0; i < pointer_on_chunked_vector_->Size(); ++i) {
        delete[] (T *) pointer_on_chunked_vector_->At(i);
      }
      delete pointer_on_chunked_vector_;
    } else if (pointer_on_small_array_ != nullptr) {
      delete[] pointer_on_small_array_;
    }
  }

  inline ChunkedVector &operator=(ChunkedVector &&other) noexcept {
    pointer_on_chunked_vector_ = other.pointer_on_chunked_vector;
    other.pointer_on_chunked_vector = nullptr;
    pointer_on_small_array_ = other.pointer_on_small_array;
    other.pointer_on_small_array = nullptr;
    size_ = other.size_;
    other.size_ = 0;
  }

  inline T &Front() {
    assert(size_);
    return At(0);
  }

  inline T &Back() {
    assert(size_);
    return At(size_ - 1);
  }

  inline bool Empty() {
    return !size_;
  }

  inline void PushBack(const T &new_object) {
    IncreaseSizeTo(size_ + 1);
    Back() = new_object;
  }

  template<typename... Args>
  inline void EmplaceBack(Args &&... args) {
    IncreaseSizeTo(size_ + 1);
    Back() = T(args...);
  }

  inline void PopBack() {
    assert(size_ > 0);
    DecreaseSizeTo(size_ - 1);
  }

  inline void Swap(ChunkedVector &other) {
    std::swap(size_, other.size_);
    std::swap(pointer_on_small_array_, other.pointer_on_small_array_);
    std::swap(pointer_on_chunked_vector_, other.pointer_on_chunked_vector_);
  }

  inline void Clear() {
    DecreaseSizeTo(0);
  }

 private:
  ChunkedVector<void *, allocate_memory_for_one_time> *pointer_on_chunked_vector_ = nullptr;
  T *pointer_on_small_array_ = nullptr;
  size_t size_ = 0;

  inline size_t NumberOfNeededBlocks(size_t size) {
    if (size == 0) {
      return 0;
    } else {
      return ((size - 1) / allocate_memory_for_one_time) + 1;
    }
  }

  inline void IncreaseSizeTo(size_t new_size, T common_value) {
    size_t old_size = size_;
    IncreaseSizeTo(new_size);
    for (size_t i = old_size; i < new_size; ++i) {
      At(i) = common_value;
    }
  }

  inline void IncreaseSizeTo(size_t new_size) {
    if (pointer_on_chunked_vector_ == nullptr) {
      if (new_size > allocate_memory_for_one_time) {
        size_t number_of_needed_blocks = NumberOfNeededBlocks(new_size);
        pointer_on_chunked_vector_ = new ChunkedVector<void *, allocate_memory_for_one_time>(number_of_needed_blocks);
        if (pointer_on_small_array_ == nullptr) {
          pointer_on_chunked_vector_->At(0) = new T[allocate_memory_for_one_time];
        } else {
          pointer_on_chunked_vector_->At(0) = pointer_on_small_array_;
          pointer_on_small_array_ = nullptr;
        }
        for (size_t i = 1; i < number_of_needed_blocks; ++i) {
          pointer_on_chunked_vector_->At(i) = new T[allocate_memory_for_one_time];
        }
      } else {
        if (pointer_on_small_array_ == nullptr) {
          pointer_on_small_array_ = new T[allocate_memory_for_one_time];
        }
      }
    } else {
      size_t number_of_needed_blocks = NumberOfNeededBlocks(new_size);
      size_t start_number_of_blocks = pointer_on_chunked_vector_->Size();
      if (start_number_of_blocks < number_of_needed_blocks) {
        pointer_on_chunked_vector_->Resize(number_of_needed_blocks);
      }
      for (size_t i = start_number_of_blocks; i < number_of_needed_blocks; ++i) {
        pointer_on_chunked_vector_->At(i) = new T[allocate_memory_for_one_time];
      }
    }

    size_ = new_size;
  }

  inline void DecreaseSizeTo(size_t new_size) {
    if (pointer_on_chunked_vector_ != nullptr) {
      size_t number_of_needed_blocks = NumberOfNeededBlocks(new_size) + 1;
      size_t current_number_of_blocks = pointer_on_chunked_vector_->Size();
      for (size_t i = number_of_needed_blocks; i < current_number_of_blocks; ++i) {
        delete[] (T *) pointer_on_chunked_vector_->At(i);
      }
      if (number_of_needed_blocks < current_number_of_blocks) {
        pointer_on_chunked_vector_->Resize(number_of_needed_blocks);
      }
    }

    size_ = new_size;
  }
};

#endif //CHUNKEDVECTOR__CHUNKEDVECTOR_H_
