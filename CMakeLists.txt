cmake_minimum_required(VERSION 3.16)

# Project name and version
project(MyChallenges VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Helper function to simplify adding challenges
function(add_challenge folder name)
    # Use the full path to the source file
    set(SOURCE_FILE ${CMAKE_SOURCE_DIR}/${folder}/main.cpp)
    
    if (EXISTS ${SOURCE_FILE})
        add_executable(${name} ${SOURCE_FILE})
        set_target_properties(${name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${folder})
    else()
        message(FATAL_ERROR "Source file not found: ${SOURCE_FILE}")
    endif()
endfunction()

# Add challenges
add_challenge(2024/Day_1 2024_Day_1)
add_challenge(2024/Day_2 2024_Day_2)
# add_challenge(Day_2)
