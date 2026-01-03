cmake_minimum_required(VERSION 3.12)
project("Userspace Memory Allocator"
    VERSION 0.1.0
    DESCRIPTION "A C memory allocator like malloc but in userspace only"
    LANGUAGES C CXX
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable testing infrastructure
include(CTest)

add_compile_options(-Wall -Werror -Wpedantic -Wextra)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)

