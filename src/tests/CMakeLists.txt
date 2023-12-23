

include(FindTests)

add_library(OddEngineTest STATIC main.cpp)
target_link_libraries(OddEngineTest PUBLIC OddEngine gtest gmock)

# Find tests
set(test_dirs
        core/allocator
        core/util
)

foreach(test_dir ${test_dirs})
    file(GLOB test_files ${CMAKE_SOURCE_DIR}/src/${test_dir}/*_tests.cpp)

    foreach (test_file ${test_files})
        get_filename_component(test_name ${test_file} NAME_WE)

        add_executable(${test_name} ${test_file})
        add_test(NAME ${test_name} COMMAND ${test_file})

        target_link_libraries(${test_name} PRIVATE OddEngineTest)
        set_target_properties(${test_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    endforeach()
endforeach()

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(OddEngineTest PRIVATE -Wextra -Wconversion -Wno-missing-braces -Wpedantic -Weffc++ -Werror)
endif()
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(OddEngineTest PRIVATE -Wno-c++14-extensions)
endif()
