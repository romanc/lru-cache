# LRU Cache

Simple, header-only implementation of a last recently used (LRU) cache, see [wikipedia](https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_(LRU)).

## Usage

Simplest is to copy `src/LRUCache.h` directly into your project tree. See `examples/` folder for useage samples.

## Building samples and test

First, clone this repository. Initializing the submodule is optional and only necessary if you want to build the tests.

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

**Warning** This is not intended for use in production.
