#pragma once

#include <cstddef>
#include <optional>
#include <stdexcept>  // logic_error
#include <cassert> // assert

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
    // замыкание кольцевого буфера - после последнего элемента в массиве data_ будет следовать первый
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

    // добавление элемента в конец
    void EnqueueBack(T &elem) {
      if (isFull()) {
        // буфер полон - перезаписываем данные
        incrementHead();
        incrementTail();
        data_[tail_] = elem;
      } else if (isEmpty()) {
        // буфер пуст - добавляем первый элемент куда угодно, но я решил, что на нулевую позицию
        head_ = 0;
        tail_ = 0;
        data_[tail_] = elem;
        size_ += 1;
      } else {
        // просто добавляем новый элемент в конец
        incrementTail();
        data_[tail_] = elem;
        size_ += 1;
      }
    }

    // добавление элемента в начало
    void EnqueueFront(T &elem) {
      if (isFull()) {
        // буфер полон - перезаписываем данные
        decrementHead();
        decrementTail();
        data_[head_] = elem;
      } else if (isEmpty()) {
        // буфер пуст - добавляем первый элемент куда угодно, но я решил, что на нулевую позицию
        head_ = 0;
        tail_ = 0;
        data_[head_] = elem;
        size_ += 1;
      } else {
        // просто добавляем новый элемент в конец
        decrementHead();
        data_[head_] = elem;
        size_ += 1;
      }
    }

    // взятие элемента с конца и его удаление
    T DequeueBack() {
      if (isEmpty()) {
        // из пустого буфера нечего удалять
        throw std::logic_error("cannot dequeue from empty buffer");
      }
      T to_return;
      if (size() == 1) {
        // в случае одного элемента нет нужды в том чтобы перемещать индекс после очищения буфера
        to_return = data_[tail_];
        size_ = 0;
      } else {
        // просто перемещаем указатель, тем самым разрешая перезаписать элемент, к нему больше не будет доступа
        to_return = data_[tail_];
        decrementTail();
        size_ -= 1;
      }

      return to_return;
    }

    // взятие элемента с начала и его удаление
    T DequeueFront() {
      if (isEmpty()) {
        // из пустого буфера нечего удалять
        throw std::logic_error("cannot dequeue from empty buffer");
      }
      T to_return;
      if (size() == 1) {
        // в случае одного элемента нет нужды в том чтобы перемещать индекс после очищения буфера
        to_return = data_[head_];
        size_ = 0;
      } else {
        // просто перемещаем указатель, тем самым разрешая перезаписать элемент, к нему больше не будет доступа
        to_return = data_[head_];
        incrementHead();
        size_ -= 1;
      }

      return to_return;
    }

    // получение элемента с конца без его удаления
    std::optional<T> getFront() const {
      return  size_ == 0 ? std::nullopt : std::make_optional(data_[head_]);
    }

    // получение элемента с начала без его удаления
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

    // увеличение вместительности буфера
    void Resize(size_t new_capacity) {
      assert(new_capacity > capacity_);

      T *new_data = new T[new_capacity];

      if (head_ <= tail_) {
        // первый случай - начало левее конца:  [x, x, 1, 2, 3, 4, x]
        std::copy(data_ + head_, data_ + tail_ + 1, new_data);
      } else {
        // второй случай - начало правее конца:  [3, 4, x, x, x, 1, 2]
        std::copy(data_ + head_, data_ + capacity_, new_data);
        std::copy(data_, data_ + tail_ + 1, new_data + capacity_ - head_);
      }
      if (size_ > 0) {
        // данные переместились в начало массива - обновим указатели
        head_ = 0;
        tail_ = size_ - 1;
      }
      capacity_ = new_capacity;
      // высвободим память из-под старого массива
      delete[] data_;
      data_ = new_data;
    }

    void Clear() {
      // менять значения указателей необязательно, они все равно поменяются, если добавить в пустой буфер элемент
      size_ = 0;
    }

    ~circular_buffer() {
      tail_ = 0;
      head_ = 0;
      size_ = 0;
      capacity_ = 0;
      // не забываем высвободить память
      delete[] data_;
      data_ = nullptr;
    }
  };

}  // namespace itis