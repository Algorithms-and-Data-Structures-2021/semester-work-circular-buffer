#include "circular_buffer.hpp"

#include <stdexcept>  // logic_error


// файл с определениями

namespace itis {

    // здесь должны быть определения методов вашей структуры

    template<class T>
    void circular_buffer<T>::EnqueueBack(T &elem) {
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

    template<class T>
    void circular_buffer<T>::EnqueueFront(T &elem) {
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

    template<class T>
    T circular_buffer<T>::DequeueBack() {
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

    template<class T>
    T circular_buffer<T>::DequeueFront() {
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

    template<class T>
    std::optional<T> circular_buffer<T>::getFront() const {
      return  size_ == 0 ? std::nullopt : std::make_optional(data_[head_]);
    }

    template<class T>
    std::optional<T> circular_buffer<T>::getBack() const {
      return  size_ == 0 ? std::nullopt : std::make_optional(data_[tail_]);
    }

    template<class T>
    void circular_buffer<T>::incrementHead() {
      head_ = (head_ + 1) % capacity_;
    }

    template<class T>
    void circular_buffer<T>::incrementTail() {
      tail_ = (tail_ + 1) % capacity_;
    }

    template<class T>
    void circular_buffer<T>::decrementHead() {
      if (head_ == 0) /* т.к. тип size_t не может принять отриц. значение, проврка такая */{
        head_ = capacity_ - 1;
      } else {
        head_ -= 1;
      }
    }

    template<class T>
    void circular_buffer<T>::decrementTail() {
      if (tail_ == 0) /* т.к. тип size_t не может принять отриц. значение, проврка такая */{
        tail_ = capacity_ - 1;
      } else {
        tail_ -= 1;
      }
    }


    template<class T>
      bool circular_buffer<T>::isFull() const {
        return size_ == capacity_;
      }

    template<class T>
    bool circular_buffer<T>::isEmpty() const {
      return size_ == 0;
    }

    template<class T>
    size_t circular_buffer<T>::size() const {
      return size_;
    }

    template<class T>
    size_t circular_buffer<T>::capacity() const {
      return capacity_;
    }

    template<class T>
    void circular_buffer<T>::Clear() {
      size_ = 0;
    }

    template<class T>
    circular_buffer<T>::~circular_buffer() {
      tail_ = 0;
      head_ = 0;
      size_ = 0;
      capacity_ = 0;
      delete[] data_;
      data_ = nullptr;
    }

}  // namespace itis