#include "LRUCache.h"

#include <iostream>

using namespace std;

int main() {
  LRUCache cache(3);

  cout << "put(A)" << endl;
  cache.put("A", "alpha");
  cache.debug();

  cout << "put(B)" << endl;
  cache.put("B", "beta");
  cache.debug();

  cout << "put(B)" << endl;
  cache.put("B", "beta");
  cache.debug();

  cout << "put(C)" << endl;
  cache.put("C", "gamma");
  cache.debug();

  cout << "put(D)" << endl;
  cache.put("D", "delta");
  cache.debug();

  cout << "cache[A]: " << cache.get("A") << endl;
  cout << "cache[A]: " << cache.get("A") << endl;
  cout << "cache[B]: " << cache.get("B") << endl;
  cout << "cache[C]: " << cache.get("C") << endl;

  cache.debug();

  return 0;
}