# CMake generated Testfile for 
# Source directory: /mnt/data/Programming/C/MemAllocator/tests
# Build directory: /mnt/data/Programming/C/MemAllocator/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MemAllocationTests "/mnt/data/Programming/C/MemAllocator/build/tests/MemAllocationTests")
set_tests_properties(MemAllocationTests PROPERTIES  _BACKTRACE_TRIPLES "/mnt/data/Programming/C/MemAllocator/tests/CMakeLists.txt;18;add_test;/mnt/data/Programming/C/MemAllocator/tests/CMakeLists.txt;0;")
subdirs("../_deps/googletest-build")
