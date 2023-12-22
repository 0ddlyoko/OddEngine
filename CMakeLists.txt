cmake_minimum_required(VERSION 3.27)
project(OddEngineApp VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)

enable_testing()

option(ENABLE_TESTS "Enable the unit tests" OFF)

# Search in the "cmake" directory for additional CMake modules.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Add third party libraries
add_subdirectory(third_party)

# And now, add project sources
add_subdirectory(src)

#add_executable(OddEngine main.cpp
#        src/core/allocator/Allocator.cpp
#        src/core/allocator/Allocator.h
#        src/core/util/PointerMath.h
#        src/core/util/PointerMath.inl
#)
#
#add_subdirectory(tests)
