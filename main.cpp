#include <iostream>

#include "circular_buffer.hpp"

using namespace std;

int main() {
  itis::circular_buffer<int> buf = itis::circular_buffer<int>(8);
  for (int num = 1; num < 16; num++) {
    buf.EnqueueBack(num);
  }
  buf.Resize(10);
  int num = 99;
  buf.EnqueueBack(num); num = 11; buf.EnqueueFront(num);
  cout << buf.getFront().value() << ' ' << buf.getBack().value() << endl;
  return 0;
}