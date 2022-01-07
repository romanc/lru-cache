#include <algorithm>
#include <list>
#include <map>

template <class KeyType, class ValueType> class LRUCache {
public:
  LRUCache(std::size_t capacity) : capacity(capacity) {}

  void put(const KeyType &key, const ValueType &value) {
    const auto search = data.find(key);

    // known key, remove from recentlyUsed
    if (search != data.end()) {
      auto start = std::remove(recentlyUsed.begin(), recentlyUsed.end(), key);
      recentlyUsed.erase(start, recentlyUsed.end());
    }

    recentlyUsed.push_front(key);
    data[key] = value;

    if (data.size() > capacity) {
      data.erase(recentlyUsed.back());
      recentlyUsed.pop_back();
    }
  }

  std::optional<ValueType> get(const KeyType &key) {
    const auto search = data.find(key);
    if (search == data.end()) {
      // key not found - return nothing
      return std::nullopt;
    }

    auto start = std::remove(recentlyUsed.begin(), recentlyUsed.end(), key);
    recentlyUsed.erase(start, recentlyUsed.end());
    recentlyUsed.push_front(key);

    // return the value associated with this key
    return search->second;
  }

private:
  std::size_t capacity;
  std::map<KeyType, ValueType> data;
  std::list<KeyType> recentlyUsed;
};
