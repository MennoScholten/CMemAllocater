include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(MemAllocationTests allocatorTests.cpp)

target_link_libraries(MemAllocationTests PRIVATE
    LIBMEMALLOCATOR
    gtest
    gtest_main
)

add_test(
    NAME MemAllocationTests
    COMMAND MemAllocationTests
)

