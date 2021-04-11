#pragma once

#include <cstddef>
#include <optional>
#include <stdexcept>  // logic_error

using std::size_t;
// Заголовочный файл с объявлением структуры данных

namespace itis {

  // Tip 1: объявите здесь необходимые структуры, функции, константы и прочее


  // Пример: объявление константы времени компиляции в заголовочном файле
  inline constexpr auto kStringConstant = "Hello, stranger!";

  // Пример: объявление структуры с полями и методами
  template<class T>
  struct circular_buffer {
   private:
    size_t size_{0};
    size_t capacity_{0};
    T *data_{nullptr};

    size_t tail_{0};
    size_t head_{0};

    void incrementHead() {
      head_ = (head_ + 1) % capacity_;
    }

    void incrementTail() {
      tail_ = (tail_ + 1) % capacity_;
    }

    void decrementHead() {
      if (head_ == 0) /* т.к. тип size_t не может принять отриц. значение, проврка такая */{
        head_ = capacity_ - 1;
      } else {
        head_ -= 1;
      }
    }

    void decrementTail() {
      if (tail_ == 0) /* т.к. тип size_t не может принять отриц. значение, проврка такая */{
        tail_ = capacity_ - 1;
      } else {
        tail_ -= 1;
      }
    }

    // Tip 2: На начальном этапе разработки структуры данных можете определения методов задавать в
    // заголовочном файле, как только работа будет завершена, можно будет оставить здесь только объявления.
   public:
    explicit circular_buffer(size_t max_size_) :
            data_(new T[max_size_]), capacity_(max_size_) {}

    void EnqueueBack(T &elem) {
      if (isFull()) {
        incrementHead();
        incrementTail();
        data_[tail_] = elem;
      } else if (isEmpty()) {
        head_ = 0;
        tail_ = 0;
        data_[tail_] = elem;
        size_ += 1;
      } else {
        incrementTail();
        data_[tail_] = elem;
        size_ += 1;
      }
    }

    void EnqueueFront(T &elem) {
      if (isFull()) {
        decrementHead();
        decrementTail();
        data_[head_] = elem;
      } else if (isEmpty()) {
        head_ = 0;
        tail_ = 0;
        data_[head_] = elem;
        size_ += 1;
      } else {
        decrementHead();
        data_[head_] = elem;
        size_ += 1;
      }
    }

    T DequeueBack() {
      if (isEmpty()) {
        throw std::logic_error("cannot dequeue from empty buffer");
      }
      T to_return;
      if (size() == 1) {
        to_return = data_[tail_];
        size_ = 0;
      } else {
        to_return = data_[tail_];
        decrementTail();
        size_ -= 1;
      }

      return to_return;
    }

    T DequeueFront() {
      if (isEmpty()) {
        throw std::logic_error("cannot dequeue from empty buffer");
      }
      T to_return;
      if (size() == 1) {
        to_return = data_[head_];
        size_ = 0;
      } else {
        to_return = data_[head_];
        incrementHead();
        size_ -= 1;
      }

      return to_return;
    }

    std::optional<T> getFront() const {
      return  size_ == 0 ? std::nullopt : std::make_optional(data_[head_]);
    }

    std::optional<T> getBack() const {
      return  size_ == 0 ? std::nullopt : std::make_optional(data_[tail_]);
    }

    bool isFull() const {
      return size_ == capacity_;
    }

    bool isEmpty() const {
      return size_ == 0;
    }

    size_t size() const {
      return size_;
    }

    size_t capacity() const {
      return capacity_;
    }

    void Clear() {
      size_ = 0;
    }

    ~circular_buffer() {
      tail_ = 0;
      head_ = 0;
      size_ = 0;
      capacity_ = 0;
      delete[] data_;
      data_ = nullptr;
    }
  };

}  // namespace itis