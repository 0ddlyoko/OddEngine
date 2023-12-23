#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "allocator.h"

class MockAllocator : public Core::Allocator::Allocator {
public:
    MockAllocator(size_t size, void* start): Core::Allocator::Allocator(size, start) {}

    MOCK_METHOD(void*, allocate, (size_t size, uint8_t alignment), (override));
    MOCK_METHOD(void, deallocate, (void* p), (override));
    MOCK_METHOD(void, clear, (), (override));
};

TEST(AllocatorTest, BasicMethods) {
    void *alloc = malloc(sizeof(int) * 1000);
    MockAllocator allocator(4, alloc);

    EXPECT_EQ(4, allocator.getSize());
    EXPECT_EQ(alloc, allocator.getStart());
    EXPECT_EQ(0, allocator.getUsedMemory());
    EXPECT_EQ(0, allocator.getNumAllocations());
}
// We can't test allocate & deallocate methods as we need to implement it
