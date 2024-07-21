set(CMAKE_CXX_STANDARD 17)

if (BUILD_TESTING)
    add_executable(tests main.cpp unit/heap_init.cpp unit/heap_alloc.cpp unit/heap_free.cpp)
    target_link_libraries(tests PRIVATE GTest::gtest_main)
    target_sources(tests PRIVATE ${PROJECT_SOURCE_DIR}/src/heap.cpp)
    target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/include)

    include(GoogleTest)
    gtest_discover_tests(tests)
endif()
