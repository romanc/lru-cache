#include "../src/LRUCache.h"

#include <iostream>

using namespace std;
using namespace lrucache;

int main() {
  LRUCache<string, string> cache(3);

  cout << "put(A)" << endl;
  cache.put("A", "alpha");

  cout << "put(B)" << endl;
  cache.put("B", "beta");

  cout << "put(B)" << endl;
  cache.put("B", "beta");

  cout << "put(C)" << endl;
  cache.put("C", "gamma");

  cout << "put(D)" << endl;
  cache.put("D", "delta");

  cout << "cache[A]: "
       << (cache.get("A").has_value() ? cache.get("A").value().get()
                                      : "not found")
       << endl;
  cout << "cache[A]: "
       << (cache.get("A").has_value() ? cache.get("A").value().get()
                                      : "not found")
       << endl;
  cout << "cache[B]: "
       << (cache.get("B").has_value() ? cache.get("B").value().get()
                                      : "not found")
       << endl;
  cout << "cache[C]: "
       << (cache.get("C").has_value() ? cache.get("C").value().get()
                                      : "not found")
       << endl;
  cout << "cache[C]: "
       << (cache.get("C").has_value() ? cache.get("C").value().get()
                                      : "not found")
       << endl;
  cout << "cache[D]: "
       << (cache.get("D").has_value() ? cache.get("D").value().get()
                                      : "not found")
       << endl;

  return 0;
}