cmake_minimum_required(VERSION 3.16..3.31.6)

project(ARMCortexM-TestFramework
    LANGUAGES CXX C ASM
    VERSION 1.0.0
    DESCRIPTION "Test framework for ARM Cortex-M C++ Library"
)

# Options
option(BUILD_TESTS "Build test suite" ON)
option(BUILD_BENCHMARKS "Build performance benchmarks" ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the library as subdirectory
add_subdirectory(lib)

# Enable testing
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Install rules
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests/platforms
    DESTINATION share/armcortexm-tests
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests/robot
    DESTINATION share/armcortexm-tests
)
