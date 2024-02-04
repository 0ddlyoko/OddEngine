#include <gtest/gtest.h>
#include "freelist_allocator.h"
#include "../util/pointer_math.h"


struct AllocationHeader {
    uint8_t adjustment;
    size_t size;
};

struct FreeBlock {
    size_t size;
    FreeBlock* next_free_address;
};

TEST(StackAllocatorTest, BasicMethods) {
    void* main_pointer = malloc(1000);
    void* current_pointer = main_pointer;

    core::allocator::FreeListAllocator freelistAllocator(1000, main_pointer);

    ASSERT_EQ(main_pointer, freelistAllocator.getStartFreeBlock());
    ASSERT_EQ(1000 - sizeof(FreeBlock), ((FreeBlock *) freelistAllocator.getStartFreeBlock())->size);
    ASSERT_EQ(nullptr, ((FreeBlock *) freelistAllocator.getStartFreeBlock())->next_free_address);
    ASSERT_EQ(main_pointer, freelistAllocator.getStart());
    ASSERT_EQ(1000, freelistAllocator.getSize());
    ASSERT_EQ(0, freelistAllocator.getUsedMemory());
    ASSERT_EQ(0, freelistAllocator.getNumAllocations());

    size_t sizeof_8 = sizeof(uint8_t);
    size_t sizeof_16 = sizeof(uint16_t);
    size_t sizeof_64 = sizeof(uint64_t);
    size_t alignof_8 = alignof(uint8_t);
    size_t alignof_16 = alignof(uint16_t);
    size_t alignof_64 = alignof(uint64_t);

    // Allocate some memory to see if it's working fine
    uint8_t* memory_8 = (uint8_t *) freelistAllocator.allocate(sizeof_8, alignof_8);
    *memory_8 = 42;
    uint8_t align_header = core::util::pointer_math::getAlignWithHeader<AllocationHeader>(current_pointer, alignof_8);
    current_pointer = (void *) ((uintptr_t) current_pointer + align_header);
    auto allocation_header_8 = (AllocationHeader*) core::util::pointer_math::remove(memory_8, sizeof(AllocationHeader));

    ASSERT_EQ(current_pointer, memory_8);
    current_pointer = core::util::pointer_math::add(current_pointer, sizeof_8);
    ASSERT_EQ(current_pointer, freelistAllocator.getStartFreeBlock());
    ASSERT_EQ(align_header + sizeof_8, allocation_header_8->size);
    ASSERT_EQ(main_pointer, freelistAllocator.getStart());
    ASSERT_EQ(1000, freelistAllocator.getSize());
    ASSERT_EQ(align_header + sizeof_8, freelistAllocator.getUsedMemory());
    ASSERT_EQ(1, freelistAllocator.getNumAllocations());


    // Allocate another memory
    uint16_t* memory_16 = (uint16_t *) freelistAllocator.allocate(sizeof_16, alignof_16);
    *memory_16 = 42L;
    uint8_t align_header_2 = core::util::pointer_math::getAlignWithHeader<AllocationHeader>(current_pointer, alignof_16);
    current_pointer = (void *) ((uintptr_t) current_pointer + align_header_2);
    auto allocation_header_16 = (AllocationHeader*) core::util::pointer_math::remove(memory_16, sizeof(AllocationHeader));

    ASSERT_EQ(current_pointer, memory_16);
    current_pointer = core::util::pointer_math::add(current_pointer, sizeof_16);
    ASSERT_EQ(current_pointer, freelistAllocator.getStartFreeBlock());
    ASSERT_EQ(align_header_2 + sizeof_16, allocation_header_16->size);
    ASSERT_EQ(main_pointer, freelistAllocator.getStart());
    ASSERT_EQ(1000, freelistAllocator.getSize());
    ASSERT_EQ(align_header + sizeof_8 + align_header_2 + sizeof_16, freelistAllocator.getUsedMemory());
    ASSERT_EQ(2, freelistAllocator.getNumAllocations());


    // Deallocate the uint8_t memory
    freelistAllocator.deallocate(memory_8);

    ASSERT_EQ(main_pointer, freelistAllocator.getStartFreeBlock());
    ASSERT_EQ(main_pointer, freelistAllocator.getStart());
    ASSERT_EQ(1000, freelistAllocator.getSize());
    ASSERT_EQ(align_header_2 + sizeof_16, freelistAllocator.getUsedMemory());
    ASSERT_EQ(1, freelistAllocator.getNumAllocations());


    // Allocate another memory
    uint64_t* memory_64 = (uint64_t *) freelistAllocator.allocate(sizeof_64, alignof_64);
    *memory_64 = 42L;
    uint8_t align_header_3 = core::util::pointer_math::getAlignWithHeader<AllocationHeader>(current_pointer, alignof_64);
    current_pointer = (void *) ((uintptr_t) current_pointer + align_header_3);
    auto allocation_header_64 = (AllocationHeader*) core::util::pointer_math::remove(memory_64, sizeof(AllocationHeader));

    ASSERT_EQ(current_pointer, memory_64);
    current_pointer = core::util::pointer_math::add(current_pointer, sizeof_64);
    ASSERT_EQ(main_pointer, freelistAllocator.getStartFreeBlock());
    ASSERT_EQ(align_header_3 + sizeof_64, allocation_header_64->size);
    ASSERT_EQ(main_pointer, freelistAllocator.getStart());
    ASSERT_EQ(1000, freelistAllocator.getSize());
    ASSERT_EQ(align_header_2 + sizeof_16 + align_header_3 + sizeof_64, freelistAllocator.getUsedMemory());
    ASSERT_EQ(2, freelistAllocator.getNumAllocations());


    // Allocate another memory that should fit in the
    uint8_t* memory_8_2 = (uint8_t *) freelistAllocator.allocate(sizeof_8, alignof_8);
    *memory_8_2 = 42L;
    uint8_t align_header_4 = core::util::pointer_math::getAlignWithHeader<AllocationHeader>(current_pointer, alignof_8);
    auto allocation_header_8_2 = (AllocationHeader*) core::util::pointer_math::remove(memory_8_2, sizeof(AllocationHeader));

    // Should be at the start
    ASSERT_EQ(main_pointer, memory_8_2 - align_header_4);
    ASSERT_EQ(current_pointer, freelistAllocator.getStartFreeBlock());
    ASSERT_EQ(align_header_4 + sizeof_8, allocation_header_8_2->size);
    ASSERT_EQ(main_pointer, freelistAllocator.getStart());
    ASSERT_EQ(1000, freelistAllocator.getSize());
    ASSERT_EQ(align_header_2 + sizeof_16 + align_header_3 + sizeof_64 + align_header_4 + sizeof_8, freelistAllocator.getUsedMemory());
    ASSERT_EQ(3, freelistAllocator.getNumAllocations());
}
