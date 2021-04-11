#include <iostream>

#include "circular_buffer.hpp"

using namespace std;

int main() {
  itis::circular_buffer<int> buf = itis::circular_buffer<int>(8);
  int num = 1;
  buf.EnqueueBack(num);
  cout << buf.getBack().value() << ' ' << buf.getFront().value() << endl;
  return 0;
}