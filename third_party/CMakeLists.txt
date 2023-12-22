if (ENABLE_TESTS)
    # Add Google Test
    set(install_gtest OFF)
    set(install_gmock OFF)
    set(build_gmock ON)
    add_subdirectory("googletest")
#    find_package(GTest REQUIRED)
#    include_directories(${GTEST_INCLUDE_DIRS})
endif(ENABLE_TESTS)
