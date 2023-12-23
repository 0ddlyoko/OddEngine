if (ENABLE_TESTS)
    # Add Google Test
    set(INSTALL_GTEST OFF)
    set(INSTALL_GMOCK OFF)
    set(BUILD_GMOCK ON)

    if ("${CMAKE_SYSTEM_NAME}" STREQUAL "CYGWIN")
        add_definitions(-DTEST_HAS_PTHREAD=0)
        set(gtest_disable_pthreads ON)
    endif()

    add_subdirectory("googletest")
endif(ENABLE_TESTS)
