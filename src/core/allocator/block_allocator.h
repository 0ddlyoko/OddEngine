#pragma once

#include "allocator.h"


namespace Core::Allocator {
    /**
     * Block Allocator.
     * Allocate memory per fixed block size
     */
    class BlockAllocator: public Allocator {

    public:
        BlockAllocator(size_t size, void* start, size_t block_size, uint8_t alignment);

        void *allocate(size_t size, uint8_t alignment) override;
        void deallocate(void *p) override;

        [[nodiscard]] uint8_t getTotalNumberOfBlocks() const;
        [[nodiscard]] void *getStartFreeBlock() const;
        [[nodiscard]] bool isFullDiscovered() const;
        [[nodiscard]] size_t getBlockSize() const;
        [[nodiscard]] uint8_t getAlignment() const;


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
