add_library(LIBMEMALLOCATOR STATIC
    allocator.c
)

target_include_directories(LIBMEMALLOCATOR PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(LIBMEMALLOCATOR PRIVATE ${PROJECT_SOURCE_DIR}/src/include)

target_compile_options(LIBMEMALLOCATOR PRIVATE $<$<CONFIG:Debug>:-fsanitize=address,undefined>)

target_link_options(LIBMEMALLOCATOR PRIVATE $<$<CONFIG:Debug>:-fsanitize=address,undefined>)

