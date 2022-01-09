#include "../src/LRUCache.h"

#include <catch2/catch.hpp>

using namespace std;
using namespace lrucache;

TEST_CASE("Usage tests", "[lrucache]") {
  LRUCache<string, string> cache{3};

  SECTION("Default constructed cache") {
    REQUIRE(cache.size() == 0);
    REQUIRE(cache.isEmpty());
    REQUIRE(cache.isFull() == false);
    REQUIRE(cache.get("42").has_value() == false);
  }

  SECTION("Put adds element", "[lrucache]") {
    cache.put("A", "alpha");
    REQUIRE(cache.size() == 1);
    REQUIRE(cache.isFull() == false);
    REQUIRE(cache.isEmpty() == false);
  }

  SECTION("Emplace adds element") {
    cache.emplace("A", "alpha");
    REQUIRE(cache.size() == 1);
  }

  SECTION("Put with same key overrides value") {
    cache.put("A", "alpha");
    cache.put("A", "alpha2");
    REQUIRE(cache.size() == 1);
    REQUIRE(cache.get("A")->get() == "alpha2");
  }

  SECTION("Emplace with same key overrides value") {
    cache.emplace("A", "alpha");
    cache.emplace("A", "alpha2");
    REQUIRE(cache.size() == 1);
    REQUIRE(cache.get("A")->get() == "alpha2");
  }

  SECTION("Last recently inserted is evicted from cache") {
    cache.emplace("A", "alpha"); // A -> alpha
    cache.emplace("B", "beta");  // B -> beta, A -> alpha
    REQUIRE(cache.size() == 2);

    cache.emplace("C", "gamma"); // C -> gamma, B -> beta, A -> alpha
    REQUIRE(cache.size() == 3);
    REQUIRE(cache.isFull());

    cache.emplace("D", "delta"); // D -> delta, C -> gamma, B -> beta
    REQUIRE(cache.size() == 3);
    REQUIRE(cache.isFull());

    REQUIRE(cache.get("A").has_value() == false);
  }

  SECTION("Reading counts as using") {
    cache.emplace("A", "alpha"); // A -> alpha
    cache.emplace("B", "beta");  // B -> beta, A -> alpha
    cache.get("A");              // A -> alpha, B -> beta
    cache.emplace("C", "gamma"); // C -> gamma, A -> alpha, B -> beta
    cache.get("A");              // A -> alpha, C -> gamma, B -> beta
    cache.emplace("D", "delta"); // D -> delta, A -> alpha, C -> gamma

    REQUIRE(cache.get("A")->get() == "alpha");
    // A -> alpha, D -> delta, C -> gamma
    REQUIRE(cache.get("B").has_value() == false);
    // A -> alpha, D -> delta, C -> gamma
  }
}