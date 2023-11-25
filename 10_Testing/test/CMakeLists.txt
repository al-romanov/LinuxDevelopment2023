add_executable(grow_test grow_test.c)
target_link_libraries(grow_test buf)
add_test(NAME grow_test COMMAND grow_test)

add_executable(init_test init_test.c)
target_link_libraries(init_test buf)
add_test(NAME init_test COMMAND init_test)

add_executable(null_test null_test.c)
target_link_libraries(null_test buf)
add_test(NAME null_test COMMAND null_test)

add_executable(pop_test pop_test.c)
target_link_libraries(pop_test buf)
add_test(NAME pop_test COMMAND pop_test)

add_executable(push_test push_test.c)
target_link_libraries(push_test buf)
add_test(NAME push_test COMMAND push_test)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})
if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    setup_target_for_coverage_lcov(NAME get_coverage
        EXECUTABLE init_test
        BASE_DIRECTORY "../build")
endif()
