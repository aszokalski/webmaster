add_executable(generator_tests generator_tests.cpp)
target_link_libraries(generator_tests
        Generator
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )