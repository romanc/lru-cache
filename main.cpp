#include "LRUCache.h"

#include <iostream>

using namespace std;

int main() {
  LRUCache cache(3);

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

  cout << "cache[A]: " << cache.get("A") << endl;
  cout << "cache[A]: " << cache.get("A") << endl;
  cout << "cache[B]: " << cache.get("B") << endl;
  cout << "cache[C]: " << cache.get("C") << endl;
  cout << "cache[C]: " << cache.get("C") << endl;

  return 0;
}