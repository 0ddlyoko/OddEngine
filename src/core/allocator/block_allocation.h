#pragma once

#include "allocator.h"


namespace Core::Allocator {
    /**
     * Block Allocator.
     * Allocate memory per fixed block size
     */
    class BlockAllocation: public Allocator {

    public:
        BlockAllocation(size_t size, void* start, size_t block_size, uint8_t alignment);

        void *allocate(size_t size, uint8_t alignment) override;
        void deallocate(void *p) override;

        void *getStartFreeBlock();
        uint8_t getTotalNumberOfBlocks();

    private:

        struct FreeBlock {
            FreeBlock* next_free_address;
        };

        FreeBlock* _start_free_block;
        bool _is_full_discovered;
        size_t _block_size;
        uint8_t _alignment;
    };
}
