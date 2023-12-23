#project(OddEngine)
#
#set(CMAKE_CXX_STANDARD 23)

add_subdirectory(core)

# Create the core app
add_library(OddEngine INTERFACE)
target_link_libraries(OddEngine INTERFACE core)

# Create the app
add_executable(OddEngineApp main.cpp)
target_link_libraries(OddEngineApp OddEngine)
add_dependencies(OddEngineApp OddEngine)

# Tests

if (ENABLE_TESTS)
    add_subdirectory(tests)
#    include_directories(${GTEST_INCLUDE_DIRS})

    # Add Tests
endif()
