#ifndef LRU_CACHE
#define LRU_CACHE

#include <algorithm>
#include <functional>
#include <list>
#include <unordered_map>

namespace lrucache {

template <class KeyType, class ValueType> class LRUCache {
public:
  LRUCache(std::size_t capacity) : capacity(capacity) {}

  template <class U> void put(const KeyType &key, U &&value) {
    const auto search = data.find(key);

    // case: known key
    if (search != data.end()) {
      // move key in recently used to the end
      auto pos = std::find(recentlyUsed.begin(), recentlyUsed.end(), key);
      recentlyUsed.splice(recentlyUsed.end(), recentlyUsed, pos);

      // update the value
      data.insert_or_assign(key, std::forward<U>(value));
      return;
    }

    // case: cache full
    if (data.size() >= capacity) {
      // evict oldest element
      data.erase(recentlyUsed.front());
      recentlyUsed.pop_front();
    }

    // store new element
    recentlyUsed.push_back(key);
    data.emplace(key, std::forward<U>(value));
  }

  std::optional<std::reference_wrapper<const ValueType>>
  get(const KeyType &key) const {
    const auto search = data.find(key);

    // case: key not found
    if (search == data.end()) {
      // return nothing
      return std::nullopt;
    }

    // move key in recently used to the end
    auto pos = std::find(recentlyUsed.begin(), recentlyUsed.end(), key);
    recentlyUsed.splice(recentlyUsed.end(), recentlyUsed, pos);

    // return the value associated with this key
    return std::cref(search->second);
  }

private:
  const std::size_t capacity;
  std::unordered_map<KeyType, ValueType> data;
  mutable std::list<KeyType> recentlyUsed;
};

} // namespace lrucache

#endif