

function(find_tests dir)
    file(GLOB TestFiles ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/*_tests.cpp)

#    include_directories(${CMAKE_SOURCE_DIR}/third_party/googletest)

#    message("Files: ${TestFiles}")

    foreach (TestFile ${TestFiles})
        get_filename_component(TestName ${TestFile} NAME_WE)
        set(TestName oddengine.test.${TestName})

        add_executable(${TestName} ${TestFile})
        add_test(NAME ${TestName} COMMAND ${TestName})

        message("Adding test file: ${TestName} - ${TestFile}")

        target_link_libraries(${TestName} gtest)
        if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(${TestName} PRIVATE -Wextra -Wconversion -Wno-missing-braces -Wpedantic -Weffc++ -Werror)
        endif()
        if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
            target_compile_options(${TestName} PRIVATE -Wno-c++14-extensions)
        endif()
    endforeach()
endfunction()
