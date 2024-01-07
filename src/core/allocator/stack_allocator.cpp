
#include "stack_allocator.h"
#include "../util/pointer_math.h"

namespace Core::Allocator {
    StackAllocator::StackAllocator(size_t size, void *start): Allocator(size, start), _current_free(start), _last_allocation(nullptr) {}

    void *StackAllocator::allocate(size_t size, uint8_t alignment) {
        uint8_t adjustment = Core::Util::PointerMath::getAlignWithHeader<AllocationHeader>(_current_free, alignment);

        if (_used_memory + adjustment + size > _size) return nullptr;

        void* aligned_address = Core::Util::PointerMath::add(_current_free, adjustment);
        auto* header_address = (AllocationHeader*) Core::Util::PointerMath::remove(aligned_address, sizeof(AllocationHeader));
        header_address->previous_address = _current_free;
        header_address->adjustment = adjustment;

        _current_free = Core::Util::PointerMath::add(aligned_address, size);
        _used_memory += adjustment + size;
        _num_allocations++;

        return (void *) aligned_address;
    }

    void StackAllocator::deallocate(void *p) {
        assert(p == _last_allocation);
        auto* header_address = (AllocationHeader*) Core::Util::PointerMath::remove(p, sizeof(AllocationHeader));

        size_t size = ((uintptr_t) _current_free - (uintptr_t) p);
        _used_memory -= size + header_address->adjustment;
        _num_allocations--;

        _current_free = header_address->previous_address;
    }

    void *StackAllocator::getCurrentFree() {
        return _current_free;
    }

    void *StackAllocator::getLastAllocator() {
        return _last_allocation;
    }
}
