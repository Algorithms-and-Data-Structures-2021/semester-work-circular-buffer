#include <iostream>

#include "circular_buffer.hpp"

using namespace std;

int main() {
  itis::circular_buffer<int> buf = itis::circular_buffer<int>(8);
  for (int num = 1; num < 16; num++) {
    buf.EnqueueBack(num);
  }
  cout << buf.getFront().value() << ' ' << buf.getBack().value() << endl;
  return 0;
}