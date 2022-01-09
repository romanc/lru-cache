#include "../src/LRUCache.h"
#include <iostream>

using namespace lrucache;
using namespace std;

class Moveable {
public:
  Moveable(int n) : n(n) {
    cout << "constructor(Moveable:" << n << ")" << endl;
  }

  Moveable(const Moveable &other) noexcept {
    n = other.n;
    cout << "copy contructor (Moveable:" << n << ")" << endl;
  }
  Moveable &operator=(const Moveable &other) noexcept {
    n = other.n;
    cout << "copy assignment (Moveable:" << n << ")" << endl;

    return *this;
  }

  Moveable(Moveable &&other) noexcept {
    n = other.n;
    other.n = -1;
    cout << "move contructor (Moveable:" << n << ")" << endl;
  }
  Moveable &operator=(Moveable &&other) noexcept {
    n = other.n;
    other.n = -1;
    cout << "move assignment (Moveable:" << n << ")" << endl;

    return *this;
  }

  ~Moveable() { cout << "destructor (Moveable:" << n << ")" << endl; }

private:
  int n;
};

class NonMoveable {
public:
  NonMoveable(int n) : n(n) {
    cout << "constructor(NonMoveable:" << n << ")" << endl;
  }

  NonMoveable(const NonMoveable &other) noexcept {
    n = other.n;
    cout << "copy contructor (NonMoveable:" << n << ")" << endl;
  }
  NonMoveable &operator=(const NonMoveable &other) noexcept {
    n = other.n;
    cout << "copy assignment (NonMoveable:" << n << ")" << endl;

    return *this;
  }

  ~NonMoveable() { cout << "destructor (NonMoveable:" << n << ")" << endl; }

private:
  int n;
};

int main() {
  // This sample is to show how emplace() forwards constructor arguments to the
  // `unordered_map` inside the `LRUCache`.
  //
  // Sample output
  //
  // $ ./moveTest
  // Moveable class
  // ==============
  // cache.put(1, 1)
  // constructor(Moveable:1)
  // move contructor (Moveable:1)
  // destructor (Moveable:-1)
  //
  // cache.put(2, 2)
  // constructor(Moveable:2)
  //
  // cache.put(3, 3)
  // destructor (Moveable:1)
  // constructor(Moveable:3)
  //
  // NonMoveable class
  // =================
  // cache.put(1, 1)
  // constructor(NonMoveable:1)
  // copy contructor (NonMoveable:1)
  // destructor (NonMoveable:1)
  //
  // cache.put(2, 2)
  // constructor(NonMoveable:2)
  //
  // cache.put(3, 3)
  // destructor (NonMoveable:1)
  // constructor(NonMoveable:3)
  //
  // destructor (NonMoveable:3)
  // destructor (NonMoveable:2)
  // destructor (Moveable:3)
  // destructor (Moveable:2)

  cout << "Moveable class" << endl << "==============" << endl;
  LRUCache<int, Moveable> cache{2};

  // put(1, 1) will first create a Moveable from 1 and then move it
  cout << "cache.put(1, 1)" << endl;
  cache.put(1, 1);
  cout << endl;

  // emplace(2, 2) will forward the constructor argument and construct Movable
  // in-place inside the cache.
  cout << "cache.put(2, 2)" << endl;
  cache.emplace(2, 2);
  cout << endl;

  cout << "cache.put(3, 3)" << endl;
  cache.emplace(3, 3);
  cout << endl;

  cout << "NonMoveable class" << endl << "=================" << endl;
  LRUCache<int, NonMoveable> otherCache{2};

  // put(1, 1) will first create a Moveable from 1 and then copy it
  cout << "cache.put(1, 1)" << endl;
  otherCache.put(1, 1);
  cout << endl;

  // emplace(2, 2) will forward the constructor argument and construct Movable
  // in-place inside the cache.
  cout << "cache.put(2, 2)" << endl;
  otherCache.emplace(2, 2);
  cout << endl;

  cout << "cache.put(3, 3)" << endl;
  otherCache.emplace(3, 3);
  cout << endl;

  return 0;
}