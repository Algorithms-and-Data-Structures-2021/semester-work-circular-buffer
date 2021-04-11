#pragma once

#include <cstddef>
#include <optional>

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

    void incrementHead();

    void incrementTail();

    void decrementHead();

    void decrementTail();

    // Tip 2: На начальном этапе разработки структуры данных можете определения методов задавать в
    // заголовочном файле, как только работа будет завершена, можно будет оставить здесь только объявления.
   public:
    explicit circular_buffer(size_t max_size_) :
            data_(new T[max_size_]), capacity_(max_size_) {}

    void EnqueueBack(T &elem);

    void EnqueueFront(T &elem);

    T DequeueBack();

    T DequeueFront();

    std::optional<T> getFront() const;

    std::optional<T> getBack() const;

    bool isFull() const;

    bool isEmpty() const;

    size_t size() const;

    size_t capacity() const;

    void Clear();

    ~circular_buffer();
  };

}  // namespace itis