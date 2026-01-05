#include "gtest/gtest.h"
#include <iostream>
extern "C" {
    #include "allocater.h"
}

TEST(MemAllocater, CheckNullAllocation) {
    unsigned char *pInt = (unsigned char*) allocater(0);
    EXPECT_EQ(pInt, nullptr);
}

TEST(MemAllocater, CheckInvSizeAllocation) {
    unsigned char *pInt = (unsigned char*) allocater(-1);
    EXPECT_NE(pInt, nullptr);
}

TEST(MemAllocater, CheckOutOfMemoryAllocation) {
    unsigned char *pInt = (unsigned char*) allocater(1024*1025);
    EXPECT_EQ(pInt, nullptr);
}

TEST(MemAllocater, CheckMemPointerReturned) {
    unsigned char *pInt = (unsigned char*) allocater(10);
    std::cout << "Value of pInt: " << pInt << "\n";
    EXPECT_NE(pInt, nullptr);
}

TEST(MemAllocater, CheckMemPointerReturnedAfterMultiAlloc) {
    unsigned char *pInt = (unsigned char*) allocater(10);
    std::cout << "Value of pInt: " << pInt << "\n";
    unsigned char *pInt2 = (unsigned char*) allocater(10);
    std::cout << "Value of pInt2: " << pInt2 << "\n";
    unsigned char *pInt3 = (unsigned char*) allocater(10);
    std::cout << "Value of pInt3: " << pInt3 << "\n";
    EXPECT_NE(pInt, nullptr);
    EXPECT_NE(pInt2, nullptr);
    EXPECT_NE(pInt3, nullptr);
}
