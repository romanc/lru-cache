#include <algorithm>
#include <list>
#include <map>
#include <string>

class LRUCache {
public:
  LRUCache(std::size_t capacity) : capacity(capacity) {}

  void put(const std::string &key, const std::string &value) {
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

  std::string get(const std::string &key) {
    const auto search = data.find(key);
    if (search == data.end()) {
      // key not found, return empty string
      return "";
    }

    auto start = std::remove(recentlyUsed.begin(), recentlyUsed.end(), key);
    recentlyUsed.erase(start, recentlyUsed.end());
    recentlyUsed.push_front(key);

    // return the value associated with this key
    return search->second;
  }

private:
  std::size_t capacity;
  std::map<std::string, std::string> data;
  std::list<std::string> recentlyUsed;
};
