
#include "freelist_allocator.h"
#include "../util/pointer_math.h"

namespace core::allocator {
    FreeListAllocator::FreeListAllocator(size_t size, void *start): Allocator(size, start) {
        assert(size > sizeof(FreeBlock));
        _start_free_block = (FreeBlock*) start;
        _start_free_block->size = size - sizeof(FreeBlock);
        _start_free_block->next_free_address = nullptr;
    }

    void *FreeListAllocator::allocate(size_t size, uint8_t alignment) {
        // Try to find the best match
        FreeBlock* best_match = nullptr;
        FreeBlock* best_match_previous = nullptr;
        size_t best_match_size = 0;
        uint8_t best_match_alignment = 0;
        FreeBlock* current_free_block = _start_free_block;
        FreeBlock* previous_free_block = nullptr;
        while (current_free_block != nullptr) {
            size_t block_alignment = core::util::pointer_math::getAlignWithHeader<AllocationHeader>(current_free_block, alignment);
            size_t block_real_size = block_alignment + size;
            if (current_free_block->size == block_real_size) {
                best_match = current_free_block;
                best_match_alignment = block_alignment;
                best_match_size = block_real_size;
                best_match_previous = previous_free_block;
                break;
            } else if (current_free_block->size > block_real_size && (best_match == nullptr || current_free_block->size < best_match_size)) {
                best_match = current_free_block;
                best_match_alignment = block_alignment;
                best_match_size = current_free_block->size;
                best_match_previous = previous_free_block;
            }
            previous_free_block = current_free_block;
            current_free_block = current_free_block->next_free_address;
        }
        // Check if there is a free place
        if (best_match == nullptr)
            return nullptr;
        // Recalculate size to avoid allocating the whole free block
        size_t size_to_use = best_match_alignment + size;
        // Check if it's possible to add a FreeBlock at the end of this allocation
        if (best_match->size - size_to_use <= sizeof(FreeBlock)) {
            // it's not possible, increase the size
            size_to_use = best_match->size;
            if (best_match_previous == nullptr) {
                _start_free_block = best_match->next_free_address;
            } else {
                best_match_previous->next_free_address = best_match->next_free_address;
            }
        } else {
            // It's possible
            auto* next_free_block = (FreeBlock*) core::util::pointer_math::add(best_match, size_to_use);
            next_free_block->size = best_match->size - size_to_use;
            next_free_block->next_free_address = best_match->next_free_address;
            if (best_match_previous == nullptr) {
                _start_free_block = next_free_block;
            } else {
                best_match_previous->next_free_address = next_free_block;
            }
        }
        void* aligned_address = core::util::pointer_math::add(best_match, best_match_alignment);
        auto* header_address = (AllocationHeader*) core::util::pointer_math::remove(aligned_address, sizeof(AllocationHeader));
        header_address->adjustment = best_match_alignment;
        header_address->size = size_to_use;

        _used_memory += size_to_use;
        _num_allocations++;

        return (void *) aligned_address;
    }

    void FreeListAllocator::deallocate(void *p) {
        auto* header_address = (AllocationHeader*) core::util::pointer_math::remove(p, sizeof(AllocationHeader));
        size_t header_size = header_address->size;
        void* start_address = core::util::pointer_math::remove(p, header_address->adjustment);

        // Find free block before this one
        FreeBlock* free_block_before = _start_free_block;
        while (free_block_before != nullptr && free_block_before->next_free_address != nullptr && (uintptr_t) free_block_before->next_free_address < (uintptr_t) start_address) {
            free_block_before = free_block_before->next_free_address;
        }
        if ((uintptr_t) free_block_before > (uintptr_t) start_address)
            free_block_before = nullptr;
        auto* current_free_block = (FreeBlock*) start_address;
        current_free_block->size = header_size;
        current_free_block->next_free_address = nullptr;
        if (free_block_before == nullptr) {
            // There is no free block before this one
            current_free_block->next_free_address = _start_free_block;
            _start_free_block = current_free_block;
            // Check if there is a free block right after this one
            if ((uintptr_t) current_free_block->next_free_address == (uintptr_t) current_free_block + current_free_block->size) {
                // There is a free block right after this one
                // Merge both blocks
                current_free_block->size += current_free_block->next_free_address->size;
                current_free_block->next_free_address = current_free_block->next_free_address->next_free_address;
            }
        } else {
            // There is a free block before this one
            // Check if there is a free block right after this one
            if ((uintptr_t) free_block_before->next_free_address == (uintptr_t) current_free_block + current_free_block->size) {
                // There is a free block right after this one
                // Merge both blocks
                current_free_block->size += free_block_before->next_free_address->size;
                current_free_block->next_free_address = free_block_before->next_free_address->next_free_address;
                free_block_before->next_free_address = current_free_block;
            } else {
                current_free_block->next_free_address = free_block_before->next_free_address;
                free_block_before->next_free_address = current_free_block;
            }
            // Check if there is a free block right before this one
            if ((uintptr_t) free_block_before + free_block_before->size == (uintptr_t) current_free_block) {
                // There is a free block right before this one
                // Merge both blocks
                free_block_before->size += current_free_block->size;
                free_block_before->next_free_address = current_free_block->next_free_address;
            }
        }

        _used_memory -= header_size;
        _num_allocations--;
    }

    void *FreeListAllocator::getStartFreeBlock() const {
        return _start_free_block;
    }
}
