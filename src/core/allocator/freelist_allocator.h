#pragma once

#include "allocator.h"

namespace Core::Allocator {
    /**
     * FreeList Allocator.
     * Allocate memory where it's possible. Try to match best-match to avoid having hole.
     * Act like real memory.
     */
    class FreeListAllocator: public Allocator {

    public:
        FreeListAllocator(size_t size, void* start);

        void *allocate(size_t size, uint8_t alignment) override;
        void deallocate(void *p) override;

        [[nodiscard]] void *getStartFreeBlock() const;

    private:

        struct AllocationHeader {
            uint8_t adjustment;
            size_t size;
        };

        struct FreeBlock {
            size_t size;
            FreeBlock* next_free_address;
        };

        FreeBlock* _start_free_block;
    };
}
