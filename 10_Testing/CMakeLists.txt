project(buf-grow-testing)
cmake_minimum_required(VERSION 3.10)

include(CTest)

include_directories(include)
add_subdirectory(src)

enable_testing()
add_subdirectory(test)
