cmake_minimum_required(VERSION 3.16)

# Project name and version
project(MyChallenges VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB MODULES_SOURCES 2025/modules/*.cpp)
file(GLOB MODULES_HEADERS 2025/modules/*.h)

add_executable(2025_challenges 2025/main.cpp ${MODULES_SOURCES} ${MODULES_HEADERS})

# Add Google Test
add_subdirectory(${CMAKE_SOURCE_DIR}/external/gtest)
include_directories(${CMAKE_SOURCE_DIR}/external/gtest/googletest/include)

# Add test executable
add_executable(test_samples 2025/tests/test_samples.cpp  ${MODULES_SOURCES} ${MODULES_HEADERS})
target_link_libraries(test_samples PRIVATE gtest gtest_main pthread)
