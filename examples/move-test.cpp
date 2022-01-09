#include "../src/LRUCache.h"
#include <iostream>

using namespace lrucache;
using namespace std;

class MyInt {
public:
  MyInt(int n) : n(n) { cout << "constructor(MyInt:" << n << ")" << endl; }

  MyInt(const MyInt &other) noexcept {
    n = other.n;
    cout << "copy contructor (MyInt:" << n << ")" << endl;
  }
  MyInt &operator=(const MyInt &other) noexcept {
    n = other.n;
    cout << "copy assignment (MyInt:" << n << ")" << endl;

    return *this;
  }

  MyInt(MyInt &&other) noexcept {
    n = other.n;
    other.n = -1;
    cout << "move contructor (MyInt:" << n << ")" << endl;
  }
  MyInt &operator=(MyInt &&other) noexcept {
    n = other.n;
    other.n = -1;
    cout << "move assignment (MyInt:" << n << ")" << endl;

    return *this;
  }

  ~MyInt() { cout << "destructor (MyInt:" << n << ")" << endl; }

private:
  int n;
};

int main() {
  // This sample is to show how constructor arguments to `MyInt` are
  // forwarded and only constructed inside the `unordered_map` inside
  // the `LRUCache`.
  //
  // Sample output
  //
  // $ ./moveTest
  // constructor(MyInt:1)
  // constructor(MyInt:2)
  // constructor(MyInt:3)
  // destructor (MyInt:1)
  // constructor(MyInt:4)
  // destructor (MyInt:4)
  // destructor (MyInt:3)
  // destructor (MyInt:2)

  LRUCache<int, MyInt> cache(3);

  cache.put(1, 1);
  cache.put(2, 2);
  cache.put(3, 3);
  cache.put(4, 4);

  return 0;
}