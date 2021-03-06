#include "../src/LRUCache.h"

#include <iostream>

using namespace std;
using namespace lrucache;

int main() {
  LRUCache<string, string> cache{3};

  cout << "put(A)" << endl;
  cache.emplace("A", "alpha");

  cout << "put(B)" << endl;
  cache.emplace("B", "beta");

  cout << "put(B)" << endl;
  cache.emplace("B", "beta");

  cout << "put(C)" << endl;
  cache.emplace("C", "gamma");

  cout << "put(D)" << endl;
  cache.emplace("D", "delta");

  const string default_value = "not found";

  cout << "cache[A]: "
       << (cache.get("A") ? cache.get("A")->get() : default_value) << endl;
  cout << "cache[A]: "
       << (cache.get("A") ? cache.get("A")->get() : default_value) << endl;
  cout << "cache[B]: "
       << (cache.get("B") ? cache.get("B")->get() : default_value) << endl;
  cout << "cache[C]: "
       << (cache.get("C") ? cache.get("C")->get() : default_value) << endl;
  cout << "cache[C]: "
       << (cache.get("C") ? cache.get("C")->get() : default_value) << endl;
  cout << "cache[D]: "
       << (cache.get("D") ? cache.get("D")->get() : default_value) << endl;

  return 0;
}