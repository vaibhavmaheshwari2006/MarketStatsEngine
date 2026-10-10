cmake_minimum_required(VERSION 3.10)
project(MarketStatsEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable maximum optimizations for the benchmark
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -DNDEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include_directories(src)

add_executable(MarketStatsEngine 
    src/main.cpp 
    src/MarketStatsEngine.cpp
)
