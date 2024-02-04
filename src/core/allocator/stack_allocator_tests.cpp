#include <gtest/gtest.h>
#include "stack_allocator.h"
#include "../util/pointer_math.h"


struct AllocationHeader {
    uint8_t adjustment;
    void* previous_address;
};

TEST(StackAllocatorTest, BasicMethods) {
    void* main_pointer = malloc(1000);
    void* current_pointer = main_pointer;

    core::allocator::StackAllocator stackAllocator(1000, main_pointer);

    ASSERT_EQ(main_pointer, stackAllocator.getCurrentFree());
    ASSERT_EQ(main_pointer, stackAllocator.getStart());
    ASSERT_EQ(1000, stackAllocator.getSize());
    ASSERT_EQ(0, stackAllocator.getUsedMemory());
    ASSERT_EQ(0, stackAllocator.getNumAllocations());

    size_t sizeof_int = sizeof(int);
    size_t sizeof_long = sizeof(long);
    size_t alignof_int = alignof(int);
    size_t alignof_long = alignof(long);

    // Allocate some memory to see if it's working fine
    int* memory_int = (int *) stackAllocator.allocate(sizeof_int, alignof_int);
    *memory_int = 42;
    uint8_t align_header = core::util::pointer_math::getAlignWithHeader<AllocationHeader>(current_pointer, alignof_int);
    current_pointer = (int *) ((uintptr_t) current_pointer + align_header);

    ASSERT_EQ(current_pointer, memory_int);
    current_pointer = core::util::pointer_math::add(current_pointer, sizeof_int);
    ASSERT_EQ(current_pointer, stackAllocator.getCurrentFree());
    ASSERT_EQ(main_pointer, stackAllocator.getStart());
    ASSERT_EQ(1000, stackAllocator.getSize());
    ASSERT_EQ(align_header + sizeof_int, stackAllocator.getUsedMemory());
    ASSERT_EQ(1, stackAllocator.getNumAllocations());


    // Allocate another memory
    long* memory_long = (long *) stackAllocator.allocate(sizeof_long, alignof_long);
    *memory_long = 42L;
    uint8_t align_header_2 = core::util::pointer_math::getAlignWithHeader<AllocationHeader>(current_pointer, alignof_long);
    current_pointer = (long *) ((uintptr_t) current_pointer + align_header_2);

    ASSERT_EQ(current_pointer, memory_long);
    current_pointer = core::util::pointer_math::add(current_pointer, sizeof_long);
    ASSERT_EQ(current_pointer, stackAllocator.getCurrentFree());
    ASSERT_EQ(main_pointer, stackAllocator.getStart());
    ASSERT_EQ(1000, stackAllocator.getSize());
    // alignof_int + sizeof_long because it's not correctly aligned
    ASSERT_EQ(align_header + sizeof_int + align_header_2 + sizeof_long, stackAllocator.getUsedMemory());
    ASSERT_EQ(2, stackAllocator.getNumAllocations());
}
