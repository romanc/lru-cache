#include "../src/LRUCache.h"

#include <catch2/catch.hpp>

using namespace std;
using namespace lrucache;

TEST_CASE("Default constructed cache", "[lrucache]") {
  LRUCache<int, double> cache{3};

  REQUIRE(cache.size() == 0);
  REQUIRE(cache.isEmpty());
  REQUIRE(cache.isFull() == false);

  REQUIRE(cache.get(42).has_value() == false);
}

TEST_CASE("Put adds element", "[lrucache]") {
  LRUCache<string, string> cache{2};
  REQUIRE(cache.size() == 0);

  cache.put("A", "alpha");
  REQUIRE(cache.size() == 1);
}

TEST_CASE("Emplace adds element", "[lrucache]") {
  LRUCache<string, string> cache{2};
  REQUIRE(cache.size() == 0);

  cache.emplace("A", "alpha");
  REQUIRE(cache.size() == 1);
}

TEST_CASE("Put with same key overrides value", "[lrucache]") {
  LRUCache<string, string> cache{2};

  cache.put("A", "alpha");
  REQUIRE(cache.size() == 1);

  cache.put("A", "alpha2");
  REQUIRE(cache.size() == 1);
  REQUIRE(cache.get("A")->get() == "alpha2");
}

TEST_CASE("Emplace with same key overrides value", "[lrucache]") {
  LRUCache<string, string> cache{2};

  cache.emplace("A", "alpha");
  REQUIRE(cache.size() == 1);

  cache.emplace("A", "alpha2");
  REQUIRE(cache.size() == 1);
  REQUIRE(cache.get("A")->get() == "alpha2");
}

TEST_CASE("Last recently inserted is evicted from cache", "[lrucache]") {
  LRUCache<string, string> cache{3};

  cache.put("A", "alpha"); // A -> alpha
  REQUIRE(cache.size() == 1);

  cache.put("B", "beta"); // B -> beta, A -> alpha
  REQUIRE(cache.size() == 2);

  cache.put("C", "gamma"); // C -> gamma, B -> beta, A -> alpha
  REQUIRE(cache.size() == 3);
  REQUIRE(cache.isFull());

  cache.put("D", "delta"); // D -> delta, C -> gamma, B -> beta
  REQUIRE(cache.size() == 3);
  REQUIRE(cache.isFull());

  REQUIRE(cache.get("A").has_value() == false);
}

TEST_CASE("Reading counts as using", "[lrucache]") {
  LRUCache<string, string> cache{3};

  cache.put("A", "alpha"); // A -> alpha
  REQUIRE(cache.size() == 1);

  cache.put("B", "beta"); // B -> beta, A -> alpha
  REQUIRE(cache.size() == 2);

  cache.get("A");          // A -> alpha, B -> beta
  cache.put("C", "gamma"); // C -> gamma, A -> alpha, B -> beta
  REQUIRE(cache.size() == 3);
  REQUIRE(cache.isFull());

  cache.get("A");          // A -> alpha, C -> gamma, B -> beta
  cache.put("D", "delta"); // D -> delta, A -> alpha, C -> gamma
  REQUIRE(cache.size() == 3);
  REQUIRE(cache.isFull());

  REQUIRE(cache.get("A")->get() == "alpha");
  // A -> alpha, D -> delta, C -> gamma
  REQUIRE(cache.get("B").has_value() == false);
  // A -> alpha, D -> delta, C -> gamma
}