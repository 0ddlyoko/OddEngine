

include(FindTests)

add_library(OddEngineTest STATIC main.cpp)
target_link_libraries(OddEngineTest PUBLIC OddEngine gtest)

# Find tests
set(test_dirs
    core/allocator
)

foreach(test_dir test_dirs)
    file(GLOB test_files ${CMAKE_SOURCE_DIR}/src/${test_dir}/*_tests.cpp)

    foreach (test_file ${test_files})
        get_filename_component(TestName ${test_file} NAME_WE)

        add_executable(${test_target} "${test_file}.cpp")
        gtest_discover_tests(${test_target})
        target_link_libraries(${test_target} PRIVATE OddEngineTest)
        set_target_properties(${test_target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#
#        set(TestName oddengine.test.${TestName})
#
#        add_executable(${TestName} ${test_file})
#        add_test(NAME ${TestName} COMMAND ${TestName})
#
#        message("Adding test file: ${TestName} - ${test_file}")
#
#        target_link_libraries(${TestName} gtest)
#        if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
#            target_compile_options(${TestName} PRIVATE -Wextra -Wconversion -Wno-missing-braces -Wpedantic -Weffc++ -Werror)
#        endif()
#        if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#            target_compile_options(${TestName} PRIVATE -Wno-c++14-extensions)
#        endif()
    endforeach()
endforeach()
find_tests(${CMAKE_SOURCE_DIR}/src/core/allocator)
