cmake_minimum_required(VERSION 3.17)

project(LRUCache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(LRUCACHE_BUILD_TESTS "Build tests" ON)
option(LRUCACHE_BUILD_EXAMPLES "Build examples" OFF)

if(LRUCACHE_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

if(LRUCACHE_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
  add_test(LRUTests tests/runner)
endif()
