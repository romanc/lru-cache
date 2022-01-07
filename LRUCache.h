#include <algorithm>
#include <iostream>
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
      std::cout << "found existing key" << std::endl;
      auto start = std::remove(recentlyUsed.begin(), recentlyUsed.end(), key);
      recentlyUsed.erase(start, recentlyUsed.end());
    }

    recentlyUsed.push_front(key);
    data[key] = value;

    if (data.size() > capacity) {
      std::cout << "removing last recently used element" << std::endl;
      std::cout << "data.size() = " << data.size() << std::endl;
      std::cout << "rUsed.size() = " << recentlyUsed.size() << std::endl;

      auto remove = recentlyUsed.back();

      // std::cout << remove << std::endl;
      std::cout << "removing " << remove << " from cache" << std::endl;
      data.erase(remove);
      recentlyUsed.pop_back();

      std::cout << "data.size() = " << data.size() << std::endl;
      std::cout << "rUsed.size() = " << recentlyUsed.size() << std::endl;
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

  void debug() const {
    std::cout << "keys: ";
    for (const auto &[key, value] : data) {
      std::cout << key << " ";
    }
    std::cout << std::endl;

    std::cout << "Last recently used: ";
    for (const auto &key : recentlyUsed) {
      std::cout << key << " ";
    }
    std::cout << std::endl;
  }

private:
  std::size_t capacity;
  std::map<std::string, std::string> data;
  std::list<std::string> recentlyUsed;
};
