add_subdirectory(Catch2)
add_executable(runner usage.cpp memory.cpp catchMain.cpp)
target_link_libraries(runner Catch2::Catch2)
