# LRU Cache

Generic, header-only implementation of a last recently used (LRU) cache, see [wikipedia](https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_(LRU)).

## Usage

`LRUCache` is templated on `KeyType` and `ValueType`. The cache is initialized with a maximal capcity and offers `put(key, value)` / `emplace(key, value)` and `get(key)` functions.

```c++
#include<LRUCache.h>

#include <iostream>

using namespace std;
using namespace lrucache;

int main() {
  // LRU cache with capacity 2
  LRUCache<string, string> cache{2};

  cache.emplace("A", "alpha"); // A -> alpha
  cache.emplace("B", "beta");  // B -> beta, A -> alpha
  cache.emplace("C", "gamma"); // C -> gamma, B -> beta

  const string default_value = "not found";

  cout << "cache[A]: "
       << (cache.get("A") ? cache.get("A")->get() : default_value) << endl;
  cout << "cache[B]: "
       << (cache.get("B") ? cache.get("B")->get() : default_value) << endl;

  // cache[A]: not found
  // cache[B]: beta

  // cache is now: B -> beta, C -> gamma
  return 0;
}
```

In contrast to `put()`, `emplace()` forwards construtor arguments of the `ValueType`, see [move example](examples/move-test.cpp).

The return value of `get(key)` is an optional (see [optional type](https://en.cppreference.com/w/cpp/utility/optional) (C++17)) reference to the key's associated value in the cache. Optional references are not part of the C++17 standard (see [why](https://www.fluentcpp.com/2018/10/05/pros-cons-optional-references/)). This library decided against using raw pointers and used `std::optional<std:reference_wrapper<const ValueType>>` instead. Sadly, the reference wrapper breaks `optional<T>::value_or(default_value)` which leads to the current syntax.

#### Using it in your project

`LRUCache` is header-only, so teh simplest usage is to copy `src/LRUCache.h` directly into your project tree. See [examples/](examples/) folder for more usage samples.

**Warning** It is not advised to use this library in production code. This code is provided as-is. Use at your own risk, see [LICENSE].

## Building samples and test

If you want to run tests and samples, start  by cloning this repository. Initializing the submodule is optional and only necessary if you want to build the tests.

```bash
git clone --recurse-submodule git@github.com:romanc/lru-cache.git
```

Then, create a build folder, configure `CMake` (commands below use the [Ninja](https://ninja-build.org/) build system), build and run all tests.

```bash
cd lru-cache/
mkdir build/
cd build/
cmake -G Ninja ..
cmake -build .
ctest
```

**Note** By default, tests will be built, but examples won't. Configure `CMake` with `cmake -G Ninja -DLRUCACHE_BUILD_EXAMPLES=ON ..` to build the examples:

```bash
cd lru-cache/
mkdir build/
cd build/
cmake -G Ninja -DLRUCACHE_BUILD_EXAMPLES=ON ..
cmake -build .
./examples/simpleExample
```
