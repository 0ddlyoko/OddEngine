
#include "block_allocation.h"
#include "../util/pointer_math.h"

namespace Core::Allocator {
    BlockAllocation::BlockAllocation(size_t size, void* start, size_t block_size, uint8_t alignment): Allocator(size, start) {
        _is_full_discovered = false;
        _block_size = block_size;
        _alignment = alignment;
        uint8_t alignment_to_free_block = Core::Util::PointerMath::getAlignment(start, alignment);
        assert(size > alignment_to_free_block + sizeof(FreeBlock));
        _start_free_block = (FreeBlock*) Core::Util::PointerMath::add(start, alignment_to_free_block);
        _start_free_block->next_free_address = nullptr;
    }

    void *BlockAllocation::allocate(size_t size, uint8_t alignment) {
        assert(size == _block_size);
        FreeBlock* free_block = _start_free_block;
        if (free_block == nullptr)
            return nullptr;
        // Calculate next free block
        FreeBlock* next_free_block = free_block->next_free_address;
        if (next_free_block == nullptr && !_is_full_discovered) {
            next_free_block = (FreeBlock*) Core::Util::PointerMath::add(free_block, _block_size);
            next_free_block = (FreeBlock*) Core::Util::PointerMath::align(next_free_block, alignment);
            if (Core::Util::PointerMath::add(next_free_block, _block_size) >= Core::Util::PointerMath::add(_start, _size)) {
                next_free_block = nullptr;
                _is_full_discovered = true;
            }
        }
        _start_free_block = next_free_block;
        if (_start_free_block != nullptr)
            _start_free_block->next_free_address = nullptr;

        return free_block;
    }

    void BlockAllocation::deallocate(void *p) {

    }

    void *BlockAllocation::getStartFreeBlock() {
        return _start_free_block;
    }

    uint8_t BlockAllocation::getTotalNumberOfBlocks() {
        uint8_t alignment_to_free_block = Core::Util::PointerMath::getAlignment(_start, );
        uint8_t size = Core::Util::PointerMath::add(_start, )
    }
}
