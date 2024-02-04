#include <gtest/gtest.h>
#include "block_allocator.h"
#include "../util/pointer_math.h"


struct FreeBlock {
    FreeBlock* next_free_address;
};

struct TestBlock {
    long long var1;
    long long var2;
    int var3;
};

TEST(BlockAllocatorTest, BasicMethods) {
    void* main_pointer = malloc(1000);
    void* current_pointer = main_pointer;
    size_t size = sizeof(TestBlock);
    size_t align = alignof(TestBlock);

    core::allocator::BlockAllocator blockAllocator(1000, main_pointer, size, align);

    ASSERT_EQ(main_pointer, blockAllocator.getStartFreeBlock());
    ASSERT_EQ(nullptr, ((FreeBlock *) blockAllocator.getStartFreeBlock())->next_free_address);
    ASSERT_EQ(main_pointer, blockAllocator.getStart());
    ASSERT_EQ(1000, blockAllocator.getSize());
    ASSERT_EQ(0, blockAllocator.getUsedMemory());
    ASSERT_EQ(0, blockAllocator.getNumAllocations());
    ASSERT_EQ(false, blockAllocator.isFullDiscovered());
    ASSERT_EQ(size, blockAllocator.getBlockSize());
    ASSERT_EQ(align, blockAllocator.getAlignment());

    current_pointer = core::util::pointer_math::align(current_pointer, align);
    ASSERT_EQ(current_pointer, blockAllocator.getStartFreeBlock());
    size_t total_size = 1000 - ((uintptr_t) current_pointer - (uintptr_t) main_pointer);
    ASSERT_EQ(total_size / size, blockAllocator.getTotalNumberOfBlocks());

    // Allocate some memory to see if it's working fine
    auto first_memory = (TestBlock*) blockAllocator.allocate(size, align);
    ASSERT_EQ(current_pointer, first_memory);

    current_pointer = core::util::pointer_math::add(current_pointer, size);
    ASSERT_EQ(current_pointer, blockAllocator.getStartFreeBlock());
    ASSERT_EQ(main_pointer, blockAllocator.getStart());
    ASSERT_EQ(1000, blockAllocator.getSize());
    ASSERT_EQ(size, blockAllocator.getUsedMemory());
    ASSERT_EQ(1, blockAllocator.getNumAllocations());
    ASSERT_EQ(false, blockAllocator.isFullDiscovered());

    // Allocate another memory
    auto second_memory = (TestBlock*) blockAllocator.allocate(size, align);
    ASSERT_EQ(current_pointer, second_memory);

    current_pointer = core::util::pointer_math::add(current_pointer, size);
    ASSERT_EQ(current_pointer, blockAllocator.getStartFreeBlock());
    ASSERT_EQ(main_pointer, blockAllocator.getStart());
    ASSERT_EQ(1000, blockAllocator.getSize());
    ASSERT_EQ(size * 2, blockAllocator.getUsedMemory());
    ASSERT_EQ(2, blockAllocator.getNumAllocations());
    ASSERT_EQ(false, blockAllocator.isFullDiscovered());

    // Free first block
    blockAllocator.deallocate(first_memory);
    current_pointer = core::util::pointer_math::align(main_pointer, align);
    ASSERT_EQ(current_pointer, blockAllocator.getStartFreeBlock());
    ASSERT_EQ(main_pointer, blockAllocator.getStart());
    ASSERT_EQ(1000, blockAllocator.getSize());
    ASSERT_EQ(size, blockAllocator.getUsedMemory());
    ASSERT_EQ(1, blockAllocator.getNumAllocations());
    ASSERT_EQ(false, blockAllocator.isFullDiscovered());

    // Allocate another memory (Should be on first block)
    auto third_memory = (TestBlock*) blockAllocator.allocate(size, align);
    ASSERT_EQ(current_pointer, third_memory);

    current_pointer = core::util::pointer_math::add(current_pointer, size);
    current_pointer = core::util::pointer_math::add(current_pointer, size);

    ASSERT_EQ(current_pointer, blockAllocator.getStartFreeBlock());
    ASSERT_EQ(main_pointer, blockAllocator.getStart());
    ASSERT_EQ(1000, blockAllocator.getSize());
    ASSERT_EQ(size * 2, blockAllocator.getUsedMemory());
    ASSERT_EQ(2, blockAllocator.getNumAllocations());
    ASSERT_EQ(false, blockAllocator.isFullDiscovered());
}
