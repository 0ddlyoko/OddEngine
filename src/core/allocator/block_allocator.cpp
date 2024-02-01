
#include "block_allocator.h"
#include "../util/pointer_math.h"

namespace Core::Allocator {
    BlockAllocator::BlockAllocator(size_t size, void* start, size_t block_size, uint8_t alignment): Allocator(size, start) {
        _is_full_discovered = false;
        _block_size = (size_t) Core::Util::PointerMath::align((void*) block_size, alignment);
        _alignment = alignment;
        uint8_t alignment_to_free_block = Core::Util::PointerMath::getAlignment(start, alignment);
        assert(size > alignment_to_free_block + sizeof(FreeBlock));
        assert(size > alignment_to_free_block + block_size);
        _start_free_block = (FreeBlock*) Core::Util::PointerMath::add(start, alignment_to_free_block);
        _start_free_block->next_free_address = nullptr;
    }

    void *BlockAllocator::allocate(size_t size, uint8_t alignment) {
        assert(size == _block_size || size == 0);
        assert(alignment == _alignment || alignment == 0);

        FreeBlock* free_block = _start_free_block;
        if (free_block == nullptr)
            return nullptr;
        // Calculate next free block
        FreeBlock* next_free_block = free_block->next_free_address;
        _used_memory += _block_size;
        _num_allocations++;
        // If there is a next block, set it as the first new block
        if (next_free_block != nullptr) {
            _start_free_block = next_free_block;
            return free_block;
        }
        // Otherwise, there is no next free block. If everything has been discovered, that means there is no free space
        if (_is_full_discovered) {
            _start_free_block = nullptr;
            return free_block;
        }
        // Otherwise, there could be a free space.
        next_free_block = (FreeBlock*) Core::Util::PointerMath::add(free_block, _block_size);
        if (Core::Util::PointerMath::add(next_free_block, _block_size) > Core::Util::PointerMath::add(_start, _size)) {
            next_free_block = nullptr;
            _is_full_discovered = true;
        }
        _start_free_block = next_free_block;
        if (_start_free_block != nullptr)
            _start_free_block->next_free_address = nullptr;

        return free_block;
    }

    void BlockAllocator::deallocate(void *p) {
        // We can only deallocate the block, and add it at the beginning of the queue
        auto* free_block = (FreeBlock*) p;
        free_block->next_free_address = _start_free_block;
        _start_free_block = free_block;
        _used_memory -= _block_size;
        _num_allocations--;
    }

    void *BlockAllocator::getStartFreeBlock() const {
        return _start_free_block;
    }

    uint8_t BlockAllocator::getTotalNumberOfBlocks() const {
        uint8_t alignment_to_first_block = Core::Util::PointerMath::getAlignment(_start, _alignment);
        size_t total_size = _size - alignment_to_first_block;
        return total_size / _block_size;
    }

    bool BlockAllocator::isFullDiscovered() const {
        return _is_full_discovered;
    }

    size_t BlockAllocator::getBlockSize() const {
        return _block_size;
    }

    uint8_t BlockAllocator::getAlignment() const {
        return _alignment;
    }
}
