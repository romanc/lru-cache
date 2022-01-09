#include "../src/LRUCache.h"

#include <catch2/catch.hpp>

using namespace std;
using namespace lrucache;

class Moveable {
public:
  Moveable(int n) : n(n) { ++constructorCallCount; }

  Moveable(const Moveable &other) noexcept {
    n = other.n;
    constructorCallCount = other.constructorCallCount;
    destructorCallCount = other.destructorCallCount;
    copyConstructorCallCount = other.copyConstructorCallCount;
    copyAssignCallCount = other.copyAssignCallCount;
    moveConstructorCallCount = other.moveConstructorCallCount;
    moveAssignCallCount = other.moveAssignCallCount;

    ++copyConstructorCallCount;
  }
  Moveable &operator=(const Moveable &other) noexcept {
    n = other.n;
    constructorCallCount = other.constructorCallCount;
    destructorCallCount = other.destructorCallCount;
    copyConstructorCallCount = other.copyConstructorCallCount;
    copyAssignCallCount = other.copyAssignCallCount;
    moveConstructorCallCount = other.moveConstructorCallCount;
    moveAssignCallCount = other.moveAssignCallCount;

    ++copyAssignCallCount;
    return *this;
  }

  Moveable(Moveable &&other) noexcept {
    n = other.n;
    constructorCallCount = other.constructorCallCount;
    destructorCallCount = other.destructorCallCount;
    copyConstructorCallCount = other.copyConstructorCallCount;
    copyAssignCallCount = other.copyAssignCallCount;
    moveConstructorCallCount = other.moveConstructorCallCount;
    moveAssignCallCount = other.moveAssignCallCount;

    ++moveConstructorCallCount;
  }
  Moveable &operator=(Moveable &&other) noexcept {
    n = other.n;
    constructorCallCount = other.constructorCallCount;
    destructorCallCount = other.destructorCallCount;
    copyConstructorCallCount = other.copyConstructorCallCount;
    copyAssignCallCount = other.copyAssignCallCount;
    moveConstructorCallCount = other.moveConstructorCallCount;
    moveAssignCallCount = other.moveAssignCallCount;

    ++moveAssignCallCount;
    return *this;
  }

  ~Moveable() { ++destructorCallCount; }

  size_t constructorCalls() const { return constructorCallCount; }
  size_t destructorCalls() const { return destructorCallCount; }
  size_t copyConstructorCalls() const { return copyConstructorCallCount; }
  size_t copyAssignments() const { return copyAssignCallCount; }
  size_t moveConstructorCalls() const { return moveConstructorCallCount; }
  size_t moveAssignments() const { return moveAssignCallCount; }

private:
  int n;
  size_t constructorCallCount = 0;
  size_t destructorCallCount = 0;
  size_t copyConstructorCallCount = 0;
  size_t copyAssignCallCount = 0;
  size_t moveConstructorCallCount = 0;
  size_t moveAssignCallCount = 0;
};

TEST_CASE("Memory management", "[lrucache]") {
  LRUCache<int, Moveable> cache{2};

  SECTION("Emplace call only constructor") {
    cache.emplace(1, 1);
    const auto &cacheElement = cache.get(1)->get();

    // Moveable(1) needs to be constructed once
    REQUIRE(cacheElement.constructorCalls() == 1);

    // Ensure constructed element is neither moved ...
    REQUIRE(cacheElement.moveConstructorCalls() == 0);
    REQUIRE(cacheElement.copyConstructorCalls() == 0);

    // .. nor copied
    REQUIRE(cacheElement.moveAssignments() == 0);
    REQUIRE(cacheElement.copyAssignments() == 0);
  }

  SECTION("Put moves moveable types") {
    cache.put(1, 1);
    const auto &cacheElement = cache.get(1)->get();

    // Moveable needs to be constructed somewhere
    REQUIRE(cacheElement.constructorCalls() == 1);

    // Ensure constructed element is moved ...
    REQUIRE((cacheElement.moveConstructorCalls() == 1 ||
             cacheElement.moveAssignments() == 1));

    // ... and not copied
    REQUIRE(cacheElement.copyConstructorCalls() == 0);
    REQUIRE(cacheElement.copyAssignments() == 0);
  }
}
