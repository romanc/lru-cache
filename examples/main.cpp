#include "../src/LRUCache.h"

#include <iostream>

using namespace std;

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

  cout << "cache[A]: " << cache.get("A").value_or("not found") << endl;
  cout << "cache[A]: " << cache.get("A").value_or("not found") << endl;
  cout << "cache[B]: " << cache.get("B").value_or("not found") << endl;
  cout << "cache[C]: " << cache.get("C").value_or("not found") << endl;
  cout << "cache[C]: " << cache.get("C").value_or("not found") << endl;

  return 0;
}