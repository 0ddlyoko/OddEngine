#include <gtest/gtest.h>
#include "linear_allocator.h"
#include "../util/pointer_math.h"


TEST(LinearAllocatorTest, BasicMethods) {
    void* main_pointer = malloc(1000);
    void* current_pointer = main_pointer;

    Core::Allocator::LinearAllocator linearAllocator(1000, main_pointer);

    ASSERT_EQ(main_pointer, linearAllocator.getCurrentFree());
    ASSERT_EQ(main_pointer, linearAllocator.getStart());
    ASSERT_EQ(1000, linearAllocator.getSize());
    ASSERT_EQ(0, linearAllocator.getUsedMemory());
    ASSERT_EQ(0, linearAllocator.getNumAllocations());

    size_t sizeof_int = sizeof(int);
    size_t sizeof_long = sizeof(long);
    size_t alignof_int = alignof(int);
    size_t alignof_long = alignof(long);

    // Allocate some memory to see if it's working fine
    int* memory_int = (int *) linearAllocator.allocate(sizeof_int, alignof_int);
    *memory_int = 42;
    current_pointer = Core::Util::PointerMath::align(current_pointer, alignof_int);

    ASSERT_EQ(current_pointer, memory_int);
    current_pointer = Core::Util::PointerMath::add(current_pointer, sizeof_int);
    ASSERT_EQ(current_pointer, linearAllocator.getCurrentFree());
    ASSERT_EQ(main_pointer, linearAllocator.getStart());
    ASSERT_EQ(1000, linearAllocator.getSize());
    ASSERT_EQ(sizeof_int, linearAllocator.getUsedMemory());
    ASSERT_EQ(1, linearAllocator.getNumAllocations());


    // Allocate another memory
    long* memory_long = (long *) linearAllocator.allocate(sizeof_long, alignof_long);
    *memory_long = 42L;
    current_pointer = Core::Util::PointerMath::align(current_pointer, alignof_long);

    ASSERT_EQ(current_pointer, memory_long);
    current_pointer = Core::Util::PointerMath::add(current_pointer, sizeof_long);
    ASSERT_EQ(current_pointer, linearAllocator.getCurrentFree());
    ASSERT_EQ(main_pointer, linearAllocator.getStart());
    ASSERT_EQ(1000, linearAllocator.getSize());
    ASSERT_EQ(sizeof_int + alignof_long, linearAllocator.getUsedMemory());
    ASSERT_EQ(2, linearAllocator.getNumAllocations());

    // Clear at the end to avoid having error
    linearAllocator.clear();
}
