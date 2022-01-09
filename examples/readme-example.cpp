#include "../src/LRUCache.h"

#include <iostream>

using namespace std;
using namespace lrucache;

int main() {
  // LRUCache<KeyType, ValueType> with capacity 2
  LRUCache<string, string> cache{2};

  cache.emplace("A", "alpha"); // A -> alpha
  cache.emplace("B", "beta");  // B -> beta, A -> alpha
  cache.emplace("C", "gamma"); // C -> gamma, B -> beta

  const string default_value = "not found";

  cout << "cache[A]: "
       << (cache.get("A") ? cache.get("A")->get() : default_value) << endl;
  cout << "cache[B]: "
       << (cache.get("B") ? cache.get("B")->get() : default_value) << endl;
  cout << "Number of elements in cache: " << cache.size() << endl;
  cout << boolalpha << "Is cache full? " << cache.isFull() << endl;

  // cache[A]: not found
  // cache[B]: beta
  // Number of elements in cache: 2
  // Is cache full? true

  // cache is now: B -> beta, C -> gamma
  return 0;
}